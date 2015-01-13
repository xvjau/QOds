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

#include "Tag.hpp"
#include "Attr.hpp"
#include "Attrs.hpp"
#include "Node.hpp"
#include "Ns.hpp"

namespace ods	{ // ods::

Tag::Tag(ods::Ns &ns, ods::tag::func cf) :
	func_(cf),
	ns_(ns)
{}

Tag::~Tag()
{
	delete attr_;
	delete attrs_;
	DeleteSubnodes();
}

void
Tag::AttrSet(ods::Prefix &prefix, const char *key, const QString &value)
{
	if (attrs_ == nullptr)
		attrs_ = new ods::Attrs();
	auto *attr = attrs_->Get(prefix, key);
	if (attr == nullptr) {
		attr = new ods::Attr(prefix, key);
		attrs_->Add(attr);
	}
	attr->value_set(value);
}

ods::Tag*
Tag::Clone()
{
	auto *tag = this->New();
	tag->attrs_set(attrs_->Clone());
	tag->attr_set(attr_->Clone());
	return tag;
}

void
Tag::DeleteSubnodes()
{
	foreach (auto *item, subnodes_)
		delete item;
	subnodes_.clear();
}

const QString*
Tag::GetAttrString(ods::Prefix &prefix, const char *name)
{
	auto *attr = attrs_->Get(prefix, name);
	if (attr == nullptr)
		return nullptr;
	return &attr->value();
}

ods::Tag*
Tag::GetSubtag(ods::Prefix &prefix, const char *name)
{
	foreach (auto *node, subnodes_) {
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		if (tag->attr()->Equals(prefix, name))
			return tag;
	}
	return nullptr;
}

ods::Tag*
Tag::GetSubtag(ods::tag::func f)
{
	foreach (auto *node, subnodes_) {
		if (!node->IsTag())
			continue;
		auto *tag = node->Tag();
		if (tag->func() == f)
			return tag;
	}
	return nullptr;
}

void
Tag::Read()
{
	if (attrs_ == nullptr)
		attrs_ = new ods::Attrs();
	func_(ns_, this);
	auto &xml = ns_.xml();
	attrs_->Load(xml);
	auto token = QXmlStreamReader::NoToken;
	ods::Tag *append_tag;
	QVector<ods::Tag*> subtags;
	
	foreach (auto *func, subfuncs_)
		subtags.append(func(ns_, nullptr));
	
	while (token != QXmlStreamReader::EndElement || !ns_.At(attr_))
	{
		token = xml.readNext();
		if (token == QXmlStreamReader::Characters)
		{
			const QString text = xml.text().toString();
			SubnodeAdd(new ods::Node(text));
			continue;
		}
		
		if (token != QXmlStreamReader::StartElement)
			continue;
		
		foreach (auto *tag, subtags)
		{
			if (!ns_.At(tag))
				continue;
			if (tag->used()) {
				append_tag = tag->New();
			} else {
				append_tag = tag;
				tag->used_set(true);
			}
			SubnodeAdd(new ods::Node(append_tag));
			append_tag->Read();
			break;
		}
	}
	
	foreach (auto *tag, subtags) {
		if (!tag->used())
			delete tag;
	}
}

void
Tag::SetTextP(const QString &value)
{
	ods::Tag *textp = GetSubtag(ns_.text(), ods::ns::kP);
	if (textp == nullptr) {
		textp = ods::tag::TextP(ns_, nullptr);
		subnodes_.append(new ods::Node(textp));
	} else {
		textp->DeleteSubnodes();
	}
	textp->subnodes().append(new ods::Node(value));
	bits_ |= ods::tag::bits::HasTextP;
}

void
Tag::SubfuncAdd(ods::tag::func f)
{
	subfuncs_.append(f);
}

void
Tag::Write(QXmlStreamWriter &xml, QString &err)
{
	xml.writeStartElement(attr_->QualifiedName());
	
	if (bits_ & ods::tag::bits::XmlNs)
		ns_.WriteNamespaces(xml);
	if (attrs_ != nullptr)
		attrs_->Write(xml);
	foreach (auto *node, subnodes_)
	{
		if (node->IsTag())
		{
			node->Tag()->Write(xml, err);
			if (!err.isEmpty())
				return;
		} else {
			xml.writeCharacters(*node->String());
		}
	}
	xml.writeEndElement();
}

} // ods::
