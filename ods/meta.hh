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

#ifndef ODS_META_HH_
#define ODS_META_HH_

#include "global.hxx"

namespace ods	{ // ods::
class Ns;
class Tag;
namespace meta	{ // ods::meta::

ODS_API ods::Tag*
CreationDate(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
DocumentStatistic(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
EditingCycles(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
EditingDuration(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
Generator(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
InitialCreator(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
Office(ods::Ns&, ods::Tag*);

ODS_API ods::Tag*
OfficeDocument(ods::Ns&, ods::Tag*);

} // ods::meta::
} // ods::
#endif
