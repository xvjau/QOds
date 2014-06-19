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

#include "ods.hh"
#include "Cell.hpp"
#include "Ns.hpp"
#include "Row.hpp"
#include "Sheet.hpp"

#include <QDebug>
#include <QString>
#include <QMap>
#include <QXmlStreamWriter>

namespace ods	{ // ods::

QChar
CharFromOp(const ods::Op op)
{
	switch (op) {
	case ods::Op::Mult:		return '*';
	case ods::Op::Divide:	return '/';
	case ods::Op::Add:		return '+';
	case ods::Op::Subtract:	return '-';
	default:				return '?';
	}
}

ods::Op
CharToOp(const QChar c)
{
	if (c == '*')
		return ods::Op::Mult;
	if (c == '/')
		return ods::Op::Divide;
	if (c == '+')
		return ods::Op::Add;
	if (c == '-')
		return ods::Op::Subtract;
	return ods::Op::None;
}

ods::Cell*
FindCell(ods::cell::Ref *ref, ods::Cell *source)
{
	ods::Sheet *sheet = source->row()->sheet();
	auto *row = sheet->row(ref->row);
	if (row == nullptr)
	{
		mtl_qline(QStringLiteral("No such row: ") + QString::number(ref->row)
			+ QStringLiteral(", row count: ")
			+ QString::number(sheet->CalcRowCount()));
		return nullptr;
	}
	
	auto *cell = row->cell(ref->col);
	if (cell == nullptr) {
		mtl_qline(QStringLiteral("No such cell: ") + QString::number(ref->col)
			+ QStringLiteral(", column count: ")
			+ QString::number(row->column_count()));
		return nullptr;
	}
	return cell;
}

QString
FontSizeToString(const double size, const ods::FontSizeType size_type)
{
	QString str = QString::number(size);
	if (size_type == ods::FontSizeType::Pt)
		str += "pt";
	else if (size_type == ods::FontSizeType::Cm)
		str += "cm";
	else if (size_type == ods::FontSizeType::In)
		str += "in";
	return str;
}

qint32
GenColIndex(const QStringRef &letters)
{
	const auto char_A_code = QChar('A').unicode();
	qint32 col = 0;
	const int kCount = letters.size();
	for (int j = 0; j < kCount; j++)
	{
		const int kDiff = letters.at(j).unicode() - char_A_code;
		if (kCount - 1 == j)
			col += kDiff;
		else
			col += pow(26, kCount - j - 1) * (kDiff+1);
	}
	
	return col;
}

QString
GenColName(const qint32 column)
{
	if (column < 0)
		return QStringLiteral("");
	qint32 digit_count = 1;
	qint32 offset = 0;
	// 26 => alphabet size
	for (qint32 top = 26; column >= top + offset; top *= 26)
	{
		offset += top;
		++digit_count;
	}
	
	QString ret;
	qint32 col = column - offset;
	const auto kCharACode = QChar('A').unicode();
	while (digit_count > 0)
	{
		QChar c(kCharACode + (col % 26));
		ret.prepend(c);
		--digit_count;
		col /= 26;
	}
	return ret;
}

ods::cell::Ref*
ReadRowCol(const QStringRef &s)
{
	//=> FIXME
	/** skip '.', create proper solution later **/
	QStringRef str = s.right(1);
	auto *cell_ref = new ods::cell::Ref();
	
	for(int i=0; i<str.size(); i++)
	{
		QChar c = str.at(i);
		if (!c.isDigit())
			continue;
		
		QStringRef letters = str.left(i);
		cell_ref->col = ods::GenColIndex(letters);
		QStringRef digits = str.right(i);
		bool ok;
		cell_ref->row = digits.toInt(&ok);
		if (ok) {
			cell_ref->row--;
			break;
		} else {
			delete cell_ref;
			return nullptr;
		}
	}
	
	return cell_ref;
}

ods::Type
TypeFromString(const QString &value_type)
{
	if (value_type.size() == 0)
		return ods::Type::Fail;
	if (value_type == ods::ns::kDouble)
		return ods::Type::Double;
	else if (value_type == ods::ns::kString)
		return ods::Type::String;
	else if (value_type == ods::ns::kCurrency)
		return ods::Type::Currency;
	else if (value_type == ods::ns::kPercentage)
		return ods::Type::Percentage;
	else if (value_type == ods::ns::kDate)
		return ods::Type::Date;
	else if (value_type == ods::ns::kTime)
		return ods::Type::Time;
	else if (value_type == ods::ns::kBool)
		return ods::Type::Bool;
	return ods::Type::Fail;
}

const char*
TypeToString(const ods::Type &value_type)
{
	if (value_type == ods::Type::Double)
		return ods::ns::kDouble;
	else if (value_type == ods::Type::String)
		return ods::ns::kString;
	else if (value_type == ods::Type::Currency)
		return ods::ns::kCurrency;
	else if (value_type == ods::Type::Percentage)
		return ods::ns::kPercentage;
	else if (value_type == ods::Type::Date)
		return ods::ns::kDate;
	else if (value_type == ods::Type::Time)
		return ods::ns::kTime;
	else if (value_type == ods::Type::Bool)
		return ods::ns::kBool;
	else if (value_type == ods::Type::Fail)
		return "[Fail]";
	else if (value_type == ods::Type::NotSet)
		return "[Not set]";
	else
		return "[Other]";
	return nullptr;
}

quint32
version_major() { return 1; }

quint32
version_micro() { return 0; }

quint32
version_minor() { return 0; }

} // ods::



















