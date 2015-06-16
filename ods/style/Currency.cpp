#include "Currency.hpp"

#include "../Book.hpp"
#include "../CurrencyInfo.hpp"
#include "../Ns.hpp"
#include "Manager.hpp"
#include "style.hxx"
#include "tag.hh"
#include "../Tag.hpp"

namespace ods	{ // ods::
namespace style	{ // ods::style::

Currency::Currency(ods::Book *book,
	const ods::StylePlace place) :
	book_(book),
	place_(place)
{
	auto &ns = (place == ods::StylePlace::ContentFile) ?
		book_->content()->ns() : book_->style_manager()->ns();
	tag_ = ods::style::tag::NumberCurrencyStyle(ns, nullptr);
	Init();
}

Currency::~Currency()
{
	if (info_ != nullptr)
		delete info_;
}

ods::Tag*
Currency::GetTag(ods::tag::func f)
{
	auto *tag = tag_->GetSubtag(f);
	if (tag != nullptr)
		return tag;
	tag = f(tag_->ns(), nullptr);
	tag_->SubtagAdd(tag);
	return tag;
}

void
Currency::Init()
{
	SetUniqueName();
}

void
Currency::SetDecimalPlaces(const qint8 lz)
{
	qint8 num = (lz >= 0) ? lz : 0;
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::tag::Number);
	tag->AttrSet(ns.number(), ods::ns::kDecimalPlaces, QString::number(num));
	tag->AttrSet(ns.number(), ods::ns::kMinIntegerDigits, "1");
}

void
Currency::SetInfo(const ods::CurrencyInfo &i)
{
	if (info_ == nullptr)
		info_ = new ods::CurrencyInfo();
	info_->CopyFrom(i);

	auto &ns = tag_->ns();
	SetDecimalPlaces(info_->decimal_places());
	// add gap between currency value and sign
	auto *num_tag = GetTag(ods::tag::NumberText);
	num_tag->SubnodeAdd(new ods::Node(QStringLiteral(" ")));
	auto *tag = GetTag(ods::tag::CurrencySymbol);
	tag->AttrSet(ns.number(), ods::ns::kCountry, info_->country().str);
	tag->AttrSet(ns.number(), ods::ns::kLanguage, info_->language().str);
	auto &currency = info_->currency();
	const QString str = info_->show_symbol() ? currency.sign : currency.iso;
	tag->SubnodeAdd(new ods::Node(str));
}

void
Currency::SetUniqueName()
{
	const QString base = (place_ == ods::StylePlace::StylesFile) ?
		QStringLiteral("curr_st") : QStringLiteral("curr_cn");

	int i = 0;
	while (true)
	{
		name_ = base + QString::number(i++);
		if (book_->GetCurrencyStyle(name_) == nullptr)
			break;
	}
	tag_->AttrSet(tag_->ns().style(), ods::ns::kName, name_);
}

} // ods::style::
} // ods::
