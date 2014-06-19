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

#ifndef ODS_TAG_HH_
#define ODS_TAG_HH_

#include "dso.hxx"

namespace ods	{ // ods::
class Ns;
class Tag;
namespace tag	{ // ods::tag::

ODS_DSO_SHARE ods::Tag*	BackgroundImage(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	CalculationSettings(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ConfigItem(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ConfigItemMapEntry(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ConfigItemMapIndexed(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ConfigItemMapNamed(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ConfigItemSet(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	CoveredSheetCell(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	CurrencySymbol(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	DcCreator(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	DcDate(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	DrawFrame(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	DrawImage(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	Manifest(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	ManifestFileEntry(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	Number(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	NumberText(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	OfficeBody(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	OfficeDocContent(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	OfficeDocSettings(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	OfficeSettings(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	OfficeSpreadsheet(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	Sheet(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	SheetCell(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	SheetColumn(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	SheetRow(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	SvgDesc(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	SvgTitle(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextDate(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextP(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextPageCount(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextPageNumber(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextSheetName(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextTime(ods::Ns&, ods::Tag*);
ODS_DSO_SHARE ods::Tag*	TextTitle(ods::Ns&, ods::Tag*);

} // ods::tag::
} // ods::
#endif

