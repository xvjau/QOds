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

#include "err.hpp"
#include <QByteArray>
#include <QFile>
#include <QXmlStreamReader>

#include "cell.hxx"
#include "i18n.hxx"
#include "tag.hh"
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
	Cell(ods::Row*, ods::Tag*, const qint32 col_start);
	virtual ~Cell();
	
	QString
	Address() const;
	
	ods::Cell*
	cell_next() const { return cell_next_; }
	
	void
	cell_next_set(ods::Cell *cell) { cell_next_ = cell; }
	
	ods::Cell*
	cell_prev() const { return cell_prev_; }
	
	void
	cell_prev_set(ods::Cell *cell) { cell_prev_ = cell; }
	
	ods::Cell*
	Clone();
	
	quint16
	col_count() const { return num_cols_spanned_ * num_cols_repeated_; }
	
	qint32
	col_start() const { return col_start_; }
	
	void
	col_start_set(const int n) { col_start_ = n; }
	
	ods::DrawFrame*
	CreateDrawFrame(const QFile &file);
	
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
	
	bool
	HasTextP() const;
	
	void
	InitEnd();
	
	bool
	is_covered() const;
	
	bool
	IsEmpty() const { return value_.NoValue() && !HasTextP(); }
	
	bool
	IsEmpty2() const { return IsEmpty() && style_ == nullptr; }
	
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
	SetCovered(const bool covered = true);

	void
	SetCurrencyValue(const double num,
		const ods::i18n::CurrencyType *curr_type = nullptr);
	
	void
	SetFormula(ods::Formula*);
	
	void
	SetNumColsRepeated(const quint16 num);
	
	void
	SetPercentageType(const qint8 decimal_places = 0);
	
	void
	SetPercentageValue(const double d, const qint8 decimal_places = 0);
	
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
	
	qint32
	UpToColumn() const { return col_start_ + col_count() - 1; }
	
	ods::Value&
	value() { return value_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Cell);
	
	ods::Tag*
	GetTag(ods::Prefix &p, const char *name, ods::tag::func);
	
	void
	Init();

	void
	SetCurrencyType(const ods::i18n::CurrencyType *kCurrencyType);
	
	void
	UpdateDrawFrame();
	
	qint32			col_start_ = -100;
	quint16			num_cols_repeated_ = 1;
	quint16			num_cols_spanned_ = 1;
	//quint16		num_matrix_rows_spanned_;
	quint16			num_rows_spanned_ = 1;
	
	ods::Cell		*cell_next_ = nullptr;
	ods::Cell		*cell_prev_ = nullptr;
	
	ods::DrawFrame	*draw_frame_ = nullptr;
	ods::Formula	*formula_ = nullptr;
	ods::Row		*row_ = nullptr;
	ods::Style		*style_ = nullptr;
	ods::Tag		*tag_ = nullptr;
	ods::Value		value_;
};

} // ods::
#endif
