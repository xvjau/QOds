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

#ifndef ODS_STYLE_HXX_
#define ODS_STYLE_HXX_

#ifndef ods_const
#define ods_const const char * const
#endif

namespace ods	{ // ods::
namespace style	{ // ods::style::

ods_const kApplyStyleName		= "apply-style-name";
ods_const kAutomaticStyles		= "automatic-styles";
ods_const kBackgroundColor		= "background-color";
ods_const kBackgroundImage		= "background-image";
ods_const kBaseCellAddress		= "base-cell-address";
ods_const kBlue					= "blue";
ods_const kBold					= "bold";
ods_const kBorder				= "border";
ods_const kBorderBottom			= "border-bottom";
ods_const kBorderLeft			= "border-left";
ods_const kBorderRight			= "border-right";
ods_const kBorderTop			= "border-top";
ods_const kBreakBefore			= "break-before";
ods_const kClip					= "clip";
ods_const kColor				= "color";
ods_const kColorMode			= "color-mode";
ods_const kColumnWidth			= "column-width";
ods_const kCondition			= "condition";
ods_const kContrast				= "contrast";
ods_const kCurrencyStyle		= "currency-style";
ods_const kDataStyleName		= "data-style-name";
ods_const kDefaultStyle			= "default-style";
ods_const kDefaultCellStyleName	= "default-cell-style-name";
ods_const kDisplay				= "display";
ods_const kFill					= "fill";
ods_const kFontFace				= "font-face";
ods_const kFontFaceDecls		= "font-face-decls";
ods_const kFontFamily			= "font-family";
ods_const kFontFamilyAsian		= "font-family-asian";
ods_const kFontFamilyComplex	= "font-family-complex";
ods_const kFontFamilyGeneric	= "font-family-generic";
ods_const kFontFamilyGenericAsian	= "font-family-generic-complex";
ods_const kFontFamilyGenericComplex = "font-family-generic-complex";
ods_const kFontName				= "font-name";
ods_const kFontNameAsian		= "font-name-asian";
ods_const kFontNameComplex		= "font-name-complex";
ods_const kFontPitch			= "font-pitch";
ods_const kFontPitchAsian		= "font-pitch-asian";
ods_const kFontPitchComplex		= "font-pitch-complex";
ods_const kFontSize				= "font-size";
ods_const kFontSizeAsian		= "font-size-asian";
ods_const kFontSizeComplex		= "font-size-complex";
ods_const kFontStyle			= "font-style"; // e.g. "italic"
ods_const kFontStyleAsian		= "font-style-asian";
ods_const kFontStyleComplex		= "font-style-complex";
ods_const kFontWeight			= "font-weight"; // e.g. "bold"
ods_const kFontWeightAsian		= "font-weight-asian";
ods_const kFontWeightComplex	= "font-weight-complex";
ods_const kFooter				= "footer";
ods_const kFooterLeft			= "footer-left";
ods_const kFooterStyle			= "footer-style";
ods_const kGamma				= "gamma";
ods_const kGraphicProps			= "graphic-properties";
ods_const kGreen				= "green";
ods_const kHeader				= "header";
ods_const kHeaderFooterProps	= "header-footer-properties";
ods_const kHeaderLeft			= "header-left";
ods_const kHeaderStyle			= "header-style";
ods_const kHeight				= "height";
ods_const kImage				= "image";
ods_const kImageOpacity			= "image-opacity";
ods_const kItalic				= "italic";
ods_const kLuminance			= "luminance";
ods_const kMarginLeft			= "margin-left";
ods_const kMarginRight			= "margin-right";
ods_const kMarginBottom			= "margin-bottom";
ods_const kMarginTop			= "margin-top";
ods_const kMasterPage			= "master-page";
ods_const kMasterStyles			= "master-styles";
ods_const kMinHeight			= "min-height";
ods_const kMirror				= "mirror";
ods_const kN100					= "100";
ods_const kN200					= "200";
ods_const kN300					= "300";
ods_const kN400					= "400";
ods_const kN500					= "500";
ods_const kN600					= "600";
ods_const kN700					= "700";
ods_const kN800					= "800";
ods_const kN900					= "900";
ods_const kNormal				= "normal";
ods_const kNumberStyle			= "number-style";
ods_const kOblique				= "oblique";
ods_const kOpacity				= "opacity";
ods_const kPadding				= "padding";
ods_const kPageLayout			= "page-layout";
ods_const kPageLayoutName		= "page-layout-name";
ods_const kPageLayoutProps		= "page-layout-properties";
ods_const kParagraphProps		= "paragraph-properties";
ods_const kParentStyleName		= "parent-style-name";
ods_const kRed					= "red";
ods_const kRegionLeft			= "region-left";
ods_const kRegionRight			= "region-right";
ods_const kRelHeight			= "rel-height";
ods_const kRelWidth				= "rel-width";
ods_const kRepeatContent		= "repeat-content";
ods_const kRotationAngle		= "rotation-angle";
ods_const kRowHeight			= "row-height";
ods_const kSheetName			= "sheet-name"; //<text:sheet-name>
ods_const kSheetRowProps		= "table-row-properties";
ods_const kStroke				= "stroke";
ods_const kStyleName			= "style-name";
ods_const kStyles				= "styles";
ods_const kSheetCellProps		= "table-cell-properties";
ods_const kSheetColumnProps		= "table-column-properties";
ods_const kSheetProps			= "table-properties";
ods_const kTabStopDistance		= "tab-stop-distance";
ods_const kTextAlign			= "text-align";
ods_const kTextAlignSource		= "text-align-source";
ods_const kTextAreaHorizAlign	= "textarea-horizontal-align";
ods_const kTextAreaVertAlign	= "textarea-vertical-align";
ods_const kTextProps			= "text-properties";
ods_const kTextUnderlineColor	= "text-underline-color";
ods_const kTextUnderlineStyle	= "text-underline-style";
ods_const kTextUnderlineWidth	= "text-underline-width";
ods_const kUseOptimalRowHeight	= "use-optimal-row-height";
ods_const kVerticalAlign		= "vertical-align";
ods_const kWidth				= "width";
ods_const kWritingMode			= "writing-mode";
ods_const kWritingModeLrtb		= "lr-tb";
ods_const kZIndex				= "z-index";

} // ods::style::
} // ods::

#endif
