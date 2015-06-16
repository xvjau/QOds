#include "CurrencyInfo.hpp"

namespace ods	{ // ods::

CurrencyInfo::CurrencyInfo()
{}

CurrencyInfo::~CurrencyInfo()
{}

void
CurrencyInfo::CopyFrom(const CurrencyInfo &r)
{
	country_set(r.country());
	currency_set(r.currency());
	decimal_places_set(r.decimal_places());
	language_set(r.language());
	show_symbol_set(r.show_symbol());
}

bool
CurrencyInfo::Equals(const ods::CurrencyInfo &t) const
{
	if (currency_.id != t.currency().id)
		return false;
	if (show_symbol_ != t.show_symbol())
		return false;
	if (country_.id != t.country().id)
		return false;
	if (language_.id != t.language().id)
		return false;
	if (decimal_places_ != t.decimal_places())
		return false;
	return true;
}

} // ods::
