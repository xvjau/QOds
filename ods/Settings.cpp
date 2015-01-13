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

#include "Settings.hpp"
#include "Book.hpp"
#include "filename.hxx"
#include "Ns.hpp"
#include "Tag.hpp"
#include "tag.hh"
#include <QSaveFile>

namespace ods	{ // ods::

Settings::Settings(ods::Book *book) :
	book_(book)
{
	Init();
}

Settings::~Settings()
{}

void
Settings::Init()
{
	QString full_path = QDir(book_->temp_dir_path())
		.filePath(ods::filename::kSettings);
	QFile file(full_path);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		err_ = file.errorString();
		return;
	}
	QXmlStreamReader xml(&file);
	while(!xml.atEnd() && !xml.hasError())
	{
		if (xml.readNext() != QXmlStreamReader::StartElement)
			continue;
		if (xml.name() == ods::ns::kDocSettings) {
			ns_ = new ods::Ns(&xml, ods::UriId::Office);
			root_ = ods::tag::OfficeDocSettings(*ns_, nullptr);
			root_->Read();
		}
	}
}

void
Settings::Save(const QString &save_dir, QString &err)
{
	if (root_ == nullptr) {
		err = QStringLiteral("[Settings::Save] root_ = nullptr");
		return;
	}
	
	QSaveFile out(save_dir + QStringLiteral("/") + ods::filename::kSettings);
	out.open(QIODevice::WriteOnly);
	
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	root_->Write(xml, err);
	
	if (!err.isEmpty()) {
		out.cancelWriting();
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[Settings] QSaveFile:commit() failed");
	}
}

} // ods::
