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

#include "Cell.hpp"
#include "Attrs.hpp"
#include "Book.hpp"
#include "DrawFrame.hpp"
#include "Formula.hpp"
#include "Node.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "PercentStyle.hpp"
#include "Row.hpp"
#include "Sheet.hpp"
#include "style/style.hxx"
#include "style/StyleFamily.hpp"
#include "Style.hpp"
#include "Tag.hpp"
#include "util.hh"
#include "Value.hpp"

namespace ods	{

Cell::Cell()
{
	mtl_qline("FIX THE CODE");
}

Cell::Cell(ods::Row *row, ods::Tag *tag, const qint32 col_start) :
	col_start_(col_start),
	row_(row),
	tag_(tag)
{
	row->column_count_set(col_start);
	Init();
}

Cell::~Cell() {
	delete formula_;
	delete draw_frame_;
}

QString
Cell::Address() const
{
	return ods::GenColName(col_start_) + QString::number(row_->row_start() + 1);
}

ods::Cell*
Cell::Clone()
{
	auto *tag = tag_->Clone();
	auto *cell = new ods::Cell(row_, tag, col_start_);
	cell->num_cols_repeated_set(num_cols_repeated_);
	cell->num_cols_spanned_set(num_cols_spanned_);
	cell->num_rows_spanned_set(num_rows_spanned_);
	if (formula_ != nullptr)
		cell->formula_set(formula_->Clone());
	cell->SetStyle(style_);
	cell->type_set(type_);
	value_.CopyTo(cell->value());
	return cell;
}

void
Cell::ConvertTo(const ods::cell::Type t)
{
	auto &ns = tag_->ns();
	if (t == ods::cell::Type::Covered)
	{
		tag_->attr_set(ns.sheet(), ods::ns::kCoveredSheetCell);
		tag_->func_set(ods::tag::CoveredSheetCell);
		type_ = ods::cell::Type::Covered;
	} else {
		tag_->attr_set(ns.sheet(), ods::ns::kSheetCell);
		tag_->func_set(ods::tag::SheetCell);
		if (t == ods::cell::Type::Placeholder)
			type_ = ods::cell::Type::Placeholder;
		else
			type_ = ods::cell::Type::Normal;
	}
}

ods::Tag*
Cell::GetDrawFrameTag()
{
	return GetTag(tag_->ns().draw(), ods::ns::kFrame, ods::tag::DrawFrame);
}

ods::Tag*
Cell::GetTag(ods::Prefix &p, const char *name, ods::tag::func f)
{
	auto *tag = tag_->GetSubtag(p, name);
	if (tag == nullptr)
	{
		tag = f(tag_->ns(), nullptr);
		tag_->SubtagAdd(tag);
	}
	return tag;
}

void
Cell::Init()
{
	auto *attrs = tag_->attrs();
	if (attrs == nullptr)
		return;
	
	auto &ns = tag_->ns();
	auto &subnodes = tag_->subnodes();
	bool is_string_type = false;
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		
		auto *type_attr = attrs->Get(ns.office(), ods::ns::kValueType);
		if (type_attr != nullptr)
		{
			auto tp = ods::TypeFromString(type_attr->value());
			is_string_type = (tp == ods::Type::String);
		}
		if (!is_string_type)
			continue;
		auto &nodes = tag->subnodes();
		foreach (auto *n, nodes)
		{
			if (!n->IsString())
				continue;
			value_.SetString(*n->String());
			break;
		}
		break;
	}
	
	auto *attr = attrs->Get(ns.sheet(), ods::ns::kNumColsSpanned);
	if (attr != nullptr)
		attr->ToUint16(num_cols_spanned_);
	attr = attrs->Get(ns.sheet(), ods::ns::kNumColsRepeated);
	if (attr != nullptr)
		attr->ToUint16(num_cols_repeated_);
	attr = attrs->Get(ns.sheet(), ods::ns::kNumRowsSpanned);
	if (attr != nullptr)
		attr->ToUint16(num_rows_spanned_);
	if (!is_string_type)
		value_.Read(ns, *attrs);
}

void
Cell::InitEnd()
{
	auto *attrs = tag_->attrs();
	if (attrs == nullptr)
		return;
	auto &ns = tag_->ns();
	auto *attr = attrs->Get(ns.sheet(), ods::ns::kFormula);
	if (attr == nullptr)
		return;
	const auto &formula_str = attr->value();
	// init formula after all other attributes read
	if (formula_str.isEmpty())
		return;
	formula_ = new ods::Formula(this, formula_str);
	if (formula_->error())
		mtl_qline(formula_->err());
	else
		formula_->UpdateValue();
}

