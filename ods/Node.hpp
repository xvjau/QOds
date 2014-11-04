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

#ifndef ODS_NODE_HPP_
#define ODS_NODE_HPP_

#include "err.hpp"
#include "global.hxx"
#include "node.hxx"

namespace ods	{ // ods::
class Tag;

class ODS_API Node
{
public:
	Node(const QString&);
	Node(ods::Tag*);
	virtual ~Node();
	
	QString*
	String() { return (QString*) data_; }
	
	ods::Tag*
	Tag() { return (ods::Tag*) data_; }
	
	bool
	IsString() const { return type_ == ods::node::Type::String; }
	
	bool
	IsTag() const { return type_ == ods::node::Type::Tag; }
	
private:
	NO_ASSIGN_COPY_MOVE(Node);
	
	void			*data_ = nullptr;
	ods::node::Type	type_ = ods::node::Type::Tag;
};

} // ods::

#endif
