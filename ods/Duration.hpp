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

#ifndef ODS_DURATION_HPP_
#define ODS_DURATION_HPP_

#include <QtGlobal>
#include <QtCore/QString>

#include "global.hxx"

namespace ods	{

class ODS_API Duration
{
public:
	Duration();
	virtual ~Duration();
	
	Duration(const Duration &rhs);
	
	operator QString();
	
	static Duration
	FromString(const QString&);
	
	qint32
	years() const { return years_; }
	
	void
	years_set(const qint32 n) { years_ = n; }
	
	qint32
	months() const { return months_; }
	
	void
	months_set(const qint32 n) { months_ = n; }
	
	qint32
	days() const { return days_; }
	
	void
	days_set(const qint32 n) { days_ = n; }
	
	qint32
	hours() const { return hours_; }
	
	void
	hours_set(const qint32 n) { hours_ = n; }
	
	qint32
	minutes() const { return minutes_; }
	
	void
	minutes_set(const qint32 n) { minutes_ = n; }
	
	qint32
	seconds() const { return seconds_; }
	
	void
	seconds_set(const qint32 n) { seconds_ = n; }
	
	bool
	valid() const { return valid_; }
	
	void
	valid_set(const bool b) { valid_ = b; }
	
private:
	
	qint32		years_;
	qint32		months_;
	qint32		days_;
	qint32		hours_;
	qint32		minutes_;
	qint32		seconds_;
	bool		valid_;
};

} // namespace ods
#endif