ods::DrawFrame*
Cell::CreateDrawFrame(const QFile &file)
{
	if (draw_frame_ != nullptr)
	{
		mtl_warn("draw_frame_ != nullptr");
		return nullptr;
	}
	draw_frame_ = new ods::DrawFrame(this, file);
	if (draw_frame_->ok()) {
		return draw_frame_;
	}
	delete draw_frame_;
	draw_frame_ = nullptr;
	return nullptr;
}

void
Cell::SetFormula(ods::Formula *f)
{
	if (formula_ != nullptr)
		delete formula_;
	formula_ = f;
	formula_->source_set(this);
	auto &ns = tag_->ns();
	QString str = formula_->formula();
	tag_->AttrSet(ns.sheet(), ods::ns::kFormula, str);
	tag_->AttrSet(ns.office(), ods::ns::kValueType, ods::ns::kDouble);
}

void
Cell::SetNumColsRepeated(const qint32 num)
{
	tag_->AttrSet(tag_->ns().sheet(), ods::ns::kNumColsRepeated,
		QString::number(num));
	num_cols_repeated_ = num;
}

void
Cell::SetPercentageType(const qint8 decimal_places)
{
	const qint8 kDecimalPlaces = (decimal_places < 0) ? 0 : decimal_places;
	if (value_.IsPercentage())
	{
		style_->GetPercentStyle()->SetDecimalPlaces(kDecimalPlaces);
		return;
	}
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.office(), ods::ns::kValueType, ods::ns::kPercentage);
	auto *book = row_->sheet()->book();
	if (style_ == nullptr)
	{
		style_ = book->CreateStyle(ods::StyleFamilyId::Cell,
			ods::StylePlace::ContentFile);
		SetStyle(style_);
	}
	auto *percent_style = style_->GetPercentStyle();
	if (percent_style == nullptr)
	{
		percent_style = book->GetPercentStyle(kDecimalPlaces);
		if (percent_style == nullptr)
			percent_style = book->CreatePercentStyle(ods::StylePlace::StylesFile);
		style_->SetPercentStyle(percent_style);
	}
	percent_style->SetDecimalPlaces(kDecimalPlaces);
}

void
Cell::SetPercentageValue(const double num, const qint8 decimal_places)
{
	auto &ns = tag_->ns();
	if (!value_.IsPercentage())
	{
		SetPercentageType(decimal_places);
	} else {
		const qint8 kDecimalPlaces = (decimal_places < 0) ? 0 : decimal_places;
		style_->GetPercentStyle()->SetDecimalPlaces(kDecimalPlaces);
	}
	tag_->AttrSet(ns.office(), ods::ns::kValue, QString::number(num));
	value_.SetPercentage(num);
}

void
Cell::SetRowColSpan(const quint16 num_rows, const quint16 num_cols)
{
	auto *sheet = row_->sheet();
	const auto kRowStart = row_->row_start();
	const auto kRowEnd = kRowStart + num_rows;
	const auto kColEnd = col_start_ + num_cols - 1;
	for (auto i = kRowStart; i < kRowEnd; i++)
	{
		auto *row = sheet->row(i);
		if (row == nullptr)
			row = sheet->CreateRow(i);
		else
			row->InitEnd();
		row->SetCoveredCellRange(this, col_start_, kColEnd);
	}
	tag_->AttrSet(tag_->ns().sheet(), ods::ns::kNumRowsSpanned,
		QString::number(num_rows));
	num_rows_spanned_ = num_rows;
	
	tag_->AttrSet(tag_->ns().sheet(), ods::ns::kNumColsSpanned,
		QString::number(num_cols));
	num_cols_spanned_ = num_cols;
}

void
Cell::SetStyle(ods::Style *style)
{
	if (style_ != nullptr && style_->GetPercentStyle() != nullptr)
	{
		qDebug() << "Warning at Cell::SetStyle(..): call cell->SetStyle(..)"
			<< "before calling cell->SetPercentageValue(..)";
		style_->SetParentStyle(style);
	} else {
		style_ = style;
		tag_->AttrSet(tag_->ns().sheet(), ods::style::kStyleName, style_->name());
	}
}

void
Cell::SetValue(const double num)
{
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.office(), ods::ns::kValueType, ods::ns::kDouble);
	const QString value = QString::number(num);
	tag_->AttrSet(ns.office(), ods::ns::kValue, value);
	tag_->SetTextP(value);
	if (tag_->attrs() != nullptr)
		value_.Read(ns, *tag_->attrs());
}

void
Cell::SetValue(const QString &value)
{
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.office(), ods::ns::kValueType, ods::ns::kString);
	tag_->SetTextP(value);
	if (tag_->attrs() != nullptr)
		value_.Read(ns, *tag_->attrs());
}

} // namespace ods


































