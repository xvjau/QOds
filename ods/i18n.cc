#include "i18n.hh"

namespace ods { // ods::
namespace i18n { // ods::i18n::

void
Copy(const ods::i18n::CurrencyType &from, ods::i18n::CurrencyType &to)
{
	to.currency.id = from.currency.id;
	to.currency.iso = from.currency.iso;
	to.currency.sign = from.currency.sign;

	to.show_symbol = from.show_symbol;

	to.country.id = from.country.id;
	to.country.str = from.country.str;

	to.language.id = from.language.id;
	to.language.str = from.language.str;

	to.decimal_places = from.decimal_places;
}

bool
Equals(const ods::i18n::CurrencyType &t1, const ods::i18n::CurrencyType &t2)
{
	if (t1.currency.id != t2.currency.id)
		return false;
	if (t1.show_symbol != t2.show_symbol)
		return false;
	if (t1.country.id != t2.country.id)
		return false;
	if (t1.language.id != t2.language.id)
		return false;
	if (t1.decimal_places != t2.decimal_places)
		return false;
	return true;
}

} // ods::i18n::
} // ods::
