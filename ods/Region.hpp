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

#ifndef ODS_REGION_HPP_
#define ODS_REGION_HPP_

#include "err.hpp"
#include "global.hxx"
#include "region.hxx"
#include <QString>
#include <QVector>

namespace ods	{ // ods::

class Value;

class ODS_API Region
{
protected:
	Region();
public:
	Region(const QString &s);
	virtual ~Region();
	
	int
	deep() const { return deep_; }
	
	void
	deep_set(const int n) { deep_ = n; }
	
	int
	end_index() const { return end_index_; }
	
	void
	end_index_set(const int n) { end_index_ = n; }
	
	void
	Eval(ods::Value&);
	
	void
	Print();
	
	void
	ProcessAddAndSub(ods::Value &value);
	
	void
	ProcessMultAndDiv(ods::Value &value);
	
	int
	start_index() const { return start_index_; }
	
	void
	start_index_set(const int n) { start_index_ = n; }
	
	const QString&
	str() const { return str_; }
	
	void
	str_set(const QString &s) { str_ = s; }
	
private:
	NO_ASSIGN_COPY_MOVE(Region);
	
	void
	Init(const QString &kFormula);
	
	void
	ParseString();
	
	int			start_index_ = -1;
	int			end_index_ = -1;
	int			deep_ = 0;
	QString		str_;
	QVector<ods::region::Token*>	tokens_;
};

} // ods::
#endif
