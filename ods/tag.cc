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
#include "Ns.hpp"
#include "style/style.hxx"
#include "style/tag.hh"
#include "Tag.hpp"

#include <mtl/err.hpp>

namespace ods	{ // ods::
namespace tag	{ // ods::tag::

ods::Tag*
BackgroundImage(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::BackgroundImage);
		tag->attr_set(ns.style(), ods::style::kBackgroundImage);
		return tag;
	}
	tag->Add(ns.draw(), ods::style::kOpacity);
	return nullptr;
}

ods::Tag*
CalculationSettings(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::tag::CalculationSettings);
		tag->attr_set(ns.sheet(), ods::ns::kCalculationSettings);
		return tag;
	}
	tag->Add(ns.sheet(), ods::ns::kCaseSensitive);
	tag->Add(ns.sheet(), ods::ns::kSearchWholeCell);
	tag->Add(ns.sheet(), ods::ns::kUseWildcards);
	tag->Add(ns.sheet(), ods::ns::kUseRegularExpressions);
	tag->Add(ns.sheet(), ods::ns::kAutomaticFindLabels);
	return nullptr;
}

ods::Tag*
ConfigItem(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ConfigItem);
		tag->attr_set(ns.config(), ods::ns::kConfigItem);
		return tag;
	}
	
	tag->Add(ns.config(), ods::ns::kName);
	tag->Add(ns.config(), ods::ns::kType);
	return nullptr;
}

ods::Tag*
ConfigItemMapEntry(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ConfigItemMapEntry);
		tag->attr_set(ns.config(), ods::ns::kConfigItemMapEntry);
		return tag;
	}
	tag->Add(ns.config(), ods::ns::kName);
	tag->SubfuncAdd(ods::tag::ConfigItem);
	tag->SubfuncAdd(ods::tag::ConfigItemMapNamed);
	return nullptr;
}

ods::Tag*
ConfigItemMapIndexed(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ConfigItemMapIndexed);
		tag->attr_set(ns.config(), ods::ns::kConfigItemMapIndexed);
		return tag;
	}
	tag->Add(ns.config(), ods::ns::kName);
	tag->SubfuncAdd(ods::tag::ConfigItemMapEntry);
	return nullptr;
}

ods::Tag*
ConfigItemMapNamed(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ConfigItemMapNamed);
		tag->attr_set(ns.config(), ods::ns::kConfigItemMapNamed);
		return tag;
	}
	tag->Add(ns.config(), ods::ns::kName);
	tag->SubfuncAdd(ods::tag::ConfigItemMapEntry);
	return nullptr;
}

ods::Tag*
ConfigItemSet(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ConfigItemSet);
		tag->attr_set(ns.config(), ods::ns::kConfigItemSet);
		return tag;
	}
	
	tag->Add(ns.config(), ods::ns::kName);
	tag->SubfuncAdd(ods::tag::ConfigItem);
	tag->SubfuncAdd(ods::tag::ConfigItemMapIndexed);
	return nullptr;
}

ods::Tag*
CoveredSheetCell(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::CoveredSheetCell);
		tag->attr_set(ns.sheet(), ods::ns::kCoveredSheetCell);
		return tag;
	}
	tag->Add(ns.sheet(), ods::ns::kFormula);
	tag->Add(ns.sheet(), ods::ns::kNumColsRepeated);
	tag->Add(ns.sheet(), ods::ns::kNumColsSpanned);
	tag->Add(ns.sheet(), ods::ns::kNumRowsSpanned);
	tag->Add(ns.sheet(), ods::style::kStyleName);
	tag->Add(ns.office(), ods::ns::kValue);
	tag->Add(ns.office(), ods::ns::kValueType);
	tag->SubfuncAdd(ods::tag::TextP);
	return nullptr;
}

ods::Tag*
CurrencySymbol(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::CurrencySymbol);
		tag->attr_set(ns.number(), ods::ns::kCurrencySymbol);
		return tag;
	}
	tag->Add(ns.number(), ods::ns::kCountry);
	tag->Add(ns.number(), ods::ns::kLanguage);
	return nullptr;
}

ods::Tag*
DcCreator(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::DcCreator);
		tag->attr_set(ns.dc(), ods::ns::kCreator);
		return tag;
	}
	return nullptr;
}

