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

#ifndef ODS_STYLE_HPP_
#define ODS_STYLE_HPP_

#include "decl.hxx"
#include "err.hpp"
#include "global.hxx"
#include "ods.hxx"
#include "tag.hxx"
#include <QColor>

namespace ods	{ // ods::

namespace style	{ // ods::style::
class Border;
class StyleFamily;
} // ods::style::

class ODS_API Style
{
public:
	Style(ods::Book*, ods::Tag*, ods::style::StyleFamily*,
		const ods::StylePlace);
	virtual ~Style();
	
	ods::Style*
	Derive(const ods::StylePlace place = ods::StylePlace::NotSet);
	
	const QString&
	font_name() const { return font_name_; }
	
	double
	font_size() const { return font_size_; }
	
	void
	font_size_set(const double d) { font_size_ = d; }
	
	double
	FontSizeInInches();
	
	ods::FontSizeType
	font_size_type() const { return font_size_type_; }
	
	void
	font_size_type_set(const ods::FontSizeType t) { font_size_type_ = t; }
	
	ods::PercentStyle*
	GetPercentStyle();
	
	ods::Tag*
	GetTag(ods::tag::func f);
	
	const QString&
	name() { return name_; }
	
	ods::Style*
	parent_style() const { return parent_style_; }
	
	void
	SetBackgroundColor(const QColor&);
	
	void
	SetBold(const bool flag);
	
	void
	SetBorder(ods::style::Border*);
	
	void
	SetFontName(const QString &font_name);
	
	void
	SetFontSize(const float size,
		const ods::FontSizeType size_type = ods::FontSizeType::Pt);
	
	void
	SetFontStyle(const ods::FontStyle);
	
	void
	SetFontWeight(const ods::FontWeight);
	
	void
	SetHAlignment(const ods::HAlign a);
	
	void
	SetItalic(const bool flag);
	
	void
	SetOptimalRowHeight(const double, const ods::FontSizeType);
	
	void
	SetParentStyle(ods::Style*);
	
	void
	SetPercentStyle(ods::PercentStyle*);
	
	void
	SetTextColor(const QColor &color);
	
	void
	SetVAlignment(const ods::VAlign a);
	
	ods::style::StyleFamily*
	style_family() const { return style_family_; }
	
	ods::Tag*
	tag() const { return tag_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Style);
	
	void
	Init();
	
	void
	SetUniqueName();
	
	QColor					background_color_;
	ods::Book				*book_ = nullptr;
	QString					font_name_;
	double					font_size_ = -1.0;
	ods::FontSizeType		font_size_type_ = ods::FontSizeType::NotSet;
	QString					name_;
	ods::Style				*parent_style_ = nullptr;
	ods::PercentStyle		*percent_style_ = nullptr;
	ods::StylePlace			place_;
	ods::style::StyleFamily	*style_family_ = nullptr;
	ods::Tag				*tag_ = nullptr;
	QColor					text_color_;
};

} // ods::

#endif
