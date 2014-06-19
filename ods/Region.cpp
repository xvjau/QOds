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

#include "Region.hpp"
#include "ods.hh"
#include "Value.hpp"

#include <QDebug>
#include <QStringRef>

namespace ods	{ // ods::

Region::Region()
{}

Region::Region(const QString &s)
{
	Init(s);
}

Region::~Region() {}

void
Region::Init(const QString &formula_str)
{
	static ods::Region current_region; // thread-safe in c++11
	for (int i = 0; i < formula_str.size(); i++)
	{
		const QChar c = formula_str.at(i);
		if (c == '(') {
			current_region.start_index_set(i);
			current_region.deep_set(current_region.deep() + 1);
			if (deep_ < current_region.deep())
			{
				start_index_ = current_region.start_index();
				deep_ = current_region.deep();
				end_index_ = -1;
			}
		} else if (c == ')') {
			if (current_region.deep() == deep_ && end_index_ == -1) {
				end_index_ = i;
			}
			current_region.deep_set(current_region.deep() - 1);
			if (current_region.deep() == 0) {
				current_region.end_index_set(i);
			}
		}
	}
	
	if (deep_ < 1) {
		str_ = formula_str;
	} else {
		str_ = formula_str.mid(start_index_ + 1, end_index_ - start_index_ - 1);
	}
}

void
Region::Eval(ods::Value &value)
{
	ParseString();
	value.DeleteData();
	value.set(new double(), ods::Type::Double);
	
	// first * and /
	ProcessMultAndDiv(value);
	// only + and - left
	ProcessAddAndSub(value);
	
	auto *last_one = tokens_[tokens_.size()-1];
	value.SetDouble(last_one->num);
}

void
Region::ParseString()
{
	const QString &str = str_;
	int next = 0;
	bool last_was_op = true, ok;
	// e.g. 23*8-5
	for (int i = 0; i < str.size(); i++)
	{
		ods::Op op;
		do {
			op = ods::CharToOp(str[next]);
			next++;
			if (next >= str.size()) {
				op = ods::Op::None;
				break;
			}
			if (last_was_op) { // then next one can't be an op
				last_was_op = false;
				op = ods::Op::None;
				continue;
			}
			last_was_op = (op != ods::Op::None);
		} while (op == ods::Op::None);
		
		int found_op = (op == ods::Op::None) ? 0 : 1;
		QStringRef num_str = str.midRef(i, next - i - found_op);
		auto *token = new ods::region::Token();
		token->num = num_str.toDouble(&ok);
		token->op = ok ? op : ods::Op::Fail;
		tokens_.push_back(token);
		i = next - 1;
	}
}

void
Region::Print()
{
	qDebug() << "ods::Region" << start_index_ << "<=>" <<
		end_index_ << ", deep" << deep_ << ", str:" << str_;
}

void
Region::ProcessAddAndSub(ods::Value &value)
{
	for (int i = 0; i < tokens_.size(); i++)
	{
		const auto *token = tokens_[i];
		const ods::Op op = token->op;
		if (op == ods::Op::Fail)
		{
			value.type_set(ods::Type::Fail);
			break;
		}
		if (i >= tokens_.size() - 1)
			continue;
		auto *token_next = tokens_[i+1];
		if (op == ods::Op::Add)
			token_next->num = token->num + token_next->num;
		else
			token_next->num = token->num - token_next->num;
		tokens_.removeAt(i);
		i--;
	}
}

void
Region::ProcessMultAndDiv(ods::Value &value)
{
	for (int i = 0; i < tokens_.size(); i++)
	{
		const auto *token = tokens_[i];
		const ods::Op op = token->op;
		if (op == ods::Op::Fail)
		{
			value.type_set(ods::Type::Fail);
			break;
		}
		if (op != ods::Op::Mult && op != ods::Op::Divide)
			continue;
		if (i >= tokens_.size() - 1)
		{
			mtl_warn("Shouldn't happen");
			continue;
		}
		auto *token_next = tokens_[i+1];
		if (op == ods::Op::Mult)
			token_next->num = token->num * token_next->num;
		else
			token_next->num = token->num / token_next->num;
		tokens_.removeAt(i);
		i--;
	}
}

} // ods::
