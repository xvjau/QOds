#ifndef ODS_CURRENCYINFO_HPP_
#define ODS_CURRENCYINFO_HPP_

#include "err.hpp"
#include "global.hxx"
#include "i18n.hxx"

namespace ods	{ // ods::

class ODS_API CurrencyInfo
{
public:
	CurrencyInfo();
	virtual ~CurrencyInfo();

	void
	CopyFrom(const CurrencyInfo&);

	const ods::i18n::Country&
	country() const { return country_; }

	void
	country_set(const ods::i18n::Country &c)
	{
		country_.id = c.id;
		country_.str = c.str;
	}

	const ods::i18n::Currency&
	currency() const { return currency_; }

	void
	currency_set(const ods::i18n::Currency &c)
	{
		currency_.id = c.id;
		currency_.iso = c.iso;
		currency_.sign = c.sign;
	}

	qint8
	decimal_places() const { return decimal_places_; }

	void
	decimal_places_set(const qint8 n) { decimal_places_ = n; }

	bool
	Equals(const ods::CurrencyInfo &t) const;

	const ods::i18n::Language&
	language() const { return language_; }

	void
	language_set(const ods::i18n::Language &l)
	{
		language_.id = l.id;
		language_.str = l.str;
	}

	bool
	show_symbol() const { return show_symbol_; }

	void
	show_symbol_set(const bool flag) { show_symbol_ = flag; }

private:
	NO_ASSIGN_COPY_MOVE(CurrencyInfo);

	ods::i18n::Country	country_ = ods::i18n::kGermany;
	ods::i18n::Currency	currency_ = ods::i18n::kEuro;
	qint8				decimal_places_ = 2;
	ods::i18n::Language	language_ = ods::i18n::kGerman;
	bool				show_symbol_ = true;
};

} // ods::

#endif
