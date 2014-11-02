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

#ifndef ODS_CELL_HPP_
#define ODS_CELL_HPP_

#include "global.hxx"

#include <mtl/err.hpp>
#include <QByteArray>
#include <QFile>
#include <QXmlStreamReader>

#include "cell.hxx"
#include "tag.hxx"
#include "Value.hpp"

namespace ods	{ // ods::

class DrawFrame;
class Formula;
class Prefix;
class Row;
class Style;
class Tag;

class ODS_API Cell
{
public:
	Cell();
	Cell(ods::Row*, ods::Tag*, const qint32 col_start);
	virtual ~Cell();
	
	QString
	Address() const;
	
	ods::Cell*
	Clone();
	
	qint32
	col_start() const { return col_start_; }
	
	void
	col_start_set(const int n) { col_start_ = n; }
	
	void
	ConvertTo(const ods::cell::Type);
	
	QString
	Diagnose() { return value_.Diagnose(); }
	
	ods::Formula*
	formula() const { return formula_; }
	
	void
	formula_set(ods::Formula *f) { formula_ = f; }
	
	ods::Tag*
	GetDrawFrameTag();
	
	bool
	HasFormula() const { return formula_ != nullptr; }
	
	void
	InitEnd();
	
	bool
	is_placeholder() const { return type_ == ods::cell::Type::Placeholder; }
	
	ods::DrawFrame*
	CreateDrawFrame(const QFile &file);
	
	quint16
	num_cols_repeated() const { return num_cols_repeated_; }
	
	void
	num_cols_repeated_set(const quint16 n) { num_cols_repeated_ = n; }
	
	quint16
	num_cols_spanned() const { return num_cols_spanned_; }
	
	void
	num_cols_spanned_set(const quint16 n) { num_cols_spanned_ = n; }
	
	quint16
	num_rows_spanned() const { return num_rows_spanned_; }
	
	void
	num_rows_spanned_set(const quint16 n) { num_rows_spanned_ = n; }
	
	ods::Row*
	row() const { return row_; }
	
	void
	Set(ods::Prefix &prefix, const char *key, const QString &value);
	
	void
	SetCovered();
	
	void
	SetFormula(ods::Formula*);
	
	void
	SetNumColsRepeated(const qint32 num);
	
	void //@@@HasDoc
	SetRowColSpan(const quint16, const quint16);
	
	void
	SetStyle(ods::Style*);
	
	void
	SetValue(const double);
	
	void
	SetValue(const QString&);
	
	ods::Style*
	style() const { return style_; }
	
	ods::Tag*
	tag() { return tag_; }
	
	ods::cell::Type
	type() const { return type_; }
	
	void
	type_set(const ods::cell::Type t) { type_ = t; }
	
	void
	UpdateAll() { UpdateValue(); }
	
	void
	UpdateValue() { mtl_line("Should not be called"); };
	
	qint32
	UpToColumn() const { return col_start_ +
		(num_cols_spanned_ * num_cols_repeated_) - 1; }
	
	ods::Value&
	value() { return value_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Cell);
	
	ods::Tag*
	GetTag(ods::Prefix &p, const char *name, ods::tag::func);
	
	void
	Init();
	
	void
	UpdateDrawFrame();
	
	qint32			col_start_ = 0;
	quint16			num_cols_repeated_ = 1;
	quint16			num_cols_spanned_ = 1;
	//quint16		num_matrix_rows_spanned_;
	quint16			num_rows_spanned_ = 1;
	
	ods::DrawFrame	*draw_frame_ = nullptr;
	ods::Formula	*formula_ = nullptr;
	ods::Row		*row_ = nullptr;
	ods::Style		*style_ = nullptr;
	ods::Tag		*tag_ = nullptr;
	ods::cell::Type	type_ = ods::cell::Type::Normal;
	ods::Value		value_;
};

} // ods::
#endif
