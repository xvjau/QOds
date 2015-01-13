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

#ifndef ODS_Content_HPP_
#define ODS_Content_HPP_

#include "global.hxx"
#include "ns.hxx"
#include "ods.hxx"
#include "err.hpp"
#include <QFile>
#include <QHash>
#include <QString>
#include <QVector>
#include <QXmlStreamReader>

class QXmlStreamWriter;

namespace ods	{

class Book;
class Ns;
class Sheet;
class Style;
class Tag;

class ODS_API Content
{
public:
	Content(ods::Book *book);
	virtual ~Content();
	
	ods::Tag*
	automatic_styles_tag() const { return automatic_styles_tag_; }
	
	ods::Book*
	book() { return book_; }

	ods::Sheet*
	CreateSheet(const QString &sheet_name);
	
	const QString&
	err() const { return err_; }
	
	void
	InitDefault();
	
	void
	InitEnd();
	
	ods::Ns&
	ns() const { return *ns_; }
	
	void
	Save(const QString &save_dir, QString &err);
	
	void
	Scan(ods::Tag *parent);
	
	ods::Sheet*
	sheet(int index);
	
	ods::Sheet*
	sheet(const QString &name);
	
	QVector<ods::Sheet*>&
	sheets() { return sheets_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Content);
	
	void
	InitAutomaticStyles();

	void
	PreSave();
	
	void
	Read();
	
	ods::Tag				*automatic_styles_tag_ = nullptr;
	const QString			base_path_;
	ods::Book				*book_ = nullptr;
	ods::Tag				*doc_content_ = nullptr;
	ods::Tag				*font_face_decls_tag_ = nullptr;
	QString					err_;
	QFile					file_;
	ods::Ns					*ns_ = nullptr;
	ods::Tag				*office_body_ = nullptr;
	ods::Tag				*office_spreadsheet_ = nullptr;
	QVector<ods::Sheet*>	sheets_;
};

} // namespace ods
#endif
