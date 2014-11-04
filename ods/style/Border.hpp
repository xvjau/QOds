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

#ifndef ODS_STYLE_BORDER_HPP_
#define ODS_STYLE_BORDER_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"
#include <QColor>

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API Border
{
public:
	Border();
	virtual ~Border();
	
	ods::style::Border*
	Derive();
	
	void
	SetColor(const QColor c) { color_ = c.name(QColor::HexRgb); }
	
	quint8
	sides() const { return sides_; }
	
	void
	sides_set(const quint8 bits) { sides_ = bits; }
	
	void
	SetStyle(const ods::BorderStyle s);
	
	void
	SetWidth(const ods::BorderWidth);
	
	void
	SetWidth(const QString &w) { width_ = w; }
	
	QString
	toString();
	
protected:
	void
	CopyTo(ods::style::Border*);
	
	void
	SetColor(const QString &c) { color_ = c; }
	
	void
	SetStyle(const QString &style) { border_style_ = style; }

private:
	NO_ASSIGN_COPY_MOVE(Border);
	
	quint8			sides_ = ods::BorderSideAll;
	QString			border_style_;
	QString			color_;
	bool			is_none_ = false;
	QString			width_;
};

} // ods::style::
} // ods::

#endif
