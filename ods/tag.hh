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

#include "global.hxx"

namespace ods	{ // ods::
class Ns;
class Tag;
namespace tag	{ // ods::tag::

namespace bits	{ // ods::tag::bits::

const quint8
	HasTextP	= 1,
	Used		= 2,
	XmlNs		= 4;
} // ods::tag::bits::

ODS_API ods::Tag*	BackgroundImage(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CalculationSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItem(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapEntry(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapIndexed(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemMapNamed(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ConfigItemSet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CoveredSheetCell(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	CurrencySymbol(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DcCreator(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DcDate(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DrawFrame(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DrawImage(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Manifest(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ManifestFileEntry(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Number(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberPercentageStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberText(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeBody(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeDocContent(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeDocSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeSettings(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeSpreadsheet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Sheet(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetCell(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetColumn(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetRow(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SvgDesc(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SvgTitle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextDate(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextP(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextPageCount(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextPageNumber(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextSheetName(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextTime(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextTitle(ods::Ns&, ods::Tag*);

} // ods::tag::
} // ods::
#endif

