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

#ifndef ODS_SHEET_HPP_
#define ODS_SHEET_HPP_

#include "err.hpp"
#include "global.hxx"
#include "Tag.hpp"
#include <QString>
#include <QVector>

class QXmlStreamReader;
class QXmlStreamWriter;

namespace ods	{

class Book;
class Column;
class Content;
class Ns;
class Row;
class Style;
class Tag;

class ODS_API Sheet
{
public:
	Sheet(ods::Content *content, ods::Tag*);
	virtual ~Sheet();
	
	void
	Add(ods::Row *row) { rows_.push_back(row); }
	
	ods::Book*
	book();
	
	qint32
	CalcRowCount();
	
	ods::Column*
	column() const { return column_; }
	
	ods::Content*
	content() const { return content_; }
	
	ods::Row*
	CreateRow(const qint32 at_row);
	
	const QByteArray&
	err() const { return err_; }
	
	ods::Row*
	GetPrevRow(const qint32 at_row);
	
	void
	InitEnd();
	
	ods::Row*
	InsertPlaceholder(const qint32 at_row, const qint32 row_repeat);
	
	ods::Row*
	InsertRow(const qint32 at_row);
	
	const QString&
	name() const { return name_; }
	
	ods::Ns&
	ns() const { return tag_->ns(); }
	
	void
	PreSave();
	
	ods::Row* // error => nullptr
	row(qint32 column);
	
	QVector<ods::Row*>*
	rows() { return &rows_; }
	
	void
	SetStyle(ods::Style*);
	
	ods::Style*
	style() const { return style_; }
	
	ods::Tag*
	tag() const { return tag_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Sheet);
	
	void
	Init();
	
	void
	InitColumn();
	
	void
	InitDefault();
	
	ods::Column			*column_ = nullptr;
	ods::Content		*content_ = nullptr;
	QByteArray			err_;
	QVector<ods::Row*>	rows_;
	QString				name_;
	ods::Style			*style_ = nullptr;
	ods::Tag			*tag_ = nullptr;
};

} // namespace ods
#endif
