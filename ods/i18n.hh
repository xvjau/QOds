#ifndef ODS_I18N_HH_
#define ODS_I18N_HH_

#include "i18n.hxx"

namespace ods { // ods::
namespace i18n { // ods::i18n::

void
Copy(const ods::i18n::CurrencyType &from, ods::i18n::CurrencyType &to);

bool
Equals(const ods::i18n::CurrencyType &t1, const ods::i18n::CurrencyType &t2);

} // ods::i18n::
} // ods::

#endif
