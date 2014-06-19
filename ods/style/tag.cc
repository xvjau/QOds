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

#include "tag.hh"
#include "../Ns.hpp"
#include "style.hxx"
#include "../Tag.hpp"
#include "../tag.hh"

namespace ods		{ // ods::
namespace style		{ // ods::style::
namespace tag		{ // ods::style::tag::

ods::Tag*
AutomaticStyles(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		auto *t = new ods::Tag(ns, ods::style::tag::AutomaticStyles);
		t->attr_set(ns.office(), ods::style::kAutomaticStyles);
		return t;
	}
	tag->SubfuncAdd(ods::style::tag::PageLayout);
	tag->SubfuncAdd(ods::style::tag::Style);
	return nullptr;
}

ods::Tag*
DefaultStyle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		auto *t = new ods::Tag(ns, ods::style::tag::DefaultStyle);
		t->attr_set(ns.style(), ods::style::kDefaultStyle);
		return t;
	}
	tag->Add(ns.style(), ods::ns::kFamily);
	tag->SubfuncAdd(ods::style::tag::ParagraphProps);
	tag->SubfuncAdd(ods::style::tag::SheetCellProps);
	tag->SubfuncAdd(ods::style::tag::SheetColumnProps);
	tag->SubfuncAdd(ods::style::tag::SheetProps);
	tag->SubfuncAdd(ods::style::tag::SheetRowProps);
	tag->SubfuncAdd(ods::style::tag::TextProps);
	return nullptr;
}

ods::Tag*
FontFace(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		auto *t = new ods::Tag(ns, ods::style::tag::FontFace);
		t->attr_set(ns.style(), ods::style::kFontFace);
		return t;
	}
	
	tag->Add(ns.svg(), ods::style::kFontFamily);
	tag->Add(ns.style(), ods::style::kFontFamilyGeneric);
	tag->Add(ns.style(), ods::style::kFontPitch);
	tag->Add(ns.style(), ods::ns::kName);
	return nullptr;
}

ods::Tag*
FontFaceDecls(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		auto *t = new ods::Tag(ns, ods::style::tag::FontFaceDecls);
		t->attr_set(ns.office(), ods::style::kFontFaceDecls);
		return t;
	}
	tag->SubfuncAdd(ods::style::tag::FontFace);
	return nullptr;
}

ods::Tag*
FooterStyle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::FooterStyle);
		tag->attr_set(ns.style(), ods::style::kFooterStyle);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::HeaderFooterProps);
	return nullptr;
}

ods::Tag*
GraphicProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::style::tag::GraphicProps);
		tag->attr_set(ns.style(), ods::style::kGraphicProps);
		return tag;
	}
	tag->Add(ns.draw(), ods::style::kStroke);
	tag->Add(ns.draw(), ods::style::kFill);
	tag->Add(ns.draw(), ods::style::kTextAreaHorizAlign);
	tag->Add(ns.draw(), ods::style::kTextAreaVertAlign);
	tag->Add(ns.draw(), ods::style::kColorMode);
	tag->Add(ns.draw(), ods::style::kLuminance);
	tag->Add(ns.draw(), ods::style::kContrast);
	tag->Add(ns.draw(), ods::style::kGamma);
	tag->Add(ns.draw(), ods::style::kRed);
	tag->Add(ns.draw(), ods::style::kGreen);
	tag->Add(ns.draw(), ods::style::kBlue);
	tag->Add(ns.draw(), ods::style::kImageOpacity);
	tag->Add(ns.fo(), ods::style::kClip);
	return nullptr;
}

ods::Tag*
HeaderFooterProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::HeaderFooterProps);
		tag->attr_set(ns.style(), ods::style::kHeaderFooterProps);
		return tag;
	}
	
	tag->Add(ns.fo(), ods::style::kBackgroundColor);
	tag->Add(ns.fo(), ods::style::kBorder);
	tag->Add(ns.fo(), ods::style::kMarginBottom);
	tag->Add(ns.fo(), ods::style::kMarginLeft);
	tag->Add(ns.fo(), ods::style::kMarginRight);
	tag->Add(ns.fo(), ods::style::kMarginTop);
	tag->Add(ns.fo(), ods::style::kMinHeight);
	tag->Add(ns.fo(), ods::style::kPadding);
	
	//tag->SubfuncAdd(ods::tag::tag::BackgroundImage);
	return nullptr;
}

ods::Tag*
HeaderStyle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::HeaderStyle);
		tag->attr_set(ns.style(), ods::style::kHeaderStyle);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::HeaderFooterProps);
	return nullptr;
}

