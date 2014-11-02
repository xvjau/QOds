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

#ifndef ODS_HH_
#define ODS_HH_

#include <QStringRef>
#include <QDateTime>
#include <QGlobalStatic>
#include <QXmlStreamAttributes>

#include "cell.hxx"
#include "global.hxx"
#include "Duration.hpp"

class QXmlStreamWriter;

namespace ods	{ // ods::

class Cell;
class Ns;

ODS_API QChar
CharFromOp(const ods::Op);

ODS_API ods::Op // error => ods::Op::NONE
CharToOp(const QChar sign);

ODS_API ods::Cell* // error => nullptr
FindCell(ods::cell::Ref *ref, ods::Cell *source);

ODS_API QString
FontSizeToString(const double size, const ods::FontSizeType tp);

ODS_API qint32
GenColIndex(const QStringRef &letters);

ODS_API QString
GenColName(const qint32 kColumn);

ODS_API ods::cell::Ref* // error => nullptr
ReadRowCol(const QStringRef &s);

ODS_API ods::Type
TypeFromString(const QString &ods_type);

ODS_API const char* // nullptr if not found
TypeToString(const ods::Type &value_type);

ODS_API quint32
version_major();

ODS_API quint32
version_micro();

ODS_API quint32
version_minor();

} // ods::

#endif


