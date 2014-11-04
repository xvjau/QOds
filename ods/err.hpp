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
 
#ifndef MTL_ERR_HPP_
#define MTL_ERR_HPP_

#include <errno.h>
#include <cstdio>
#include <QDebug>

#ifdef __unix__
	#define MTL_COLOR_BLUE		"\x1B[34m"
	#define MTL_COLOR_DEFAULT	"\x1B[0m"
	#define MTL_COLOR_GREEN		"\x1B[32m"
	#define MTL_COLOR_RED		"\e[0;91m"
#else
	#define MTL_COLOR_BLUE		""
	#define MTL_COLOR_DEFAULT	""
	#define MTL_COLOR_GREEN		""
	#define MTL_COLOR_RED		""
#endif

#ifdef _MSC_VER
#define mtl_line(fmt, ...) fprintf(stdout, \
	"%s[%s %s %.3d] " fmt "%s\n", MTL_COLOR_BLUE, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, __VA_ARGS__, MTL_COLOR_DEFAULT)
#else
#define mtl_line(fmt, args...) fprintf(stdout, \
	"%s[%s %s %.3d] " fmt "%s\n", MTL_COLOR_BLUE, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, ##args, MTL_COLOR_DEFAULT)
#endif

#ifdef _MSC_VER
#define mtl_warn(fmt, ...) fprintf(stderr, \
	"%s[Warning %s %s %.3d] " fmt "%s\n", MTL_COLOR_RED, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, __VA_ARGS__, MTL_COLOR_DEFAULT)
#else
#define mtl_warn(fmt, args...) fprintf(stderr, \
	"%s[Warning %s %s %.3d] " fmt "%s\n", MTL_COLOR_RED, SRC_FILE_NAME, \
	__FUNCTION__, __LINE__, ##args, MTL_COLOR_DEFAULT)
#endif

#define mtl_status(status) fprintf (stderr, "%s[%s %s %.3d] %s%s\n", \
	MTL_COLOR_RED, SRC_FILE_NAME, \
	__LINE__, __FUNCTION__, strerror(status), MTL_COLOR_DEFAULT)

#define mtl_errno fprintf (stderr, "[%s %.3d] %m\n", __LINE__, __FUNCTION__)

#define mtl_qline(qstr) qDebug().nospace() << MTL_COLOR_BLUE << "[" << \
	SRC_FILE_NAME << ' ' << __FUNCTION__ << ' ' << __LINE__ << "] " << \
	qstr << MTL_COLOR_DEFAULT

#define NO_ASSIGN_COPY_MOVE(TypeName)	\
	TypeName(const TypeName&) = delete;		\
	void operator=(const TypeName&) = delete; \
	TypeName(TypeName&&) = delete;

#define NO_MOVE(TypeName)	\
	TypeName(TypeName&&) = delete;

#endif
