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

#ifndef ODS_META_HPP_
#define ODS_META_HPP_

#include "err.hpp"
#include "global.hxx"
#include "Duration.hpp"
#include <QDateTime>
#include <QFile>
#include <QMap>
#include <QXmlStreamReader>

namespace ods	{

class Book;
class Ns;
class Tag;

class ODS_API Meta
{
public:
	Meta(ods::Book*);
	virtual ~Meta();
	
	const QString&
	err() const { return err_; }
	
	bool
	error() const { return err_.size() > 0; }
	
	void
	Save(const QString &save_dir, QString &err);
	
private:
	NO_ASSIGN_COPY_MOVE(Meta);
	
	void
	InitDefault();
	
	void
	Read();
	
	ods::Book		*book_ = nullptr;
	QString			err_;
	ods::Ns			*ns_ = nullptr;
	ods::Tag		*office_doc_ = nullptr;
	ods::Tag		*office_meta_ = nullptr;
	
	/**
	qint32				cell_count_ = -1;
	QDateTime			creation_date_;
	QDateTime			dc_date_;
	qint32				editing_cycles_ = - 1;
	ods::Duration		editing_duration_;
	QString				generator_;
	qint32				object_count_ = -1;
	qint32				sheet_count_ = -1;
	**/
};

} // namespace ods
#endif
