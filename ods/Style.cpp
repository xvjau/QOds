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

#include "Style.hpp"
#include "Book.hpp"
#include "Ns.hpp"
#include "ods.hh"
#include "style/Border.hpp"
#include "style/Manager.hpp"
#include "style/style.hxx"
#include "style/tag.hh"
#include "style/StyleFamily.hpp"
#include "Tag.hpp"

namespace ods	{ // ods::

Style::Style(ods::Book *book, ods::Tag *t,
	ods::style::StyleFamily *f, const ods::StylePlace place) :
	book_(book),
	place_(place),
	style_family_(f),
	tag_(t)
{
	Init();
}

Style::~Style()
{
	delete style_family_;
}

ods::Style*
Style::Derive(const ods::StylePlace kPlace)
{
	auto p = kPlace;
	if (p == ods::StylePlace::NotSet)
		p = place_;
	auto *style = book_->CreateStyle(style_family_->id(), p);
	style->SetParentStyle(this);
	style->font_size_set(font_size_);
	style->font_size_type_set(font_size_type_);
	return style;
}

double
Style::FontSizeInInches()
{
	if (font_size_type_ == ods::FontSizeType::In)
		return font_size_;
	if (font_size_type_ == ods::FontSizeType::NotSet) {
		mtl_warn("Fix");
		return -1.0f;
	}
	
	if (font_size_type_ == ods::FontSizeType::Cm)
		return font_size_ * ods::kInchesInACm;
	return font_size_ * ods::kInchesInAPoint;
}

void
Style::Init()
{
	tag_->AttrSet(tag_->ns().style(), ods::ns::kFamily,
		style_family_->toString());
	if (tag_->func() != ods::style::tag::DefaultStyle)
		SetUniqueName();
}

/**
ods::Tag*
Style::GetCellPropsTag() {
	return GetTag(tag_->ns().style(), ods::style::kSheetCellProps,
		ods::style::tag::SheetCellProps);
}

ods::Tag*
Style::GetColumnPropsTag() {
	return GetTag(tag_->ns().style(), ods::style::kSheetColumnProps,
		ods::style::tag::SheetColumnProps);
}

ods::Tag*
Style::GetGraphicPropsTag()
{
	return GetTag(tag_->ns().style(), ods::style::kGraphicProps,
		ods::style::tag::GraphicProps);
}

ods::Tag*
Style::GetParagraphPropsTag()
{
	return GetTag(tag_->ns().style(), ods::style::kParagraphProps,
		ods::style::tag::ParagraphProps);
}

ods::Tag*
Style::GetRowPropsTag()
{
	return GetTag(tag_->ns().style(), ods::style::kSheetRowProps,
		ods::style::tag::SheetRowProps);
}
**/

ods::Tag*
Style::GetTag(ods::tag::func f)
{
	auto *tag = tag_->GetSubtag(f);
	if (tag == nullptr)
	{
		tag = f(tag_->ns(), nullptr);
		tag_->SubtagAdd(tag);
	}
	return tag;
}
/**
ods::Tag*
Style::GetTextPropsTag() {
	return GetTag(tag_->ns().style(), ods::style::kTextProps, 
		ods::style::tag::TextProps);
}
**/
void
Style::SetBackgroundColor(const QColor &color)
{
	background_color_ = color;
	if (!style_family_->IsCell())
	{
		mtl_warn("Not implemented yet");
		return;
	}
	
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::SheetCellProps);
	tag->AttrSet(ns.fo(), ods::style::kBackgroundColor,
		background_color_.name(QColor::HexRgb));
}

void
Style::SetBold(const bool yes)
{
	if (yes)
		SetFontWeight(ods::FontWeight::Bold);
	else
		SetFontWeight(ods::FontWeight::Normal);
}

void
Style::SetBorder(ods::style::Border *border)
{
	auto *tag = GetTag(ods::style::tag::SheetCellProps);
	QString val = border->toString();
	
	const quint8 sides = border->sides();
	if (sides == ods::BorderSideAll)
	{
		tag->AttrSet(tag_->ns().fo(), ods::style::kBorder, val);
		return;
	}
	if (sides & ods::BorderSideBottom)
		tag->AttrSet(tag_->ns().fo(), ods::style::kBorderBottom, val);
	if (sides & ods::BorderSideLeft)
		tag->AttrSet(tag_->ns().fo(), ods::style::kBorderLeft, val);
	if (sides & ods::BorderSideRight)
		tag->AttrSet(tag_->ns().fo(), ods::style::kBorderRight, val);
	if (sides & ods::BorderSideTop)
		tag->AttrSet(tag_->ns().fo(), ods::style::kBorderTop, val);
}

void
Style::SetFontName(const QString &kFontName)
{
	auto *tag = GetTag(ods::style::tag::TextProps);
	book_->style_manager()->ApplyFontFace(kFontName, tag);
	font_name_ = kFontName;
}

