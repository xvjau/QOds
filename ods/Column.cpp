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

#include "Column.hpp"
#include "Ns.hpp"
#include "Style.hpp"
#include "style/style.hxx"
#include "Tag.hpp"

namespace ods	{ // ods::

Column::Column(ods::Sheet *sheet, ods::Tag *tag) :
	sheet_(sheet),
	tag_(tag)
{
	Init();
}

Column::~Column()
{}

void
Column::Init()
{
	auto *attrs = tag_->attrs();
	if (attrs == nullptr)
		return;
	auto &ns = tag_->ns();
	auto *attr = attrs->Get(ns.sheet(), ods::ns::kNumColsRepeated);
	if (attr != nullptr)
		attr->ToInt32(column_count_);
	//attr = attrs->Get(ns.sheet(), ods::style::kStyleName);
	//if (attr != nullptr)
}

void
Column::SetNumColsRepeated(const qint32 num)
{
	auto &ns = tag_->ns();
	column_count_ = num;
	if (column_count_ > 0)
		tag_->AttrSet(ns.sheet(), ods::ns::kNumColsRepeated,
			QString::number(num));
}

void
Column::SetStyle(ods::Style *style)
{
	style_ = style;
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.sheet(), ods::style::kStyleName, style->name());
}

} // ods::

















