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

#ifndef ODS_TAG_HPP_
#define ODS_TAG_HPP_

#include "Attr.hpp"
#include "Attrs.hpp"
#include "global.hxx"
#include "Node.hpp"
#include "Prefix.hpp"
#include "tag.hh"
#include "tag.hxx"
#include <mtl/err.hpp>
#include <QVector>

namespace ods	{ // ods::
class Base;
class Node;
class Ns;

class ODS_API Tag
{
	static const quint8 kUsed	= 1;
	static const quint8 kXmlNs	= 2;
	
public:
	Tag(ods::Ns&, ods::tag::func);
	virtual ~Tag();
	
	void
	Add(ods::Prefix &prefix, const char *name) {
		if (attrs_ == nullptr)
			attrs_ = new ods::Attrs();
		attrs_->Add(prefix, name);
	}
	
	ods::Attr*
	attr() { return attr_; }
	
	void
	attr_set(ods::Prefix &prefix, const char *name) {
		attr_ = new ods::Attr(prefix, name);
	}
	
	ods::Attrs*
	attrs() { return attrs_; }
	
	void
	AttrSet(ods::Prefix &prefix, const char *key, const QString &value);
	
	quint8
	bits() const { return bits_; }
	
	void
	bits_set(const quint8 n) { bits_ = n; }
	
	ods::Tag*
	Clone();
	
	void
	DeleteSubnodes();
	
	ods::tag::func
	func() { return func_; }
	
	void
	func_set(ods::tag::func f) { func_ = f; }
	
	const QString*
	GetAttrString(ods::Prefix &prefix, const char *name);
	
	ods::Tag*
	GetSubtag(ods::Prefix &prefix, const char *name);
	
	ods::Tag*
	GetSubtag(ods::tag::func f);
	
	bool
	IsCell() const { return ods::tag::SheetCell == func_; }
	
	bool
	IsColumn() const { return ods::tag::SheetColumn == func_; }
	
	bool
	IsRow() const { return ods::tag::SheetRow == func_; }
	
	bool
	IsSheet() const { return ods::tag::Sheet == func_; }
	
	ods::Tag*
	New() { return func_(ns_, nullptr); }
	
	ods::Ns&
	ns() { return ns_; }
	
	QString
	QualifiedName() const { return attr_->QualifiedName(); }
	
	void
	Read();
	
	void
	SetPrintXmlns(const bool a) {
		if (a)
			bits_ |= kXmlNs;
		else
			bits_ &= ~kXmlNs;
	}
	
	void
	SetTextP(const QString &value);
	
	void
	SubfuncAdd(ods::tag::func);
	
	void
	SubnodeAdd(ods::Node *node) { subnodes_.append(node); }
	
	QVector<ods::Node*>&
	subnodes() { return subnodes_; }
	
	void
	SubtagAdd(ods::Tag *tag) { SubnodeAdd(new ods::Node(tag)); }
	
	bool
	used() const { return (bits_ & kUsed) != 0; }
	
	void
	used_set(const bool a) {
		if (a)
			bits_ |= kUsed;
		else
			bits_ &= ~kUsed;
	}
	
	void
	Write(QXmlStreamWriter &xml, QString &err);
	
private:
	NO_ASSIGN_COPY_MOVE(Tag);
	
	ods::Attr				*attr_ = nullptr;
	ods::Attrs				*attrs_ = nullptr;
	ods::tag::func			func_;
	ods::Ns					&ns_;
	QVector<ods::tag::func>	subfuncs_;
	QVector<ods::Node*>		subnodes_;
	quint8					bits_ = 0;
};

} // ods::

#endif