void
Style::SetFontSize(const float size, const ods::FontSizeType size_type)
{
	if (size < 0.0001)
		return;
	font_size_ = size;
	font_size_type_ = size_type;
	QString str = ods::FontSizeToString(size, size_type);
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::TextProps);
	tag->AttrSet(ns.fo(), ods::style::kFontSize, str);
	tag->AttrSet(ns.style(), ods::style::kFontSizeAsian, str);
	tag->AttrSet(ns.style(), ods::style::kFontSizeComplex, str);
}

void
Style::SetFontStyle(const ods::FontStyle s)
{
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::TextProps);
	const char *str = nullptr;
	if (s == ods::FontStyle::Italic)
		str = ods::style::kItalic;
	else if (s == ods::FontStyle::Normal)
		str = ods::style::kNormal;
	else // if (s == ods::FontStyle::Oblique)
		str = ods::style::kOblique;
	tag->AttrSet(ns.fo(), ods::style::kFontStyle, str);
	tag->AttrSet(ns.style(), ods::style::kFontStyleAsian, str);
	tag->AttrSet(ns.style(), ods::style::kFontStyleComplex, str);
}

void
Style::SetFontWeight(const ods::FontWeight w)
{
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::TextProps);
	const char *str = nullptr;
	if (w == ods::FontWeight::Bold)
		str = ods::style::kBold;
	else if (w == ods::FontWeight::Normal)
		str = ods::style::kNormal;
	else if (w == ods::FontWeight::N100)
		str = ods::style::kN100;
	else if (w == ods::FontWeight::N200)
		str = ods::style::kN200;
	else if (w == ods::FontWeight::N300)
		str = ods::style::kN300;
	else if (w == ods::FontWeight::N400)
		str = ods::style::kN400;
	else if (w == ods::FontWeight::N500)
		str = ods::style::kN500;
	else if (w == ods::FontWeight::N600)
		str = ods::style::kN600;
	else if (w == ods::FontWeight::N700)
		str = ods::style::kN700;
	else if (w == ods::FontWeight::N800)
		str = ods::style::kN800;
	else // if (w == ods::FontWeight::N900)
		str = ods::style::kN900;
	
	tag->AttrSet(ns.fo(), ods::style::kFontWeight, str);
	tag->AttrSet(ns.style(), ods::style::kFontWeightAsian, str);
	tag->AttrSet(ns.style(), ods::style::kFontWeightComplex, str);
}

void
Style::SetItalic(const bool flag)
{
	if (flag)
		SetFontStyle(ods::FontStyle::Italic);
	else
		SetFontStyle(ods::FontStyle::Normal);
}

void
Style::SetOptimalRowHeight(const double size, const ods::FontSizeType tp)
{
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::SheetRowProps);
	tag->AttrSet(ns.style(), ods::style::kUseOptimalRowHeight, ods::ns::kTrue);
	tag->AttrSet(ns.fo(), ods::style::kBreakBefore, ods::ns::kAuto);
	QString str = ods::FontSizeToString(size, tp);
	tag->AttrSet(ns.style(), ods::style::kRowHeight, str);
}

void
Style::SetParentStyle(ods::Style *style)
{
	// style:parent-style-name
	tag_->AttrSet(tag_->ns().style(), ods::style::kParentStyleName,
		style->name());
}

void
Style::SetTextColor(const QColor &color)
{
	text_color_ = color;
	if (!style_family_->IsCell())
	{
		mtl_warn("Not implemented yet");
		return;
	}
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::TextProps);
	tag->AttrSet(ns.fo(), ods::style::kColor, text_color_.name(QColor::HexRgb));
}

void
Style::SetHAlignment(const ods::HAlign a)
{
	QString value;
	if (a == ods::HAlign::Left)
		value = QStringLiteral("start");
	else if (a == ods::HAlign::Center)
		value = QStringLiteral("center");
	else
		value = QStringLiteral("end");
	
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::ParagraphProps);
	tag->AttrSet(ns.fo(), ods::style::kTextAlign, value);
	tag->AttrSet(ns.fo(), ods::style::kMarginLeft, "0in");
}

void
Style::SetVAlignment(const ods::VAlign a)
{
	QString value;
	if (a == ods::VAlign::Top)
		value = QStringLiteral("top");
	else if (a == ods::VAlign::Middle)
		value = QStringLiteral("middle");
	else if (a == ods::VAlign::Bottom)
		value = QStringLiteral("bottom");
	
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::style::tag::SheetCellProps);
	tag->AttrSet(ns.style(), ods::style::kVerticalAlign, value);
}

void
Style::SetUniqueName()
{
	QString base;
	if (place_ == ods::StylePlace::StylesFile)
		base = QStringLiteral("st");
	else
		base = QStringLiteral("cn");
	
	if (style_family_->IsCell())
		base += QStringLiteral("ce");
	else if (style_family_->IsColumn())
		base += QStringLiteral("co");
	else if (style_family_->IsRow())
		base += QStringLiteral("ro");
	else
		base += QStringLiteral("sh");
	int i = 0;
	while (true)
	{
		name_ = base + QString::number(i);
		i++;
		if (book_->GetStyle(name_, style_family_->id()) == nullptr)
			break;
	}
	tag_->AttrSet(tag_->ns().style(), ods::ns::kName, name_);
}

} // ods::