ods::Tag*
DcDate(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::DcDate);
		tag->attr_set(ns.dc(), ods::ns::kDate);
		return tag;
	}
	return nullptr;
}

ods::Tag*
DrawFrame(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::tag::DrawFrame);
		tag->attr_set(ns.draw(), ods::ns::kFrame);
		return tag;
	}
	tag->Add(ns.draw(), ods::style::kZIndex);
	tag->Add(ns.draw(), ods::ns::kId);
	tag->Add(ns.draw(), ods::style::kStyleName);
	tag->Add(ns.draw(), ods::ns::kName);
	tag->Add(ns.svg(), ods::ns::kX);
	tag->Add(ns.svg(), ods::ns::kY);
	tag->Add(ns.svg(), ods::style::kHeight);
	tag->Add(ns.svg(), ods::style::kWidth);
	tag->SubfuncAdd(ods::tag::DrawImage);
	tag->SubfuncAdd(ods::tag::SvgDesc);
	tag->SubfuncAdd(ods::tag::SvgTitle);
	return nullptr;
}

ods::Tag*
DrawImage(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::tag::DrawImage);
		tag->attr_set(ns.draw(), ods::style::kImage);
		return tag;
	}
	tag->Add(ns.xlink(), ods::ns::kHref);
	tag->Add(ns.xlink(), ods::ns::kType);
	tag->Add(ns.xlink(), ods::ns::kShow);
	tag->Add(ns.xlink(), ods::ns::kActuate);
	return nullptr;
}

ods::Tag*
Manifest(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::Manifest);
		tag->attr_set(ns.manifest(), ods::ns::kManifest);
		tag->SetPrintXmlns(true);
		return tag;
	}
	
	tag->SubfuncAdd(ods::tag::ManifestFileEntry);
	return nullptr;
}

ods::Tag*
ManifestFileEntry(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::ManifestFileEntry);
		tag->attr_set(ns.manifest(), ods::ns::kFileEntry);
		return tag;
	}
	tag->Add(ns.manifest(), ods::ns::kFullPath);
	tag->Add(ns.manifest(), ods::ns::kMediaType);
	tag->Add(ns.manifest(), ods::ns::kVersion);
	return nullptr;
}

ods::Tag*
Number(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::Number);
		tag->attr_set(ns.number(), ods::ns::kNumber);
		return tag;
	}
	tag->Add(ns.number(), ods::ns::kDecimalPlaces);
	tag->Add(ns.number(), ods::ns::kMinIntegerDigits);
	tag->Add(ns.number(), ods::ns::kGrouping);
	tag->SubfuncAdd(ods::tag::Number);
	return nullptr;
}

ods::Tag*
NumberText(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::NumberText);
		tag->attr_set(ns.number(), ods::ns::kText);
		return tag;
	}
	return nullptr;
}

ods::Tag*
OfficeBody(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::OfficeBody);
		tag->attr_set(ns.office(), ods::ns::kBody);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::OfficeSpreadsheet);
	return nullptr;
}

ods::Tag*
OfficeDocContent(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::OfficeDocContent);
		tag->attr_set(ns.office(), ods::ns::kDocContent);
		tag->SetPrintXmlns(true);
		return tag;
	}
	tag->SubfuncAdd(ods::style::tag::AutomaticStyles);
	tag->SubfuncAdd(ods::style::tag::FontFaceDecls);
	tag->SubfuncAdd(ods::tag::OfficeBody);
	return nullptr;
}

ods::Tag*
OfficeDocSettings(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::OfficeDocSettings);
		tag->attr_set(ns.office(), ods::ns::kDocSettings);
		tag->SetPrintXmlns(true);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::OfficeSettings);
	return nullptr;
}

ods::Tag*
OfficeSettings(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::OfficeSettings);
		tag->attr_set(ns.office(), ods::ns::kSettings);
		return tag;
	}
	
	tag->SubfuncAdd(ods::tag::ConfigItemSet);
	return nullptr;
}

ods::Tag*
OfficeSpreadsheet(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::OfficeSpreadsheet);
		tag->attr_set(ns.office(), ods::ns::kSpreadsheet);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::CalculationSettings);
	tag->SubfuncAdd(ods::tag::Sheet);
	return nullptr;
}

