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

#include "Formula.hpp"

#include "Cell.hpp"
#include "ods.hh"
#include "Region.hpp"
#include "Row.hpp"
#include "Sheet.hpp"
#include "Value.hpp"

#include <QDebug>

namespace ods	{

Formula::Formula() :
	formula_(ods::kFormulaPrefix)
{
}

Formula::Formula(ods::Cell *cell, const QString &str) :
	source_(cell)
{
	formula_ = str.simplified().replace(" ", "");
}

Formula::~Formula()
{}

void
Formula::Add(ods::Cell *cell)
{
	formula_ += QString("[.");
	formula_ += cell->Address();
	formula_ += QString("]");
}

void
Formula::Add(const ods::Grouping g)
{
	if (g == ods::Grouping::Open)
		formula_ += '(';
	else
		formula_ += ')';
}

void
Formula::Add(const ods::Op op)
{
	formula_ += ods::CharFromOp(op);
}

ods::Formula*
Formula::Clone()
{
	auto *formula = new ods::Formula();
	formula->formula_set(formula_);
	formula->source_set(source_);
	value_.CopyTo(formula->value());
	formula->err_set(err_);
	return formula;
}

bool
Formula::GetDouble(ods::cell::Ref *cell_ref, double &num)
{
	auto *found_cell = ods::FindCell(cell_ref, source_);
	if (found_cell == nullptr) {
		mtl_warn("Cell not found");
		return false;
	}
	if (found_cell->HasFormula()) {
		const auto &value = found_cell->formula()->value();
		if (value.NoValue()) {
			mtl_warn("No value");
		} else if (value.IsDouble()){
			num = *value.AsDouble();
			return true;
		} else {
			mtl_warn("Unknown value type");
		}
		return false;
	}
	
	bool ok;
	num = found_cell->value().toString().toDouble(&ok);
	return ok;
}

void
Formula::UpdateValue()
{
	/**
	((C5+B5)/A5)*(C4+B4*A3)+B3-C3
	((10+0.5)/3)*(4.5+2.4*22.3)+8-6
	**/
	value_.type_set(ods::Type::Fail);
	err_.clear();
	if (!formula_.startsWith(ods::kFormulaPrefix)) {
		err_ = QLatin1String("Doesn't start with ") + ods::kFormulaPrefix;
		return;
	}
	
	QString number_formula;
	QStringRef form = formula_.rightRef(formula_.size() -
		ods::kFormulaPrefix.size());
	double num;
	for(int i=0; i<form.size(); i++)
	{
		if (form.at(i) == '[')
		{
			int index = form.indexOf(']', i+1);
			if (index == -1)
			{
				err_ = QLatin1String("] not found");
				return;
			}
			QStringRef cell_name = form.mid(i+1, index-i-1);
			auto *cell_ref = ods::ReadRowCol(cell_name);
			if (cell_ref == nullptr)
			{
				err_ = QLatin1String("ReadRowCol() failed");
				return;
			}
			
			if (!GetDouble(cell_ref, num)) {
				qDebug() << "failed double(), row: " << cell_ref->row <<
					", col: " << cell_ref->col << ", from cell_name: " <<
					cell_name;
				err_ = QLatin1String("GetDouble() failed");
				return;
			}
			
			number_formula.append(QString::number(num));
			i = index;
		} else {
			number_formula.append(form.at(i));
		}
	}
	
	auto *deepest = new ods::Region(number_formula);
	while (deepest->deep() >= 1)
	{
		deepest->Eval(value_);
		if (value_.error()) {
			err_ = QLatin1String("Region::Eval() error");
			return;
		}
		if (!value_.IsDouble()) {
			err_ = QLatin1String("Value not double");
			return;
		}
		
		if (number_formula.size() == 0) {
			break;
		}
		QString str_num = QString::number(*value_.AsDouble());
		QString temp = number_formula.left(deepest->start_index());
		if (deepest->end_index() < number_formula.size()-1) {
			QString right = number_formula.right(number_formula.size()
				- deepest->end_index() - 1);
			temp += str_num + right;
		} else {
			temp += str_num;
		}
		number_formula = temp;
		delete deepest;
		deepest = new ods::Region(number_formula);
	}
	
	deepest = new ods::Region(number_formula);
	deepest->Eval(value_);
	delete deepest;
}

} // namespace ods
