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

#include "Attrs.hpp"
#include "Attr.hpp"
#include "ns.hxx"
#include "Prefix.hpp"
#include <string.h>

#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace ods	{ // ods::

Attrs::Attrs()
{}

Attrs::~Attrs()
{
	foreach (auto *attr, attrs_)
		delete attr;
}

void
Attrs::Add(ods::Prefix &prefix, const char *name)
{
	attrs_.append(new ods::Attr(prefix, name));
}

ods::Attrs*
Attrs::Clone()
{
	auto *inst = new ods::Attrs();
	auto &vec = inst->attrs();
	foreach (auto *attr, attrs_)
	{
		vec.append(attr->Clone());
	}
	return inst;
}

ods::Attr*
Attrs::Get(ods::Prefix &prefix, const char *name)
{
	foreach (auto *attr, attrs_) {
		ods::Prefix &curr_prefix = attr->prefix();
		if (prefix.uri().id != curr_prefix.uri().id)
			continue;
		if (strcmp(name, attr->name()) == 0)
			return attr;
	}
	//only reached if buggy code
	return nullptr;
}

void
Attrs::Load(QXmlStreamReader &xml)
{
	auto attribs = xml.attributes();
	foreach (auto *attr, attrs_)
		attr->Load(attribs);
}

void
Attrs::Write(QXmlStreamWriter &xml)
{
	foreach (auto *attr, attrs_)
		attr->Write(xml);
}

} // ods::
