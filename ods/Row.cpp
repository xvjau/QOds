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

#include "Row.hpp"
#include "Attrs.hpp"
#include "Book.hpp"
#include "Cell.hpp"
#include "Column.hpp"
#include "Content.hpp"
#include "Node.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "Sheet.hpp"
#include "Style.hpp"
#include "style/style.hxx"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace ods	{

Row::Row(ods::Sheet *sheet, ods::Tag *tag, const qint32 row_start) :
	row_start_(row_start),
	sheet_(sheet),
	tag_(tag)
{
	Init();
}

Row::~Row()
{
	foreach (auto *cell, cells_)
		delete cell;
}

ods::Cell*
Row::cell(const qint32 column)
{
	if (column > column_count_) {
		//mtl_qline("Fixme");
		return nullptr;
	}
	foreach (auto *cell, cells_)
	{
		if (cell->UpToColumn() >= column)
			return cell;
	}
	return nullptr;
}

ods::Cell*
Row::CreateCell(const qint32 at_column, const ods::cell::Type t)
{
	if (at_column < 0) {
		mtl_warn("at_column < 0");
		return nullptr;
	}
	if (at_column == 0) {
		return InsertCell(0, t);
	}
	
	// stage: Null
	auto *prev_cell = GetPrevCell(at_column);
	if (prev_cell == nullptr) {
		//insert placeholder with proper repeat_col
		InsertPlaceholder(0, at_column);
		return InsertCell(at_column, t);
	}
	
	// stage: Next to it
	const qint32 kPrevCellUpToCol = prev_cell->UpToColumn();

	if (kPrevCellUpToCol + 1 == at_column)
	{ // is next to it
		return InsertCell(at_column, t);
	}
	
	// stage: A gap between them
	if (prev_cell->is_placeholder())
	{
		prev_cell->SetNumColsRepeated(at_column - prev_cell->col_start());
		return InsertCell(at_column, t);
	}
	
	qint32 placeholder_num_cols = at_column - 1 - kPrevCellUpToCol;
	qint32 col_start = kPrevCellUpToCol + 1;
	InsertPlaceholder(col_start, placeholder_num_cols);
	return InsertCell(at_column, t);
}

ods::Cell*
Row::GetPrevCell(const qint32 at_column)
{
	ods::Cell *prev = nullptr;
	foreach (auto *cell, cells_)
	{
		if (cell->UpToColumn() >= at_column)
			return prev;
		prev = cell;
	}
	return prev;
}

ods::Cell*
Row::InsertCell(const qint32 at_column, const ods::cell::Type t)
{
	auto *last_cell = GetPrevCell(at_column);
	if (last_cell != nullptr && last_cell->num_cols_spanned() > 1)
	{
		auto col_repeat = last_cell->num_cols_spanned() - 1;
		auto insert_at = at_column - col_repeat;
		InsertCoveredCell(insert_at, col_repeat);
	}
	
	ods::Tag *tag = nullptr;
	if (t == ods::cell::Type::Covered)
		tag = ods::tag::CoveredSheetCell(tag_->ns(), nullptr);
	else
		tag = ods::tag::SheetCell(tag_->ns(), nullptr);
	auto *cell = new ods::Cell(this, tag, at_column);
	cell->type_set(t);
	int vec_index = 0;
	foreach (auto *cell, cells_)
	{
		if (cell->UpToColumn() > at_column)
			break;
		vec_index++;
	}
	cells_.insert(vec_index, cell);
	tag_->subnodes().insert(vec_index, new ods::Node(tag));
	return cell;
}

ods::Cell*
Row::InsertCoveredCell(const qint32 at_column, const qint32 col_repeat)
{
	auto *cell = InsertCell(at_column, ods::cell::Type::Covered);
	if (col_repeat != 1)
		cell->SetNumColsRepeated(col_repeat);
	return cell;
}

ods::Cell*
Row::InsertPlaceholder(const qint32 at_column, const qint32 col_repeat)
{
	auto *cell = InsertCell(at_column, ods::cell::Type::Placeholder);
	if (col_repeat != 1)
		cell->SetNumColsRepeated(col_repeat);
	return cell;
}

