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

#ifndef ODS_FORMULA_HPP_
#define ODS_FORMULA_HPP_

#include "cell.hxx"
#include "global.hxx"
#include "Value.hpp"
#include <mtl/err.hpp>
#include <QByteArray>
#include <QString>
#include <QStringRef>
#include <QVector>

namespace ods	{ // ods::

class Cell;
class Value;

class ODS_API Formula
{
public:
	Formula();
	Formula(ods::Cell *cell, const QString &ref);
	virtual ~Formula();
	
	void
	Add(ods::Cell *cell);
	
	void
	Add(const double d) { formula_ += QString::number(d); }
	
	void
	Add(const ods::Grouping g);
	
	void
	Add(const ods::Op op);
	
	ods::Formula*
	Clone();
	
	const QString&
	err() { return err_; }
	
	void
	err_set(const QString &s) { err_ = s; }
	
	bool
	error() { return err_.size() > 0; }
	
	const QString&
	formula() const { return formula_; }
	
	void
	formula_set(const QString &s) { formula_ = s; }
	
	bool
	GetDouble(ods::cell::Ref *cell_ref, double &num);
	
	ods::Cell*
	source() { return source_; }
	
	void
	source_set(ods::Cell *cell) { source_ = cell; }
	
	void
	UpdateValue();
	
	ods::Value&
	value() { return value_; }
	
private:
	NO_ASSIGN_COPY_MOVE(Formula);
	
	void
	Init(const QStringRef&);
	
	QString			err_;
	ods::Cell		*source_ = nullptr;
	QString			formula_;
	ods::Value		value_;
};

} // ods::
#endif
