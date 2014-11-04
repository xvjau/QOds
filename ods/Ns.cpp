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

#include "Ns.hpp"
#include "ods.hxx"
#include <QXmlStreamNamespaceDeclarations>

namespace ods	{ // ods::

Ns::Ns(const ods::UriId kVersionUriId) :
	kVersionUriId_(kVersionUriId),
	prefix_config_(ods::kConfigUri),
	prefix_dc_(ods::kDcUri),
	prefix_draw_(ods::kDrawUri),
	prefix_fo_(ods::kFoUri),
	prefix_manifest_(ods::kManifestUri),
	prefix_meta_(ods::kMetaUri),
	prefix_number_(ods::kNumberUri),
	prefix_of_(ods::kOfUri),
	prefix_office_(ods::kOfficeUri),
	prefix_sheet_(ods::kSheetUri),
	prefix_style_(ods::kStyleUri),
	prefix_svg_(ods::kSvgUri),
	prefix_text_(ods::kTextUri),
	prefix_xlink_(ods::kXlinkUri)
{
	InitDefault();
}

Ns::Ns(QXmlStreamReader *xml, const ods::UriId kVersionUriId) :
	kVersionUriId_(kVersionUriId),
	prefix_config_(ods::kConfigUri),
	prefix_dc_(ods::kDcUri),
	prefix_draw_(ods::kDrawUri),
	prefix_fo_(ods::kFoUri),
	prefix_manifest_(ods::kManifestUri),
	prefix_meta_(ods::kMetaUri),
	prefix_number_(ods::kNumberUri),
	prefix_of_(ods::kOfUri),
	prefix_office_(ods::kOfficeUri),
	prefix_sheet_(ods::kSheetUri),
	prefix_style_(ods::kStyleUri),
	prefix_svg_(ods::kSvgUri),
	prefix_text_(ods::kTextUri),
	prefix_xlink_(ods::kXlinkUri),
	xml_(xml)
{
	Read();
}

Ns::~Ns()
{}

bool
Ns::At(const Prefix &prefix, const char *kName) const
{
	QStringRef current = xml_->prefix();
	if (!current.isNull() && prefix.str() != current)
		return false;
	if (kName == nullptr)
		return true;
	return xml_->name() == kName;
}

ods::Prefix*
Ns::GetPrefixByUriId(const ods::UriId id)
{
	if (id == ods::UriId::Office)
		return &prefix_office_;
	if (id == ods::UriId::Manifest) {
		//return &prefix_manifest_;
		return nullptr;
	}
	
	return nullptr;
}

void
Ns::InitDefault()
{
	version_ = QStringLiteral("1.2");
	
	prefix_config_.str_set(QStringLiteral("config"));
	prefix_dc_.str_set(QStringLiteral("dc"));
	prefix_draw_.str_set(QStringLiteral("draw"));
	prefix_fo_.str_set(QStringLiteral("fo"));
	prefix_manifest_.str_set(QStringLiteral("manifest"));
	prefix_meta_.str_set(QStringLiteral("meta"));
	prefix_number_.str_set(QStringLiteral("number"));
	prefix_of_.str_set(QStringLiteral("of"));
	prefix_office_.str_set(QStringLiteral("office"));
	prefix_sheet_.str_set(QStringLiteral("table"));
	prefix_style_.str_set(QStringLiteral("style"));
	prefix_svg_.str_set(QStringLiteral("svg"));
	prefix_text_.str_set(QStringLiteral("text"));
	prefix_xlink_.str_set(QStringLiteral("xlink"));
}

void
Ns::Read()
{
	auto decls = xml_->namespaceDeclarations();
	foreach (auto decl, decls)
	{
		QString prefix = decl.prefix().toString();
		QStringRef uri = decl.namespaceUri();
		
		if (uri == ods::kOfficeUri.str)
			prefix_office_.str_set(prefix);
		else if (uri == ods::kSheetUri.str)
			prefix_sheet_.str_set(prefix);
		else if (uri == ods::kMetaUri.str)
			prefix_meta_.str_set(prefix);
		else if (uri == ods::kNumberUri.str)
			prefix_number_.str_set(prefix);
		else if (uri == ods::kStyleUri.str)
			prefix_style_.str_set(prefix);
		else if (uri == ods::kTextUri.str)
			prefix_text_.str_set(prefix);
		else if (uri == ods::kOfUri.str)
			prefix_of_.str_set(prefix);
		else if (uri == ods::kConfigUri.str)
			prefix_config_.str_set(prefix);
		else if (uri == ods::kDcUri.str)
			prefix_dc_.str_set(prefix);
		else if (uri == ods::kDrawUri.str)
			prefix_draw_.str_set(prefix);
		else if (uri == ods::kManifestUri.str)
			prefix_manifest_.str_set(prefix);
		else if (uri == ods::kSvgUri.str)
			prefix_svg_.str_set(prefix);
		else if (uri == ods::kFoUri.str)
			prefix_fo_.str_set(prefix);
		else if (uri == ods::kXlinkUri.str)
			prefix_xlink_.str_set(prefix);
	}
	
	auto *prefix = GetPrefixByUriId(kVersionUriId_);
	QStringRef ref;
	if (prefix != nullptr) {
		auto attrs = xml_->attributes();
		ref = attrs.value(prefix->With(ods::ns::kVersion));
	}
	if (ref.isEmpty()) {
		/** From the spec:
		  * When an "office:version"-requiring element has "office:version"
		  * omitted, the element is based on a version of the OpenDocument
		  * specification earlier than v1.2.
		**/
		version_ = QStringLiteral("1.0");
	} else {
		version_ = ref.toString();
	}
}

void
Ns::WriteNamespaces(QXmlStreamWriter &xml)
{
	prefix_config_.Write(xml);
	prefix_dc_.Write(xml);
	prefix_draw_.Write(xml);
	prefix_fo_.Write(xml);
	prefix_manifest_.Write(xml);
	prefix_meta_.Write(xml);
	prefix_number_.Write(xml);
	prefix_of_.Write(xml);
	prefix_office_.Write(xml);
	prefix_sheet_.Write(xml);
	prefix_style_.Write(xml);
	prefix_svg_.Write(xml);
	prefix_text_.Write(xml);
	prefix_xlink_.Write(xml);
	
	auto *prefix = GetPrefixByUriId(kVersionUriId_);
	if (prefix != nullptr)
		xml.writeAttribute(prefix->With(ods::ns::kVersion), version_);
}


} // ods::
