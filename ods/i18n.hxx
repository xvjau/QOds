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

const Country kBrazil { ods::i18n::Id::Brazil, QStringLiteral("BR") };
const Country kCanada { ods::i18n::Id::Canada, QStringLiteral("CA") };
const Country kChina { ods::i18n::Id::China, QStringLiteral("CN") };
const Country kFrance { ods::i18n::Id::France, QStringLiteral("FR") };
const Country kGermany { ods::i18n::Id::Germany, QStringLiteral("DE") };
const Country kIndia { ods::i18n::Id::India, QStringLiteral("IN") };
const Country kItaly { ods::i18n::Id::Italy, QStringLiteral("IT") };
const Country kLuxembourg { ods::i18n::Id::Luxembourg, QStringLiteral("LU") };
const Country kPakistan { ods::i18n::Id::Pakistan, QStringLiteral("PK") };
const Country kRussia { ods::i18n::Id::Russia, QStringLiteral("RU") };
const Country kSpain { ods::i18n::Id::Spain, QStringLiteral("ES") };
const Country kSweden { ods::i18n::Id::Sweden, QStringLiteral("SE") };
const Country kTurkey { ods::i18n::Id::Turkey, QStringLiteral("TR") };
const Country kUK { ods::i18n::Id::UK, QStringLiteral("GB") };
const Country kUSA { ods::i18n::Id::USA, QStringLiteral("US") };

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

const Currency kUSD = { CurrencyId::USD, QStringLiteral("$"), QStringLiteral("USD") };
const Currency kEuro = { CurrencyId::Euro, QStringLiteral("€"), QStringLiteral("EUR") };
const Currency kGbPound = { CurrencyId::GbPound, QStringLiteral("₤"), QStringLiteral("GBP") };
const Currency kRenminbi = { CurrencyId::Renminbi, QStringLiteral("¥"), QStringLiteral("CNY") };
const Currency kRusRuble = { CurrencyId::RusRuble, QStringLiteral("₽"), QStringLiteral("RUB") };

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

const Language kArabic { LanguageId::Arabic, QStringLiteral("ar") };
const Language kChinese { LanguageId::Chinese, QStringLiteral("zh") };
const Language kEnglish { LanguageId::English, QStringLiteral("en") };
const Language kFrench { LanguageId::French, QStringLiteral("fr") };
const Language kGerman { LanguageId::German, QStringLiteral("de") };
const Language kItalian { LanguageId::Italian, QStringLiteral("it") };
const Language kPortuguese { LanguageId::Portuguese, QStringLiteral("pt") };
const Language kRussian { LanguageId::Russian, QStringLiteral("ru") };
const Language kSpanish { LanguageId::Spanish, QStringLiteral("es") };
const Language kTurkish { LanguageId::Turkish, QStringLiteral("tr") };

} // ods::i18n::
} // ods::

#endif
