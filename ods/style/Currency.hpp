#ifndef ODS_STYLE_CURRENCY_HPP_
#define ODS_STYLE_CURRENCY_HPP_

#include "../decl.hxx"
#include "../err.hpp"
#include "../i18n.hxx"
#include "../ns.hxx"
#include "../ods.hxx"
#include "../tag.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API Currency
{
public:
	Currency(ods::Book*, const ods::StylePlace);
	virtual ~Currency();

	const ods::i18n::CurrencyType*
	currency_type() const { return currency_type_; }

	const QString&
	name() { return name_; }

	void
	SetType(const ods::i18n::CurrencyType *kCurrencyType);

	ods::Tag*
	tag() const { return tag_; }

private:
	NO_ASSIGN_COPY_MOVE(Currency);

	ods::Tag*
	GetTag(ods::tag::func f);

	void
	Init();

	void
	SetDecimalPlaces(const qint8);

	void
	SetUniqueName();

	ods::Book			*book_ = nullptr;
	ods::i18n::CurrencyType *currency_type_ = nullptr;
	QString				name_;
	ods::StylePlace		place_;
	ods::Tag			*tag_ = nullptr;
};

} // ods::style::
} // ods::

#endif
