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


#ifndef ODS_ATTR_HPP_
#define ODS_ATTR_HPP_

#include "global.hxx"
#include "Prefix.hpp"
#include "err.hpp"

class QXmlStreamAttributes;
class QXmlStreamWriter;

namespace ods	{ // ods::
class Attrs;
class Prefix;

class ODS_API Attr
{
public:
	//==> used by ods::Tag
	Attr(ods::Prefix &prefix, const char *name);
	//<== used by ods::Tag
	virtual ~Attr();
	
	ods::Attr*
	Clone();
	
	bool
	Equals(ods::Prefix &prefix, const char *name) {
		return (prefix_.uri().id == prefix.uri().id) &&
			(strcmp(name_, name) == 0);
	}
	
	void
	Load(QXmlStreamAttributes &attrs);
	
	const char*
	name() const { return name_; }
	
	ods::Prefix&
	prefix() { return prefix_; }
	
	QString
	QualifiedName() const { return prefix_.With(name_); }
	
	bool
	ToDouble(double &d);
	
	bool
	ToInt32(qint32 &n);
	
	bool
	ToUint16(quint16 &n);
	
	const QString&
	value() const { return value_; }
	
	void
	value_set(const QString &s) { value_ = s; }
	
	void
	Write(QXmlStreamWriter &xml);

private:
	NO_ASSIGN_COPY_MOVE(Attr);
	
	const char		*name_ = nullptr;
	ods::Prefix		&prefix_;
	QString			value_;
};

} // ods::

#endif