ods::Tag*
Sheet(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::Sheet);
		tag->attr_set(ns.sheet(), ods::ns::kSheet);
		return tag;
	}
	// sheet column must be first to be written first in XML, before the rows.
	tag->SubfuncAdd(ods::tag::SheetColumn);
	tag->Add(ns.sheet(), ods::ns::kName);
	tag->Add(ns.sheet(), ods::style::kStyleName);
	tag->SubfuncAdd(ods::tag::SheetRow);
	return nullptr;
}

ods::Tag*
SheetCell(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::SheetCell);
		tag->attr_set(ns.sheet(), ods::ns::kSheetCell);
		return tag;
	}
	tag->Add(ns.sheet(), ods::ns::kFormula);
	tag->Add(ns.sheet(), ods::ns::kNumColsRepeated);
	tag->Add(ns.sheet(), ods::ns::kNumColsSpanned);
	tag->Add(ns.sheet(), ods::ns::kNumRowsSpanned);
	tag->Add(ns.sheet(), ods::style::kStyleName);
	tag->Add(ns.office(), ods::ns::kValue);
	tag->Add(ns.office(), ods::ns::kValueType);
	tag->SubfuncAdd(ods::tag::TextP);
	return nullptr;
}

ods::Tag*
SheetColumn(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::SheetColumn);
		tag->attr_set(ns.sheet(), ods::ns::kSheetColumn);
		return tag;
	}
	tag->Add(ns.sheet(), ods::style::kStyleName);
	tag->Add(ns.sheet(), ods::ns::kNumColsRepeated);
	tag->Add(ns.sheet(), ods::ns::kDefaultCellStyleName);
	return nullptr;
}

ods::Tag*
SheetRow(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::SheetRow);
		tag->attr_set(ns.sheet(), ods::ns::kSheetRow);
		return tag;
	}
	tag->Add(ns.sheet(), ods::ns::kNumRowsRepeated);
	tag->Add(ns.sheet(), ods::style::kStyleName);
	tag->SubfuncAdd(ods::tag::SheetCell);
	tag->SubfuncAdd(ods::tag::CoveredSheetCell);
	return nullptr;
}

ods::Tag*
SvgDesc(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::tag::SvgDesc);
		tag->attr_set(ns.svg(), ods::ns::kDesc);
		return tag;
	}
	return nullptr;
}

ods::Tag*
SvgTitle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr)
	{
		tag = new ods::Tag(ns, ods::tag::SvgTitle);
		tag->attr_set(ns.svg(), ods::ns::kTitle);
		return tag;
	}
	return nullptr;
}

ods::Tag*
TextDate(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextDate);
		tag->attr_set(ns.text(), ods::ns::kDate);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kDataStyleName);
	tag->Add(ns.text(), ods::ns::kDateValue);
	return nullptr;
}

ods::Tag*
TextP(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextP);
		tag->attr_set(ns.text(), ods::ns::kP);
		return tag;
	}
	tag->SubfuncAdd(ods::tag::TextDate);
	tag->SubfuncAdd(ods::tag::TextPageCount);
	tag->SubfuncAdd(ods::tag::TextPageNumber);
	tag->SubfuncAdd(ods::tag::TextSheetName);
	tag->SubfuncAdd(ods::tag::TextTime);
	tag->SubfuncAdd(ods::tag::TextTitle);
	return nullptr;
}

ods::Tag*
TextPageCount(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextPageCount);
		tag->attr_set(ns.text(), ods::ns::kPageCount);
		return tag;
	}
	return tag;
}

ods::Tag*
TextPageNumber(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextPageNumber);
		tag->attr_set(ns.text(), ods::ns::kPageNumber);
		return tag;
	}
	
	return nullptr;
}

ods::Tag*
TextSheetName(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextSheetName);
		tag->attr_set(ns.text(), ods::style::kSheetName);
		return tag;
	}
	return nullptr;
}

ods::Tag*
TextTime(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextTime);
		tag->attr_set(ns.text(), ods::ns::kTime);
		return tag;
	}
	tag->Add(ns.style(), ods::ns::kDataStyleName);
	tag->Add(ns.text(), ods::ns::kTimeValue);
	return nullptr;
}

ods::Tag*
TextTitle(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::tag::TextTitle);
		tag->attr_set(ns.text(), ods::ns::kTitle);
		return tag;
	}
	return nullptr;
}

} // ods::tag::
} // ods::


