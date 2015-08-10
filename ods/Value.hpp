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

#ifndef ODS_data_HPP_
#define ODS_data_HPP_

#include "cell.hxx"
#include "err.hpp"
#include "global.hxx"
#include "ods.hh"
#include "ods.hxx"

#include <QString>
#include <QXmlStreamAttributes>

namespace ods	{

class Attrs;
class Ns;
class Tag;

class ODS_API Value
{
public:
	Value();
	Value(void *v, const ods::Type kType);
	virtual ~Value();
	
	bool*
	AsBool() const { return (bool*) data_; }

	double*
	AsCurrency() const { return AsDouble(); }
	
	QDateTime*
	AsDate() const { return (QDateTime*) data_; }
	
	double*
	AsDouble() const { return (double*) data_; }

	double*
	AsPercentage() const { return AsDouble(); }
	
	QString*
	AsString() const { return (QString*) data_; }
	
	void
	CopyTo(ods::Value&);
	
	void
	DeleteData();
	
	QString
	Diagnose();
	
	bool
	error() const { return type_ == ods::Type::Fail; }
	
	void*
	get() { return data_; }
	
	bool
	IsBool() const { return type_ == ods::Type::Bool; }
	
	bool
	IsCurrency() const { return type_ == ods::Type::Currency; }
	
	bool
	IsDate() const { return type_ == ods::Type::Date; }
	
	bool
	IsDouble() const { return type_ == ods::Type::Double; }
	
	bool
	IsPercentage() const { return type_ == ods::Type::Percentage; }
	
	bool
	IsString() const { return type_ == ods::Type::String; }
	
	bool
	IsTime() const { return type_ == ods::Type::Time; }
	
	bool
	NoValue() const { return data_ == nullptr; }
	
	bool
	Ok() const { return !error() && !NoValue(); }
	
	void
	Read(ods::Ns &ns, ods::Attrs &attrs);
	
	void
	ReadTextP(ods::Tag *tag);
	
	void
	set(void *value) { DeleteData(); data_ = value; }
	
	void
	set(void *value, const ods::Type kType) {
		DeleteData();
		data_ = value;
		type_ = kType;
	}

	void
	SetCurrency(const double d);
	
	void
	SetDouble(const double d);

	void
	SetPercentage(const double d);
	
	void
	SetString(const QString &s);
	
	QString
	toString() const;
	
	ods::Type
	type() const { return type_; }
	
	bool
	TypeIsValid() const { return type_ != ods::Type::Fail; }
	
	const char*
	TypeToString() const { return ods::TypeToString(type_); }
	
	void
	type_set(const ods::Type kType) { type_ = kType; }
	
private:
	NO_ASSIGN_COPY_MOVE(Value);
	
	void		*data_ = nullptr;
	ods::Type	type_ = ods::Type::NotSet;
};

} // namespace ods
#endif
