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

#ifndef ODS_DRAW_FRAME_HPP_
#define ODS_DRAW_FRAME_HPP_

#include "err.hpp"
#include "global.hxx"
#include "ods.hxx"
#include "tag.hxx"
#include <QFile>
#include <QPoint>
#include <QSize>


namespace ods	{ // ods::

class Cell;
class Prefix;
class Tag;

class ODS_API DrawFrame
{
public:
	DrawFrame(ods::Cell*, const QFile&);
	virtual ~DrawFrame();
	
	ods::Cell*
	cell() const { return cell_; }
	
	bool
	CopyFrom(const QFile &from);
	
	const QSize&
	current_image_size() const { return current_image_size_; }
	
	QFile&
	file() { return file_; }
	
	QString
	GetRelativeUri();
	
	const QString&
	id() { return id_; }
	
	void
	id_set(const QString &s) { id_ = s; }
	
	const QString&
	mime_type() { return mime_type_; }
	
	const QPoint&
	offset() const { return offset_; }
	
	bool
	ok() const { return state_ == ods::State::Ok; }
	
	const QSize&
	real_image_size() const { return real_image_size_; }
	
	void
	SetOffset(const QPoint &p);
	
	void
	SetSize(const QSize &size);
	
	ods::State
	state() const { return state_; }
	
	int
	zindex() const { return zindex_; }
	
	void
	zindex_set(const int n) { zindex_ = n; }

private:
	NO_ASSIGN_COPY_MOVE(DrawFrame);
	
	ods::Tag*
	GetTag(ods::tag::func);
	
	void
	Init(const QFile&);
	
	void
	UpdateTag();
	
	ods::Cell	*cell_ = nullptr;
	QSize		current_image_size_;
	QFile		file_;
	QString		file_name_;
	QString		id_;
	int			img_width_ = -1;
	int			img_height = -1;
	QString		mime_type_;
	QPoint		offset_;
	QSize		real_image_size_;
	ods::State	state_ = ods::State::Ok;
	ods::Tag	*tag_ = nullptr;
	int			zindex_ = -1;
};

} // ods::

#endif
