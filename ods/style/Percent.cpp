#include "Percent.hpp"

#include "../Book.hpp"
#include "../Ns.hpp"
#include "Manager.hpp"
#include "style.hxx"
#include "tag.hh"
#include "../Tag.hpp"

namespace ods	{ // ods::
namespace style	{ // ods::style::

Percent::Percent(ods::Book *book,
	const ods::StylePlace place) :
	book_(book),
	place_(place)
{
	auto &ns = (place == ods::StylePlace::ContentFile) ?
		book_->content()->ns() : book_->style_manager()->ns();
	tag_ = ods::tag::NumberPercentageStyle(ns, nullptr);
	Init();
}

Percent::~Percent()
{}

ods::Tag*
Percent::GetTag(ods::tag::func f)
{
	auto *tag = tag_->GetSubtag(f);
	if (tag != nullptr)
		return tag;
	tag = f(tag_->ns(), nullptr);
	tag_->SubtagAdd(tag);
	return tag;
}

void
Percent::Init()
{
	SetUniqueName();
}

void
Percent::SetDecimalPlaces(const qint8 lz)
{
	decimal_places_ = (lz >= 0) ? lz : 0;
	auto &ns = tag_->ns();
	auto *tag = GetTag(ods::tag::Number);
	tag->AttrSet(ns.number(), ods::ns::kDecimalPlaces,
		QString::number(decimal_places_));
	tag->AttrSet(ns.number(), ods::ns::kMinIntegerDigits, "1");
	
	if (add_percent_sign_)
	{
		add_percent_sign_ = false;
		auto *tag = GetTag(ods::tag::NumberText);
		tag->SubnodeAdd(new ods::Node(QStringLiteral("%")));
	}
}

void
Percent::SetUniqueName()
{
	const QString base = (place_ == ods::StylePlace::StylesFile) ?
		QStringLiteral("psst") : QStringLiteral("pscn");
	
	int i = 0;
	while (true)
	{
		name_ = base + QString::number(i++);
		if (book_->GetPercentStyle(name_) == nullptr)
			break;
	}
	tag_->AttrSet(tag_->ns().style(), ods::ns::kName, name_);
}

} // ods::style::
} // ods::
