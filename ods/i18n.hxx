#ifndef ODS_I18N_HXX_
#define ODS_I18N_HXX_

#include <QtGlobal>
#include <QString>

namespace ods	{ // ods::
namespace i18n	{ // ods::i18n::

enum class Id : quint16 {
	NotSet = 0,
	Brazil,
	Canada,
	China,
	France,
	Germany,
	India,
	Italy,
	Luxembourg,
	Pakistan,
	Russia,
	Spain,
	Sweden,
	Turkey,
	UK,
	USA
};

struct Country {
	ods::i18n::Id id;
	QString str;
};

const Country kBrazil { ods::i18n::Id::Brazil, "BR" };
const Country kCanada { ods::i18n::Id::Canada, "CA" };
const Country kChina { ods::i18n::Id::China, "CN" };
const Country kFrance { ods::i18n::Id::France, "FR" };
const Country kGermany { ods::i18n::Id::Germany, "DE" };
const Country kIndia { ods::i18n::Id::India, "IN" };
const Country kItaly { ods::i18n::Id::Italy, "IT" };
const Country kLuxembourg { ods::i18n::Id::Luxembourg, "LU" };
const Country kPakistan { ods::i18n::Id::Pakistan, "PK" };
const Country kRussia { ods::i18n::Id::Russia, "RU" };
const Country kSpain { ods::i18n::Id::Spain, "ES" };
const Country kSweden { ods::i18n::Id::Sweden, "SE" };
const Country kTurkey { ods::i18n::Id::Turkey, "TR" };
const Country kUK { ods::i18n::Id::UK, "GB" };
const Country kUSA { ods::i18n::Id::USA, "US" };

enum class CurrencyId : quint16 {
	USD,
	Euro,
	GbPound, // British pound
	Renminbi, // Chinese
	RusRuble // Russian
};

struct Currency {
	CurrencyId id;
	QString sign;
	QString iso;
};

const Currency kUSD = { CurrencyId::USD, "$", "USD" };
const Currency kEuro = { CurrencyId::Euro, "€", "EUR" };
const Currency kGbPound = { CurrencyId::GbPound, "₤", "GBP" };
const Currency kRenminbi = { CurrencyId::Renminbi, "¥", "CNY" };
const Currency kRusRuble = { CurrencyId::RusRuble, "₽", "RUB" };

enum class LanguageId : quint16 {
	NotSet = 0,
	Arabic,
	Chinese,
	English,
	French,
	German,
	Italian,
	Portuguese,
	Russian,
	Spanish,
	Turkish
};

struct Language {
	ods::i18n::LanguageId	id;
	QString str;
};

const Language kArabic { LanguageId::Arabic, "ar" };
const Language kChinese { LanguageId::Chinese, "zh" };
const Language kEnglish { LanguageId::English, "en" };
const Language kFrench { LanguageId::French, "fr" };
const Language kGerman { LanguageId::German, "de" };
const Language kItalian { LanguageId::Italian, "it" };
const Language kPortuguese { LanguageId::Portuguese, "pt" };
const Language kRussian { LanguageId::Russian, "ru" };
const Language kSpanish { LanguageId::Spanish, "es" };
const Language kTurkish { LanguageId::Turkish, "tr" };

} // ods::i18n::
} // ods::

#endif
