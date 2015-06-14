/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "Content.hpp"
#include "Book.hpp"
#include "Cell.hpp"
#include "filename.hxx"
#include "Node.hpp"
#include "Ns.hpp"
#include "Row.hpp"
#include "Sheet.hpp"
#include "Style.hpp"
#include "Tag.hpp"
#include "tag.hh"
#include "style/Percent.hpp"
#include "style/style.hxx"
#include "style/tag.hh"
#include "style/StyleFamily.hpp"
#include <QDebug>
#include <QString>
#include <QXmlStreamWriter>
#include <QSaveFile>

namespace ods	{ // ods::

Content::Content(ods::Book *book) :
	book_(book)
{
	if (book_->extracted())
		Read();
	//else
		//InitDefault();
}

Content::~Content()
{
	foreach(ods::Sheet *sheet, sheets_)
		delete sheet;
	delete ns_;
}

ods::Sheet*
Content::CreateSheet(const QString &sheet_name)
{
	auto *tag = ods::tag::Sheet(*ns_, nullptr);
	tag->AttrSet(ns_->sheet(), ods::ns::kName, sheet_name);
	auto *sheet = new ods::Sheet(this, tag);
	sheets_.append(sheet);
	office_spreadsheet_->SubtagAdd(tag);
	return sheet;
}

void
Content::InitAutomaticStyles()
{
	/**
	for (int i = 0; i <= 2; i++)
	{
		auto *pst = book_->CreatePercentStyle(ods::StylePlace::ContentFile);
		pst->SetDecimalPlaces(i);
	}
	**/
}

void
Content::InitDefault()
{
	if (ns_ != nullptr)
		return;
	
	ns_ = new ods::Ns(ods::UriId::Office);
	auto &ns = *ns_;
	doc_content_ = ods::tag::OfficeDocContent(ns, nullptr);
	
	font_face_decls_tag_ = ods::style::tag::FontFaceDecls(ns, nullptr);
	doc_content_->SubtagAdd(font_face_decls_tag_);
	
	office_body_ = ods::tag::OfficeBody(ns, nullptr);
	
	automatic_styles_tag_ = ods::style::tag::AutomaticStyles(ns, nullptr);
	doc_content_->SubtagAdd(automatic_styles_tag_);
	
	doc_content_->SubtagAdd(office_body_);
	office_spreadsheet_ = ods::tag::OfficeSpreadsheet(ns, nullptr);
	office_body_->SubtagAdd(office_spreadsheet_);
	
	auto *tag = ods::tag::CalculationSettings(ns, nullptr);
	office_spreadsheet_->SubtagAdd(tag);
	tag->AttrSet(ns.sheet(), ods::ns::kCaseSensitive, ods::ns::kFalse);
	tag->AttrSet(ns.sheet(), ods::ns::kSearchWholeCell, ods::ns::kTrue);
	tag->AttrSet(ns.sheet(), ods::ns::kUseWildcards, ods::ns::kTrue);
	tag->AttrSet(ns.sheet(), ods::ns::kUseRegularExpressions, ods::ns::kFalse);
	tag->AttrSet(ns.sheet(), ods::ns::kAutomaticFindLabels, ods::ns::kFalse);

	InitAutomaticStyles();
}

void
Content::InitEnd()
{
	foreach (auto *sheet, sheets_)
		sheet->InitEnd();
}

void
Content::PreSave()
{
	foreach (auto *sheet, sheets_)
		sheet->PreSave();
}

void
Content::Read()
{
	QString full_path = QDir(book_->temp_dir_path())
		.filePath(ods::filename::kContent);
	file_.setFileName(full_path);
	if (!file_.open(QFile::ReadOnly | QFile::Text))
	{
		err_ = file_.errorString();
		return;
	}
	QXmlStreamReader xml(&file_);
	QXmlStreamReader::TokenType token;
	while(!xml.atEnd() && !xml.hasError())
	{
		token = xml.readNext();
		if (token != QXmlStreamReader::StartElement)
			continue;
		if (xml.name() == ods::ns::kDocContent) {
			ns_ = new ods::Ns(&xml, ods::UriId::Office);
			doc_content_ = ods::tag::OfficeDocContent(*ns_, nullptr);
			doc_content_->Read();
		}
	}
	Scan(doc_content_);
	InitEnd();
}

void
Content::Scan(ods::Tag *parent)
{
	auto &subnodes = parent->subnodes();
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag())
			continue;
		auto *subtag = node->Tag();
		if (subtag->IsSheet())
		{
			auto *sheet = new ods::Sheet(this, subtag);
			sheets_.push_back(sheet);
			continue;
		}
		Scan(subtag);
	}
}

ods::Sheet*
Content::sheet(int index)
{
	if (index >= sheets_.size() || index < 0)
		return nullptr;
	return sheets_.at(index);
}

ods::Sheet*
Content::sheet(const QString &name)
{
	foreach (ods::Sheet* sheet, sheets_)
		if (sheet->name() == name)
			return sheet;
	return nullptr;
}

void
Content::Save(const QString &save_dir, QString &err)
{
	if (doc_content_ == nullptr) {
		err = QStringLiteral("[Content::Save] doc_content_ empty");
		return;
	}
	
	PreSave();
	
	QSaveFile out(save_dir + QStringLiteral("/") + ods::filename::kContent);
	out.open(QIODevice::WriteOnly);
	
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	doc_content_->Write(xml, err);
	
	if (!err.isEmpty()) {
		out.cancelWriting();
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[Content] QSaveFile:commit() failed");
	}
}

} // ods::
