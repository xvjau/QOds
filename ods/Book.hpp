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

#ifndef ODS_BOOK_HPP_
#define ODS_BOOK_HPP_
#include "dso.hxx"
#include "Content.hpp"
#include "Duration.hpp"
#include "ods.hh"
#include "tag.hxx"
#include <QDateTime>
#include <QString>
#include <QTemporaryDir>
#include <QVector>

class QXmlStreamWriter;

namespace ods	{

class DrawFrame;
class Manifest;
class Meta;
class Settings;
class Sheet;
class Style;

namespace style	{ // ods::style::
class Manager;
} // ods::style::

class ODS_DSO_SHARE Book
{
public:
	Book();
	Book(const QString &path);
	virtual ~Book();
	
	void
	Add(ods::DrawFrame *df);
	
	ods::Content*
	content() { return content_; }
	
	ods::Style*
	CreateCellStyle() { return CreateStyle(ods::StyleFamilyId::Cell); }
	
	ods::Style*
	CreateRowStyle() { return CreateStyle(ods::StyleFamilyId::Row); }
	
	ods::Sheet*
	CreateSheet(const QString &sheet_name);
	
	ods::Style*
	CreateStyle(const ods::StyleFamilyId,
		const ods::StylePlace = ods::StylePlace::StylesFile);
	
	ods::Style*
	CreateStyle(const ods::StyleFamilyId id, const ods::StylePlace place,
		ods::tag::func func);
	
	QVector<ods::DrawFrame*>&
	draw_frames() { return draw_frames_; }
	
	const QString&
	err() const { return err_; }
	
	void
	err_set(const QString &s) { err_ = s; }
	
	bool
	error() const { return err_.size() > 0; }
	
	bool
	extracted() { return extracted_file_paths_.size() > 0; }
	
	const QString&
	GetFrameId(const QString kFileName);
	
	QString*
	GetMediaDirPath();
	
	ods::Style*
	GetStyle(const QString &name, const ods::StyleFamilyId id);
	
	void
	InitDefault();
	
	ods::Manifest*
	manifest() const { return manifest_; }
	
	ods::Meta*
	meta() { return meta_; }
	
	void
	Read(const QString &file_path);
	
	QString
	Save(const QFile &targetOdsFile);
	
	ods::Sheet*
	sheet(int index) { return content_->sheet(index); }
	
	ods::Sheet*
	sheet(const QString &name) { return content_->sheet(name); }
	
	int
	sheet_count() { return content_->sheets().size(); }
	
	QVector<ods::Sheet*>&
	sheets() { return content_->sheets(); }
	
	ods::style::Manager*
	style_manager() { return style_manager_; }
	
	const QTemporaryDir&
	temp_dir() const { return temp_dir_; }
	
	void
	WriteStartDocument(QXmlStreamWriter&);
	
private:
	NO_ASSIGN_COPY_MOVE(Book);
	
	void
	PrepareDir(const QString &save_dir, QString &err);
	
	void
	SaveMimeTypeFile(const QString &dir_path);
	
	ods::Content			*content_ = nullptr;
	QVector<ods::DrawFrame*>	draw_frames_;
	QString					err_;
	QStringList				extracted_file_paths_;
	ods::Manifest			*manifest_ = nullptr;
	QString					media_dir_path_;
	ods::Meta				*meta_ = nullptr;
	QString					office_path_;
	ods::Settings			*settings_ = nullptr;
	ods::style::Manager		*style_manager_ = nullptr;
	QVector<ods::Style*>	styles_;
	QTemporaryDir			temp_dir_;
};

} // namespace ods
#endif
