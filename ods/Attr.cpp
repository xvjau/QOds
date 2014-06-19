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

#include "Attr.hpp"
#include "Attrs.hpp"
#include <QXmlStreamWriter>

namespace ods	{ // ods::

Attr::Attr(ods::Prefix &prefix, const char *name) :
	name_(name),
	prefix_(prefix)
{}

Attr::~Attr()
{}

ods::Attr*
Attr::Clone()
{
	auto *attr = new ods::Attr(prefix_, name_);
	attr->value_set(value_);
	return attr;
}

void
Attr::Load(QXmlStreamAttributes &attrs)
{
	const QString &full_prefix = prefix_.With(name_);
	QStringRef ref = attrs.value(full_prefix);
	if (!ref.isEmpty())
		value_ = ref.toString();
}
/**
QString
Attr::QualifiedName() const {
	return prefix_.With(name_);
}
**/
bool
Attr::ToDouble(double &n)
{
	bool ok;
	auto tmp = value_.toDouble(&ok);
	if (ok)
		n = tmp;
	return ok;
}

bool
Attr::ToUint16(quint16 &n)
{
	bool ok;
	auto tmp = value_.toUShort(&ok);
	if (ok)
		n = tmp;
	return ok;
}

bool
Attr::ToInt32(qint32 &n)
{
	bool ok;
	auto tmp = value_.toInt(&ok);
	if (ok)
		n = tmp;
	return ok;
}

void
Attr::Write(QXmlStreamWriter &xml)
{
	if (!value_.isEmpty())
		xml.writeAttribute(QualifiedName(), value_);
}

} // ods::
