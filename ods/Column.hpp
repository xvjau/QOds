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

#ifndef ODS_COLUMN_HPP_
#define ODS_COLUMN_HPP_

#include "global.hxx"
#include "err.hpp"

namespace ods	{ // ods::

class Ns;
class Sheet;
class Style;
class Tag;

class ODS_API Column
{
public:
	Column(ods::Sheet *sheet, ods::Tag*);
	virtual ~Column();
	
	qint32
	column_count() const { return column_count_; }
	
	void
	SetNumColsRepeated(const qint32 num);
	
	ods::Sheet*
	sheet() const { return sheet_; }
	
	void
	SetStyle(ods::Style*);
	
	ods::Tag*
	tag() const { return tag_; }

private:
	NO_ASSIGN_COPY_MOVE(Column);
	
	void
	Init();
	
	qint32		column_count_ = -1;
	ods::Sheet	*sheet_ = nullptr;
	ods::Style	*style_ = nullptr;
	ods::Tag	*tag_ = nullptr;
};

} // ods::

#endif
