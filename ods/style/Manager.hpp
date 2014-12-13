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

#ifndef ODS_STYLE_MANAGER_HPP_
#define ODS_STYLE_MANAGER_HPP_

#include "../err.hpp"
#include "../global.hxx"
#include "../ods.hxx"
#include <QString>
#include <QXmlStreamReader>

class QXmlStreamWriter;

namespace ods	{ // ods::

class Book;
class Ns;
class Style;
class Tag;

namespace style	{ // ods::style::

class ODS_API Manager
{
public:
	Manager(ods::Book *book);
	virtual ~Manager();
	
	void
	ApplyFontFace(const QString &kFontName, ods::Tag *tag);
	
	ods::Tag*
	automatic_styles_tag() const { return automatic_styles_tag_; }
	
	const QString&
	err() const { return err_; }
	
	void
	InitDefault();
	
	ods::Ns&
	ns() { return *ns_; }
	
	ods::Tag*
	styles_tag() const { return styles_tag_; }
	
	void
	Save(const QString &save_dir, QString &err);

private:
	NO_ASSIGN_COPY_MOVE(Manager);
	
	void
	InitDefaultStyles();
	
	void
	InitFontFaceDecls();
	
	void
	Read();
	
	ods::Tag			*root_tag_ = nullptr;
	ods::Tag			*automatic_styles_tag_ = nullptr;
	ods::Tag			*styles_tag_ = nullptr;
	ods::Tag			*font_face_decls_tag_ = nullptr;
	QVector<QString>	font_names_;
	ods::Tag			*master_styles_tag_ = nullptr;
	ods::Book			*book_ = nullptr;
	QString				err_;
	ods::Ns				*ns_ = nullptr;
};

} // ods::style::
} // ods::

#endif
