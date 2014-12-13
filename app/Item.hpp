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

#ifndef APP_ITEM_HPP_
#define APP_ITEM_HPP_

#include <QString>

namespace app	{ // app::

class Item
{
public:
	Item(const QString &descr, const double price, const int qtty);
	virtual ~Item();
	
	const QString&
	description() const { return description_; }
	
	void
	description_set(const QString &s) { description_ = s; }
	
	static int
	GetNextId();
	
	int
	id() const { return id_; }
	
	void
	id_set(const int n) { id_ = n; }
	
	int
	qtty_ordered() const { return qtty_ordered_; }
	
	void
	qtty_ordered_set(const int n) { qtty_ordered_ = n; }
	
	double
	unit_price() const { return unit_price_; }
	
	void
	unit_price_set(const double n) { unit_price_ = n; }
	
private:
	int			id_;
	QString		description_;
	double		unit_price_ = 0.0f;
	int			qtty_ordered_ = 0;
};



} // app::

#endif
