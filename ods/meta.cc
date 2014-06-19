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

#include "meta.hh"
#include "Ns.hpp"
#include "style/style.hxx"
#include "Tag.hpp"
#include "tag.hh"

namespace ods	{ // ods::
namespace meta	{ // ods::meta::

ods::Tag*
CreationDate(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::CreationDate);
		tag->attr_set(ns.meta(), ods::ns::kCreationDate);
		return tag;
	}
	return nullptr;
}

ods::Tag*
DocumentStatistic(ods::Ns &ns, ods::Tag *tag)
{
	
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::DocumentStatistic);
		tag->attr_set(ns.meta(), ods::ns::kDocStatistic);
		return tag;
	}
	tag->Add(ns.meta(), ods::ns::kTableCount);
	tag->Add(ns.meta(), ods::ns::kObjectCount);
	tag->Add(ns.meta(), ods::ns::kCellCount);
	return nullptr;
}

ods::Tag*
EditingCycles(ods::Ns &ns, ods::Tag *tag)
{
	
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::EditingCycles);
		tag->attr_set(ns.meta(), ods::ns::kEditingCycles);
		return tag;
	}
	return nullptr;
}

ods::Tag*
EditingDuration(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::EditingDuration);
		tag->attr_set(ns.meta(), ods::ns::kEditingDuration);
		return tag;
	}
	return nullptr;
}

ods::Tag*
Generator(ods::Ns &ns, ods::Tag *tag)
{
	
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::Generator);
		tag->attr_set(ns.meta(), ods::ns::kGenerator);
		return tag;
	}
	return nullptr;
}

ods::Tag*
InitialCreator(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::InitialCreator);
		tag->attr_set(ns.meta(), ods::ns::kInitialCreator);
		return tag;
	}
	return nullptr;
}

ods::Tag*
Office(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::Office);
		tag->attr_set(ns.office(), ods::ns::kMeta);
		return tag;
	}
	tag->SubfuncAdd(ods::meta::CreationDate);
	tag->SubfuncAdd(ods::tag::DcCreator);
	tag->SubfuncAdd(ods::tag::DcDate);
	tag->SubfuncAdd(ods::meta::DocumentStatistic);
	tag->SubfuncAdd(ods::meta::EditingDuration);
	tag->SubfuncAdd(ods::meta::EditingCycles);
	tag->SubfuncAdd(ods::meta::InitialCreator);
	tag->SubfuncAdd(ods::meta::Generator);
	return nullptr;
}

ods::Tag*
OfficeDocument(ods::Ns &ns, ods::Tag *tag)
{
	if (tag == nullptr) {
		tag = new ods::Tag(ns, ods::meta::OfficeDocument);
		tag->attr_set(ns.office(), ods::ns::kDocMeta);
		tag->SetPrintXmlns(true);
		return tag;
	}
	tag->SubfuncAdd(ods::meta::Office);
	return nullptr;
}

} // ods::meta::
} // ods::
