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

#include "Meta.hpp"
#include "Book.hpp"
#include "filename.hxx"
#include "meta.hh"
#include "Ns.hpp"
#include "ods.hxx"
#include "Tag.hpp"
#include <QDebug>
#include <QSaveFile>

namespace ods	{

Meta::Meta(ods::Book *book) :
	book_(book)
{
	if (book_->extracted())
		Read();
	else
		InitDefault();
}

Meta::~Meta()
{
	delete ns_;
	delete office_doc_;
}

void
Meta::InitDefault()
{
	ns_ = new ods::Ns(ods::UriId::Office);
	office_doc_ = ods::meta::OfficeDocument(*ns_, nullptr);
	office_meta_ = ods::meta::Office(*ns_, nullptr);
	office_doc_->SubtagAdd(office_meta_);
	
	/**
	auto *generator = ods::meta::Generator(*ns_, nullptr);
	office_meta_->SubtagAdd(generator);
	const QString kGenerator = 
		"LibreOffice/4.2.4.2$Linux_X86_64 LibreOffice_project/420$Build-2";
	generator->SubnodeAdd(new ods::Node(kGenerator));
	
	auto *creation_date = ods::meta::CreationDate(*ns_, nullptr);
	office_meta_->SubtagAdd(creation_date);
	auto date_time = QDateTime::currentDateTimeUtc();
	const QString date_str = date_time.toString(Qt::ISODate);
	creation_date->SubnodeAdd(new ods::Node(date_str));
	**/
}

void
Meta::Read()
{
	QString full_path = QDir(book_->temp_dir_path())
		.filePath(ods::filename::kMeta);
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
		if (xml.name() == ods::ns::kDocMeta) {
			ns_ = new ods::Ns(&xml, ods::UriId::Office);
			office_doc_ = ods::meta::OfficeDocument(*ns_, nullptr);
			office_doc_->Read();
		}
	}
}

void
Meta::Save(const QString &save_dir, QString &err)
{
	if (office_doc_ == nullptr)
		return;
	QString path = save_dir + QStringLiteral("/") + ods::filename::kMeta;
	QSaveFile out(path);
	out.open(QIODevice::WriteOnly);
	QXmlStreamWriter xml(&out);
	book_->WriteStartDocument(xml);
	office_doc_->Write(xml, err);
	
	if (!err.isEmpty()) {
		out.cancelWriting();
		mtl_qline(QString("Failed: ") + err);
	} else {
		xml.writeEndDocument();
		if (!out.commit())
			err = QStringLiteral("[Meta] QSaveFile:commit() failed");
	}
}


/**
void
Meta::ReadMeta()
{
	const QString &kCreationDate = ns_->meta().With(ods::ns::kCreationDate);
	const QString &kDate = ns_->dc().With(ods::ns::kDate);
	const QString &kEditingDuration = ns_->meta().With(
		ods::ns::kEditingDuration);
	const QString &kEditingCycles = ns_->meta().With(
		ods::ns::kEditingCycles);
	const QString &kGenerator = ns_->meta().With(ods::ns::kGenerator);
	const QString &kDocStatistic = ns_->meta().With(ods::ns::kDocStatistic);
	
	while (xml_.readNextStartElement()) {
		const QStringRef &name = xml_.qualifiedName();
		if (name == kCreationDate) {
			QString s = xml_.readElementText();
			creation_date_ = QDateTime::fromString(s, Qt::ISODate);
		} else if(name == kDate) {
			QString s = xml_.readElementText();
			dc_date_ = QDateTime::fromString(s, Qt::ISODate);
		} else if (name == kEditingDuration) {
			QString s = xml_.readElementText();
			editing_duration_ = ods::Duration::FromString(s);
		} else if (name == kEditingCycles) {
			editing_cycles_ = xml_.readElementText().toInt();
		} else if (name == kGenerator) {
			generator_ = xml_.readElementText();
		} else if (name == kDocStatistic) {
			const auto attrs = xml_.attributes();
			auto key = ns_->meta().With(ods::ns::kCellCount);
			cell_count_ = attrs.value(key).toInt();
			key = ns_->meta().With(ods::ns::kObjectCount);
			object_count_ = attrs.value(key).toInt();
			key = ns_->meta().With(ods::ns::kTableCount);
			sheet_count_ = attrs.value(key).toInt();
		}
	}
}
**/

} // namespace ods