ods::Tag*
Map(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::Map);
		tag->attr_set(ns.style(), ods::ns::kMap);
		return tag;
	}
	
	tag->Add(ns.style(), ods::style::kApplyStyleName);
	tag->Add(ns.style(), ods::style::kBaseCellAddress);
	tag->Add(ns.style(), ods::style::kCondition);
	return nullptr;
}

ods::Tag*
MasterPage(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::MasterPage);
		tag->attr_set(ns.style(), ods::style::kMasterPage);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kName);
	tag->Add(ns.style(), ods::style::kPageLayoutName);
	tag->SubfuncAdd(ods::style::tag::StyleFooter);
	tag->SubfuncAdd(ods::style::tag::StyleFooterLeft);
	tag->SubfuncAdd(ods::style::tag::StyleHeader);
	tag->SubfuncAdd(ods::style::tag::StyleHeaderLeft);
	return nullptr;
}

ods::Tag*
MasterStyles(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::MasterStyles);
		tag->attr_set(ns.office(), ods::style::kMasterStyles);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::MasterPage);
	return nullptr;
}

ods::Tag*
NumberCurrencyStyle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::NumberCurrencyStyle);
		tag->attr_set(ns.number(), ods::style::kCurrencyStyle);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kName);
	tag->Add(ns.style(), ods::ns::kVolatile);
	tag->SubfuncAdd(ods::tag::CurrencySymbol);
	tag->SubfuncAdd(ods::style::tag::Map);
	tag->SubfuncAdd(ods::tag::Number);
	tag->SubfuncAdd(ods::tag::NumberText);
	tag->SubfuncAdd(ods::style::tag::TextProps);
	return nullptr;
}

ods::Tag*
NumberStyle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::NumberStyle);
		tag->attr_set(ns.number(), ods::style::kNumberStyle);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kName);
	tag->SubfuncAdd(ods::tag::Number);
	return nullptr;
}

ods::Tag*
OfficeDocStyles(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::OfficeDocStyles);
		tag->attr_set(ns.office(), ods::ns::kDocStyles);
		tag->SetPrintXmlns(true);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::AutomaticStyles);
	tag->SubfuncAdd(ods::style::tag::FontFaceDecls);
	tag->SubfuncAdd(ods::style::tag::MasterStyles);
	tag->SubfuncAdd(ods::style::tag::Styles);
	return nullptr;
}

ods::Tag*
PageLayout(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::PageLayout);
		tag->attr_set(ns.style(), ods::style::kPageLayout);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kName);
	tag->Add(ns.style(), ods::ns::kPageUsage);
	tag->SubfuncAdd(ods::style::tag::FooterStyle);
	tag->SubfuncAdd(ods::style::tag::HeaderStyle);
	tag->SubfuncAdd(ods::style::tag::PageLayoutProps);
	return nullptr;
}

ods::Tag*
PageLayoutProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::PageLayoutProps);
		tag->attr_set(ns.style(), ods::style::kPageLayoutProps);
		return tag;
	}
	tag->Add(ns.style(), ods::style::kWritingMode);
	return nullptr;
}

ods::Tag*
ParagraphProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::ParagraphProps);
		tag->attr_set(ns.style(), ods::style::kParagraphProps);
		return tag;
	}
	tag->Add(ns.style(), ods::style::kTabStopDistance);
	tag->Add(ns.fo(), ods::style::kTextAlign);
	return nullptr;
}

ods::Tag*
RegionLeft(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::RegionLeft);
		tag->attr_set(ns.style(), ods::style::kRegionLeft);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::TextP);
	return nullptr;
}

ods::Tag*
RegionRight(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::RegionRight);
		tag->attr_set(ns.style(), ods::style::kRegionRight);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::TextP);
	return nullptr;
}

ods::Tag*
SheetCellProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::SheetCellProps);
		tag->attr_set(ns.style(), ods::style::kSheetCellProps);
		return tag;
	}
	tag->Add(ns.fo(), ods::style::kBorder);
	tag->Add(ns.fo(), ods::style::kBorderBottom);
	tag->Add(ns.fo(), ods::style::kBorderLeft);
	tag->Add(ns.fo(), ods::style::kBorderRight);
	tag->Add(ns.fo(), ods::style::kBorderTop);
	tag->Add(ns.fo(), ods::style::kBackgroundColor);
	tag->Add(ns.style(), ods::style::kRepeatContent);
	tag->Add(ns.style(), ods::style::kRotationAngle);
	tag->Add(ns.style(), ods::style::kTextAlignSource);
	return nullptr;
}

