#ifndef ODS_STYLE_PERCENT_HPP_
#define ODS_STYLE_PERCENT_HPP_

#include "../decl.hxx"
#include "../err.hpp"
#include "../ns.hxx"
#include "../ods.hxx"
#include "../tag.hxx"

namespace ods	{ // ods::
namespace style	{ // ods::style::

class ODS_API Percent
{
public:
	Percent(ods::Book *book, const ods::StylePlace place);
	virtual ~Percent();
	
	qint8
	decimal_places() const { return decimal_places_; }
	
	ods::Tag*
	GetTag(ods::tag::func f);
	
	void
	SetDecimalPlaces(const qint8);
	
	const QString&
	name() { return name_; }
	
	ods::Tag*
	tag() const { return tag_; }

private:
	NO_ASSIGN_COPY_MOVE(Percent);
	
	void
	Init();
	
	void
	SetUniqueName();
	
	bool				add_percent_sign_ = true;
	ods::Book			*book_ = nullptr;
	qint8				decimal_places_ = 0;
	QString				name_;
	ods::StylePlace		place_;
	ods::Tag			*tag_ = nullptr;
};

} // ods::style::
} // ods::
#endif
