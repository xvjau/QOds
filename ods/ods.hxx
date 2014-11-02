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

#ifndef ODS_ODS_HXX_ 
#define ODS_ODS_HXX_

#include "global.hxx"
#include <QtGlobal>
#include <QString>

namespace ods	{ // ods::

static const auto kFormulaPrefix	= QStringLiteral("of:=");
static const auto kSpace			= QStringLiteral(" ");
static const double kInchesInAPoint	= 0.01388888889;
static const double kPointsInAInch	= 72.0;
static const double kCmInAPoint		= 0.0352777778;
static const double kPointsInACm	= 28.3464567;
static const double kInchesInACm	= 0.393701;
static const double kCmInAnInch		= 2.54;

enum class State : quint8
{
	Ok,
	Fail, // failed for unknown reason
	FailAccess,
	FailCopy,
	FileTooLarge
};

enum class StyleFamilyId : quint8
{
	Cell,
	Column,
	Row,
	Sheet
};

enum class StylePlace : quint8
{
	StylesFile,
	ContentFile,
	NotSet
};

const quint8 BorderSideLeft		= 1;
const quint8 BorderSideTop		= 2;
const quint8 BorderSideRight	= 4;
const quint8 BorderSideBottom	= 8;
const quint8 BorderSideAll		= 
	BorderSideLeft | BorderSideTop | BorderSideRight | BorderSideBottom;

enum class BorderStyle : quint8
{
	Dashed,
	Dotted,
	Double,
	Inset,
	None,
	Outset,
	Solid
};

enum class BorderWidth : quint8
{
	Medium,
	Thick,
	Thin
};

enum class FontSizeType : quint8
{
	Pt,
	In,
	Cm,
	NotSet
};

enum class FontStyle : quint8
{
	Normal,
	Italic,
	Oblique
};

enum class FontWeight : quint8
{
	Normal,
	Bold,
	N100,
	N200,
	N300,
	N400,
	N500,
	N600,
	N700,
	N800,
	N900
};

enum class Grouping : quint8
{
	Open,
	Close
};

enum class HAlign : quint8
{
	Left,
	Center,
	Right
};

enum class VAlign : quint8
{
	Top,
	Middle,
	Bottom
};

enum class Op : quint8
{
	None,
	Add,
	Subtract,
	Mult,
	Divide,
	Subroute,
	Cell,
	Fail
};

enum class Type : quint8
{
	Bool = 2,
	Currency,
	Date,
	Double,
	Fail, // default
	NotSet,
	Percentage,
	Time,
	String
};

struct Version
{
	qint32 major = -1;
	qint32 minor = -1;
	qint32 micro = -1;
	qint32 patch = -1;
};

enum class UriId : quint8
{
	Animation = 0,
	Calcext,
	Chart,
	Config,
	Database,
	Dc,
	Dr3,
	Draw,
	Fo,
	Form,
	Manifest,
	Math,
	Meta,
	Number,
	Of,
	Office,
	Presentation,
	Script,
	Sheet,
	Smil,
	Style,
	Svg,
	Text,
	Xlink
};

struct Uri
{
	ods::UriId			id;
	const char * const	str;
};

const Uri kAnimationUri { ods::UriId::Animation,
	"urn:oasis:names:tc:opendocument:xmlns:animation:1.0" };
const Uri kCalcextUri { ods::UriId::Calcext,
	"urn:org:documentfoundation:names:experimental:calc:" };
const Uri kChartUri { ods::UriId::Chart,
	"urn:oasis:names:tc:opendocument:xmlns:chart:1.0" };
const Uri kConfigUri { ods::UriId::Config,
	"urn:oasis:names:tc:opendocument:xmlns:config:1.0" };
const Uri kDatabaseUri { ods::UriId::Database,
	"urn:oasis:names:tc:opendocument:xmlns:database:1.0" };
const Uri kDcUri { ods::UriId::Dc,
	"http://purl.org/dc/elements/1.1/" };
const Uri kDrawUri { ods::UriId::Draw,
	"urn:oasis:names:tc:opendocument:xmlns:drawing:1.0" };
const Uri kFoUri { ods::UriId::Fo,
	"urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0" };
const Uri kFormUri { ods::UriId::Form,
	"urn:oasis:names:tc:opendocument:xmlns:form:1.0" };
const Uri kManifestUri { ods::UriId::Manifest,
	"urn:oasis:names:tc:opendocument:xmlns:manifest:1.0" };
const Uri kMathUri { ods::UriId::Math,
	"http://www.w3.org/1998/Math/MathML" };
const Uri kMetaUri { ods::UriId::Meta,
	"urn:oasis:names:tc:opendocument:xmlns:meta:1.0" };
const Uri kNumberUri { ods::UriId::Number,
	"urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0" };
const Uri kOfUri { ods::UriId::Of,
	"urn:oasis:names:tc:opendocument:xmlns:of:1.2" };
const Uri kOfficeUri { ods::UriId::Office,
	"urn:oasis:names:tc:opendocument:xmlns:office:1.0" };
const Uri kPresentationUri { ods::UriId::Presentation,
	"urn:oasis:names:tc:opendocument:xmlns:presentation:1.0" };
const Uri kScriptUri { ods::UriId::Script,
	"urn:oasis:names:tc:opendocument:xmlns:script:1.0" };
const Uri kSheetUri { ods::UriId::Sheet,
	"urn:oasis:names:tc:opendocument:xmlns:table:1.0" };
const Uri kSmilUri { ods::UriId::Smil,
	"urn:oasis:names:tc:opendocument:xmlns:smil-compatible:1.0" };
const Uri kStyleUri { ods::UriId::Style,
	"urn:oasis:names:tc:opendocument:xmlns:style:1.0" };
const Uri kSvgUri { ods::UriId::Svg,
	"urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0" };
const Uri kTextUri { ods::UriId::Text,
	"urn:oasis:names:tc:opendocument:xmlns:text:1.0" };
const Uri kXlinkUri { ods::UriId::Xlink,
	"http://www.w3.org/1999/xlink" };

} // ods::

#endif