ods::Tag*
SheetColumnProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::SheetColumnProps);
		tag->attr_set(ns.style(), ods::style::kSheetColumnProps);
		return tag;
	}
	tag->Add(ns.fo(), ods::style::kBreakBefore);
	tag->Add(ns.style(), ods::style::kColumnWidth);
	return nullptr;
}

ods::Tag*
SheetProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::style::tag::SheetProps);
		tag->attr_set(ns.style(), ods::style::kSheetProps);
		return tag;
	}
	tag->Add(ns.sheet(), ods::style::kDisplay);
	tag->Add(ns.style(), ods::style::kWritingMode);
	return nullptr;
}

ods::Tag*
SheetRowProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::SheetRowProps);
		tag->attr_set(ns.style(), ods::style::kSheetRowProps);
		return tag;
	}
	tag->Add(ns.fo(), ods::style::kBreakBefore);
	tag->Add(ns.style(), ods::style::kRowHeight);
	tag->Add(ns.style(), ods::style::kUseOptimalRowHeight);
	
	return nullptr;
}

ods::Tag*
Style(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::Style);
		tag->attr_set(ns.style(), ods::ns::kStyle);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kFamily);
	tag->Add(ns.style(), ods::ns::kName);
	tag->Add(ns.style(), ods::style::kParentStyleName);
	tag->Add(ns.style(), ods::style::kDataStyleName);
	tag->SubfuncAdd(ods::style::tag::Map);
	tag->SubfuncAdd(ods::style::tag::TextProps);
	tag->SubfuncAdd(ods::style::tag::ParagraphProps);
	tag->SubfuncAdd(ods::style::tag::SheetCellProps);
	tag->SubfuncAdd(ods::style::tag::SheetColumnProps);
	tag->SubfuncAdd(ods::style::tag::GraphicProps);
	return nullptr;
}

ods::Tag*
StyleFooter(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::StyleFooter);
		tag->attr_set(ns.style(), ods::style::kFooter);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::TextP);
	return nullptr;
}

ods::Tag*
StyleFooterLeft(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::StyleFooterLeft);
		tag->attr_set(ns.style(), ods::style::kFooterLeft);
		return tag;
	}
	tag->Add(ns.style(), ods::style::kDisplay);
	return nullptr;
}

ods::Tag*
StyleHeader(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::StyleHeader);
		tag->attr_set(ns.style(), ods::style::kHeader);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::RegionLeft);
	tag->SubfuncAdd(ods::style::tag::RegionRight);
	return nullptr;
}

ods::Tag*
StyleHeaderLeft(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::StyleHeaderLeft);
		tag->attr_set(ns.style(), ods::style::kHeaderLeft);
		return tag;
	}
	tag->Add(ns.style(), ods::style::kDisplay);
	return nullptr;
}

ods::Tag*
Styles(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::Styles);
		tag->attr_set(ns.office(), ods::style::kStyles);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::DefaultStyle);
	tag->SubfuncAdd(ods::style::tag::NumberCurrencyStyle);
	tag->SubfuncAdd(ods::style::tag::NumberStyle);
	tag->SubfuncAdd(ods::style::tag::Style);
	return nullptr;
}

ods::Tag*
TextProps(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::style::tag::TextProps);
		tag->attr_set(ns.style(), ods::style::kTextProps);
		return tag;
	}
	tag->Add(ns.fo(), ods::style::kColor);
	tag->Add(ns.fo(), ods::ns::kCountry);
	tag->Add(ns.style(), ods::ns::kCountryAsian);
	tag->Add(ns.style(), ods::ns::kCountryComplex);
	tag->Add(ns.style(), ods::style::kFontFamilyComplex);
	tag->Add(ns.style(), ods::style::kFontFamilyGenericComplex);
	tag->Add(ns.style(), ods::style::kFontName);
	tag->Add(ns.style(), ods::style::kFontNameAsian);
	tag->Add(ns.style(), ods::style::kFontNameComplex);
	tag->Add(ns.style(), ods::style::kFontPitchComplex);
	tag->Add(ns.fo(), ods::style::kFontSize);
	tag->Add(ns.fo(), ods::style::kFontStyle);
	tag->Add(ns.fo(), ods::style::kFontWeight);
	tag->Add(ns.fo(), ods::ns::kLanguage);
	tag->Add(ns.style(), ods::ns::kLanguageComplex);
	tag->Add(ns.style(), ods::ns::kLanguageAsian);
	tag->Add(ns.style(), ods::style::kTextUnderlineColor);
	tag->Add(ns.style(), ods::style::kTextUnderlineStyle);
	tag->Add(ns.style(), ods::style::kTextUnderlineWidth);
	return nullptr;
}

} // ods::style::tag::
} // ods::style::
} // ods::
