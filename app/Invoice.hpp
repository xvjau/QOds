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

#ifndef APP_INVOICE_HPP_
#define APP_INVOICE_HPP_

#include <ods/ods>

namespace app	{ // app::

class Item;

class Invoice
{
public:
	Invoice();
	virtual ~Invoice();
	
private:
	
	int // last row or -1 on error
	CreateBillToHeader(const int kLastRow);
	
	int
	CreateNotes(const int kLastRow);
	
	int // last row or -1 on error
	CreateSellerHeader();
	
	int
	CreateTable(QVector<app::Item*>*, const int kLastRow);
	
	int
	CreateTableHeader(const int kLastRow);
	
	QVector<app::Item*>*
	GenItems();
	
	void
	Init();
	
	ods::Book book_;
	ods::Sheet *sheet_ = nullptr;
};

} // app::


#endif
