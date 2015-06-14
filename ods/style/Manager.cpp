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

#include "Manager.hpp"
#include "tag.hh"
#include "../Book.hpp"
#include "../filename.hxx"
#include "../Node.hpp"
#include "../Ns.hpp"
#include "../Style.hpp"
#include "style.hxx"
#include "StyleFamily.hpp"
#include "../Tag.hpp"
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamWriter>

namespace ods	{ // ods::
namespace style	{ // ods::style::

Manager::Manager(ods::Book *book) :
	book_(book)
{
	if (book_->extracted())
		Read();
	//else
	//	InitDefault();
}

Manager::~Manager()
{
	delete ns_;
	delete root_tag_;
}

void
Manager::ApplyFontFace(const QString &kFontName, ods::Tag *tag)
{
	auto &ns = *ns_;
	tag->AttrSet(ns.style(), ods::style::kFontName, kFontName);
	tag->AttrSet(ns.style(), ods::style::kFontNameAsian, kFontName);
	tag->AttrSet(ns.style(), ods::style::kFontNameComplex, kFontName);
	
	foreach (const QString &name, font_names_)
	{
		if (name == kFontName)
			return;
	}
	
	font_names_.append(kFontName);
	tag = ods::style::tag::FontFace(ns, nullptr);
	font_face_decls_tag_->SubtagAdd(tag);
	
	tag->AttrSet(ns.style(), ods::ns::kName, kFontName);
	if (kFontName.indexOf(' ') != -1) {
		auto str = QString("'").append(kFontName).append("'");
		tag->AttrSet(ns.svg(), ods::style::kFontFamily, str);
	} else {
		tag->AttrSet(ns.svg(), ods::style::kFontFamily, kFontName);
	}
}

void
Manager::InitFontFaceDecls()
{
	auto &ns = *ns_;
	font_face_decls_tag_ = ods::style::tag::FontFaceDecls(ns, nullptr);
	root_tag_->SubtagAdd(font_face_decls_tag_);
}

void
Manager::InitDefault()
{
	if (ns_ != nullptr)
		return;
	
	ns_ = new ods::Ns(ods::UriId::Office);
	root_tag_ = ods::style::tag::OfficeDocStyles(*ns_, nullptr);
	
	InitFontFaceDecls();

	styles_tag_ = ods::style::tag::Styles(*ns_, nullptr);
	ods::style::tag::Styles(*ns_, styles_tag_);
	root_tag_->SubtagAdd(styles_tag_);

	automatic_styles_tag_ = ods::style::tag::AutomaticStyles(*ns_, nullptr);
	root_tag_->SubtagAdd(automatic_styles_tag_);

	master_styles_tag_ = ods::style::tag::MasterStyles(*ns_, nullptr);
	root_tag_->SubtagAdd(master_styles_tag_);

	InitDefaultStyles();
}

void
Manager::InitDefaultStyles()
{
	auto &ns = *ns_;
	auto *default_style = book_->CreateStyle(ods::StyleFamilyId::Cell,
		ods::StylePlace::StylesFile, ods::style::tag::DefaultStyle);
	
	auto *tag = default_style->GetTag(ods::style::tag::ParagraphProps);
	tag->AttrSet(ns.style(), ods::style::kTabStopDistance,
		QStringLiteral("0.5in"));
}

void
Manager::Read()
{
	QString full_path = QDir(book_->temp_dir_path())
		.filePath(ods::filename::kStyles);
	QFile file(full_path);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		err_ = file.errorString();
		return;
	}
	QXmlStreamReader xml(&file);
	while (!xml.atEnd() && !xml.hasError())
	{
		if (xml.readNext() != QXmlStreamReader::StartElement)
			continue;
		if (xml.name() == ods::ns::kDocStyles) {
			ns_ = new ods::Ns(&xml, ods::UriId::Office);
			root_tag_ = ods::style::tag::OfficeDocStyles(*ns_, nullptr);
			root_tag_->Read();
		}
	}
	
	auto &subnodes = root_tag_->subnodes();
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		const auto f = tag->func();
		if (f == ods::style::tag::AutomaticStyles)
			automatic_styles_tag_ = tag;
		else if (f == ods::style::tag::FontFaceDecls)
			font_face_decls_tag_ = tag;
		else if (f == ods::style::tag::MasterStyles)
			master_styles_tag_ = tag;
		else if (f == ods::style::tag::Styles)
			styles_tag_ = tag;
	}
}

void
Manager::Save(const QString &save_dir, QString &err)
{
	QSaveFile out(save_dir + QStringLiteral("/") + ods::filename::kStyles);
	out.open(QIODevice::WriteOnly);
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	root_tag_->Write(xml, err);
	if (!err.isEmpty()) {
		out.cancelWriting();
		mtl_qline(QStringLiteral("Failed: ") + err);
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[styles] QSaveFile:commit() failed");
	}
}

} // ods::style::
} // ods::















