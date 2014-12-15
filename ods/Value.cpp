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

#include "Value.hpp"
#include "Attrs.hpp"
#include "Ns.hpp"
#include "ns.hxx"
#include "Tag.hpp"
#include <QStringRef>

namespace ods	{

Value::Value()
{}

Value::Value(void *v, const ods::Type kType)
{
	data_ = v;
	type_ = kType;
}

Value::~Value()
{
	DeleteData();
}

void
Value::CopyTo(ods::Value &v)
{
	v.type_set(type_);
	if (IsEmpty())
		return;
	if (IsDouble())
		v.SetDouble(*AsDouble());
	else if (IsString())
		v.SetString(*AsString());
	else if (IsPercentage())
		v.SetPercentage(*AsPercentage());
	else
		mtl_warn("Not implemented");
}

void
Value::DeleteData()
{
	if (IsEmpty())
		return;
	if (IsDouble() || IsPercentage())
		delete AsDouble();
	else if (IsString())
		delete AsString();
	data_ = nullptr;
	type_ = ods::Type::NotSet;
}

QString
Value::Diagnose()
{
	return QString("[Cell] [type] ") + ods::TypeToString(type_) +
		QString(" [value]") + toString();
}

void
Value::Read(ods::Ns &ns, ods::Attrs &attrs)
{
	DeleteData();
	auto *type_attr = attrs.Get(ns.office(), ods::ns::kValueType);
	if (type_attr == nullptr) { // shouldn't happen
		type_ = ods::Type::Fail;
		return;
	}
	type_ = ods::TypeFromString(type_attr->value());
	auto *value_attr = attrs.Get(ns.office(), ods::ns::kValue);
	if (value_attr == nullptr) {
		type_ = ods::Type::Fail;
		return;
	}
	
	if (IsDouble() || IsPercentage()) {
		double num;
		if (value_attr->ToDouble(num))
		{
			const auto value_type = IsDouble() ?
				ods::Type::Double : ods::Type::Percentage;
			set(new double(num), value_type);
		}
	} else if (IsString()) {
		set(new QString(value_attr->value()), ods::Type::String);
	} else {
		type_ = ods::Type::NotSet;
	}
}

void
Value::ReadTextP(ods::Tag *tag)
{
	QVector<ods::Node*> &nodes = tag->subnodes();
	QString *str = nullptr;
	foreach (auto *node, nodes)
	{
		if (!node->IsString())
			continue;
		str = node->String();
		SetString(*str);
		return;
	}
}

void
Value::SetDouble(const double d)
{
	DeleteData();
	type_ = ods::Type::Double;
	data_ = new double();
	*AsDouble() = d;
}

void
Value::SetPercentage(const double d)
{
	SetDouble(d);
	type_ = ods::Type::Percentage;
}

void
Value::SetString(const QString &s)
{
	DeleteData();
	type_ = ods::Type::String;
	data_ = new QString();
	*AsString() = s;
}

QString
Value::toString() const
{
	if (error() || IsEmpty())
		return "";
	
	if (IsDouble() || IsPercentage())
		return QString::number(*AsDouble());
	if (IsString())
		return *AsString();
	if (IsDate())
		return AsDate()->toString(Qt::ISODate);
	if (IsCurrency())
		mtl_qline("Currency not supported yet");
	
	return "";
}

} // namespace ods
