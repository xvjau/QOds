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

#ifndef ODS_STYLE_STYLEFAMILY_HPP_
#define ODS_STYLE_STYLEFAMILY_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API StyleFamily
{
public:
	StyleFamily(const ods::StyleFamilyId);
	virtual ~StyleFamily();
	
	bool
	IsCell() const { return id_ == ods::StyleFamilyId::Cell; }
	
	bool
	IsColumn() const { return id_ == ods::StyleFamilyId::Column; }
	
	bool
	IsRow() const { return id_ == ods::StyleFamilyId::Row; }
	
	bool
	IsSheet() const { return id_ == ods::StyleFamilyId::Sheet; }
	
	ods::StyleFamilyId
	id() { return id_; }
	
	QString
	toString();

private:
	NO_ASSIGN_COPY_MOVE(StyleFamily);
	
	ods::StyleFamilyId		id_;
};

} // ods::style::
} // ods::

#endif
