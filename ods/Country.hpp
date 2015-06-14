#ifndef ODS_COUNTRY_HPP_
#define ODS_COUNTRY_HPP_

#include "err.hpp"
#include "i18n.hxx"

namespace ods	{ // ods::

class Country
{
public:
	Country();
	virtual ~Country();

private:
	NO_ASSIGN_COPY_MOVE(Country);
};

} // ods::

#endif
