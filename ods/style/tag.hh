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

#ifndef ODS_STYLE_TAG_HH_
#define ODS_STYLE_TAG_HH_

#include "../global.hxx"

namespace ods		{ // ods::
class Ns;
class Tag;
namespace style		{ // ods::style::
namespace tag		{ // ods::style::tag::

ODS_API ods::Tag*	AutomaticStyles(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	DefaultStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	FooterStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	FontFace(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	FontFaceDecls(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	GraphicProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	HeaderFooterProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	HeaderStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Map(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	MasterPage(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	MasterStyles(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberCurrencyStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	NumberStyle(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	OfficeDocStyles(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	PageLayout(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	PageLayoutProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	ParagraphProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	RegionLeft(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	RegionRight(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetCellProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetColumnProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	SheetRowProps(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Style(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	StyleFooter(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	StyleFooterLeft(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	StyleHeader(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	StyleHeaderLeft(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	StyleRegionLeft(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	Styles(ods::Ns&, ods::Tag*);
ODS_API ods::Tag*	TextProps(ods::Ns&, ods::Tag*);

} // ods::style::tag::
} // ods::style::
} // ods::

#endif