void
Row::Init()
{
	auto *attrs = tag_->attrs();
	if (attrs != nullptr) {
		auto &ns = tag_->ns();
		auto *attr = attrs->Get(ns.sheet(), ods::ns::kNumRowsRepeated);
		if (attr != nullptr)
			attr->ToInt32(num_rows_repeated_);
	}
	column_count_ = 0;
	auto &subnodes = tag_->subnodes();
	ods::Cell *last_cell = nullptr;
	
	foreach (auto *node, subnodes)
	{
		if (!node->IsTag() || !node->Tag()->IsCell())
			continue;
		auto *tag = node->Tag();
		auto *cell = new ods::Cell(this, tag, column_count_);
		last_cell = cell;
		cells_.append(cell);
		column_count_ += cell->num_cols_repeated();
	}
}

void
Row::InitEnd()
{
	foreach (ods::Cell *cell, cells_)
	{
		cell->InitEnd();
		column_count_ += cell->num_cols_repeated();
	}
}

void
Row::PreSave(const qint32 total_cols)
{
	InitEnd();
	if (total_cols <= 0)
		return;
	const auto diff = total_cols - column_count_;
	if (diff < 1)
		return;
	// if last cell is a placeholder, increase its num_cols_repeated_
	if (cells_.size() > 0) {
		auto *cell = cells_.at(cells_.size() - 1);
		if (cell->is_placeholder()) {
			cell->SetNumColsRepeated(total_cols - cell->col_start());
			return;
		}
	}
	InsertPlaceholder(column_count_, diff);
}

void
Row::SetCoveredCellRange(ods::Cell *root_cell, const qint32 kColStart,
	const qint32 kColEnd)
{
	for (auto i = kColStart; i < kColEnd;)
	{
		auto *cov_cell = cell(i);
		if (cov_cell == nullptr)
		{
			InsertCoveredCell(i, kColEnd - i + 1);
			return;
		}
		if (cov_cell == root_cell)
		{
			i += cov_cell->num_cols_repeated();
			continue;
		}
		const auto kCellEnd = i + cov_cell->num_cols_repeated();
		if (kCellEnd == kColEnd)
		{
			cov_cell->ConvertTo(ods::cell::Type::Covered);
			i += cov_cell->num_cols_repeated();
			return;
		}
		if (kCellEnd < kColEnd)
		{
			cov_cell->ConvertTo(ods::cell::Type::Covered);
			i += cov_cell->num_cols_repeated();
			continue;
		}
mtl_qline("I got here");
		// kCellEnd > kColEnd;
	}
}

void
Row::SetNumRowsRepeated(const qint32 num)
{
	tag_->AttrSet(tag_->ns().sheet(), ods::ns::kNumRowsRepeated,
		QString::number(num));
	num_rows_repeated_ = num;
}

void
Row::SetOptimalHeightStyle()
{
	if (opt_row_height_style_ == nullptr)
	{
		opt_row_height_style_ =	sheet_->book()->CreateStyle(
			ods::StyleFamilyId::Row, ods::StylePlace::ContentFile);
	}
	double max_size = 0.0;
	foreach (auto *cell, cells_)
	{
		auto *style = cell->style();
		if (style == nullptr)
			continue;
		if (style->font_size_type() == ods::FontSizeType::NotSet)
			continue;
		double d = style->FontSizeInInches();
		if (d > max_size)
			max_size = d;
	}
	
	if (max_size <= 0.0001)
		return;
	
	opt_row_height_style_->SetOptimalRowHeight(max_size * 1.2,
		ods::FontSizeType::In);
	SetStyle(opt_row_height_style_);
}

void
Row::SetStyle(ods::Style *style)
{
	style_name_ = style->name();
	tag_->AttrSet(tag_->ns().sheet(), ods::style::kStyleName, style_name_);
}

void
Row::UpdateColIndices()
{
	qint32 col_start = 0;
	foreach (auto *cell, cells_) {
		cell->col_start_set(col_start);
		col_start += cell->num_cols_repeated();
	}
}

} // namespace ods
