/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting documentation, and
 * that the name of the copyright holders not be used in advertising or
 * publicity pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no representations
 * about the suitability of this software for any purpose.  It is provided "as
 * is" without express or implied warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THIS SOFTWARE.
 */

#include "Book.hpp"
#include "Cell.hpp"
#include "DrawFrame.hpp"
#include "filename.hxx"
#include "i18n.hh"
#include "Manifest.hpp"
#include "Meta.hpp"
#include "Row.hpp"
#include "Settings.hpp"
#include "Sheet.hpp"
#include "Style.hpp"
#include "style/Currency.hpp"
#include "style/Manager.hpp"
#include "style/Percent.hpp"
#include "style/tag.hh"
#include "style/StyleFamily.hpp"
#include "Tag.hpp"
#include "tag.hh"
#include <QFile>
#include <QXmlStreamWriter>
#include <quazip/JlCompress.h>

static const bool kDoRemove = true;

namespace ods	{

Book::Book()
{
	temp_dir_.setAutoRemove(kDoRemove);
	InitTempDir();
}

Book::Book(const QString &file_path)
{
	temp_dir_.setAutoRemove(kDoRemove);
	InitTempDir();
	Read(file_path);
}

Book::~Book()
{
	delete content_;
	delete meta_;
	delete settings_;
	delete style_manager_;
	foreach (auto *item, percent_styles_)
		delete item;
	foreach (auto *item, styles_)
		delete item;
}

void
Book::Add(ods::DrawFrame *df)
{
	static const auto kPrefix = QStringLiteral("id");
	int i = 0;
	QString new_id;
	while (true)
	{
		again:
		new_id = kPrefix + QString::number(i++);
		foreach (auto *item, draw_frames_)
		{
			if (item->id() == new_id)
				goto again;
		}
		break;
	}
	
	df->id_set(new_id);
	draw_frames_.append(df);
	int n = draw_frames_.size();
	df->zindex_set (n);
	manifest_->Add(df);
}

ods::style::Currency*
Book::CreateCurrencyStyle(const ods::StylePlace place)
{
	if (content_ == nullptr)
		InitDefault();
	auto *currency_style = new ods::style::Currency(this, place);
	currency_styles_.append(currency_style);
	auto *parent_tag = (place == ods::StylePlace::StylesFile) ?
		style_manager_->styles_tag() : content_->automatic_styles_tag();
	auto *tag = currency_style->tag();
	parent_tag->subnodes().append(new ods::Node(tag));
	return currency_style;
}

ods::style::Percent*
Book::CreatePercentStyle(const ods::StylePlace place)
{
	if (content_ == nullptr)
		InitDefault();
	auto *percent_style = new ods::style::Percent(this, place);
	percent_styles_.append(percent_style);
	auto *parent_tag = (place == ods::StylePlace::StylesFile) ?
		style_manager_->styles_tag() : content_->automatic_styles_tag();
	auto *tag = percent_style->tag();
	parent_tag->subnodes().append(new ods::Node(tag));
	return percent_style;
}

ods::Sheet*
Book::CreateSheet(const QString &sheet_name)
{
	if (content_ == nullptr)
		InitDefault();
	return content_->CreateSheet(sheet_name);
}

ods::Style*
Book::CreateStyle(const ods::StyleFamilyId id, const ods::StylePlace place,
	ods::tag::func func)
{
	if (content_ == nullptr || style_manager_ == nullptr)
		InitDefault();
	auto &ns = content_->ns();
	auto *tag = func(ns, nullptr);
	auto *family = new ods::style::StyleFamily(id);
	auto *style = new ods::Style(this, tag, family, place);
	styles_.append(style);

	ods::Tag *style_parent_tag;
	if (id == ods::StyleFamilyId::Sheet || id == ods::StyleFamilyId::Row)
		style_parent_tag = content_->automatic_styles_tag();
	else if (place == ods::StylePlace::StylesFile)
		style_parent_tag = style_manager_->styles_tag();
	else
		style_parent_tag = content_->automatic_styles_tag();

	style_parent_tag->subnodes().append(new ods::Node(tag));
	return style;
}

ods::Style*
Book::CreateStyle(const ods::StyleFamilyId id, const ods::StylePlace place)
{
	return CreateStyle(id, place, ods::style::tag::Style);
}

ods::style::Currency*
Book::GetCurrencyStyle(const ods::i18n::CurrencyType *kCurrencyType)
{
	if (kCurrencyType == nullptr)
	{
		if (currency_styles_.isEmpty())
			return nullptr;
		return currency_styles_[0];
	}
	foreach (auto *item, currency_styles_)
	{
		if (item->currency_type() == nullptr)
			continue;

		if (ods::i18n::Equals(*item->currency_type(), *kCurrencyType))
			return item;
	}
	return nullptr;
}

ods::style::Currency*
Book::GetCurrencyStyle(const QString &name)
{
	foreach (auto *item, currency_styles_)
	{
		if (name == item->name())
			return item;
	}
	return nullptr;
}

QString*
Book::GetMediaDirPath()
{
	if (!media_dir_path_.isEmpty())
		return &media_dir_path_;
	QDir dir(QDir(temp_dir_path_).filePath(ods::filename::kMediaDirName));
	if (!dir.exists())
	{
		if (!dir.mkpath("."))
			return nullptr;
	}
	media_dir_path_ = dir.absolutePath();
	return &media_dir_path_;
}

ods::style::Percent*
Book::GetPercentStyle(const qint8 decimal_places)
{
	foreach (auto *item, percent_styles_)
	{
		if (decimal_places == item->decimal_places())
			return item;
	}
	return nullptr;
}

ods::style::Percent*
Book::GetPercentStyle(const QString &name, const qint8 decimal_places)
{
	foreach (auto *item, percent_styles_)
	{
		if (decimal_places >= 0 && decimal_places != item->decimal_places())
			continue;
		if (name == item->name())
			return item;
	}
	return nullptr;
}

ods::Style*
Book::GetStyle(const QString &name, const ods::StyleFamilyId id)
{
	foreach (auto *style, styles_)
	{
		if (id != style->style_family()->id())
			continue;
		if (name == style->name())
			return style;
	}
	return nullptr;
}

void
Book::InitDefault()
{
	content_ = new ods::Content(this);
	style_manager_ = new ods::style::Manager(this);
	
	meta_ = new ods::Meta(this);
	manifest_ = new ods::Manifest(this);
	content_->InitDefault();
	style_manager_->InitDefault();
}

void
Book::InitTempDir()
{
	if (!dev_mode_)
	{
		temp_dir_path_ = temp_dir_.path();
		return;
	}
	temp_dir_path_ = QDir(QDir::homePath()).filePath("file");
	QDir dir(temp_dir_path_);
	if (!dir.mkpath("."))
		mtl_warn("Can't create temp dir");
}

void
Book::PrepareDir(const QString &save_dir, QString &err)
{
	QDir dir(save_dir);
	if (dir.exists()) {
		if (!dir.removeRecursively()) {
			err = QString(SRC_FILE_NAME) + ": Failed to remove dir";
			return;
		}
	}
	if (!dir.mkpath("."))
		err = QString(SRC_FILE_NAME) + ": Failed to create dir";
}

void
Book::Read(const QString &file_path)
{
	if (!dev_mode_ && !temp_dir_.isValid()) {
		mtl_warn("temp dir invalid");
		return;
	}
	extracted_file_paths_ = JlCompress::extractDir(file_path, temp_dir_path_);
	manifest_ = new ods::Manifest(this);
	content_ = new ods::Content(this);
	meta_ = new ods::Meta(this);
	style_manager_ = new ods::style::Manager(this);
	if (manifest_->HasSettings())
		settings_ = new ods::Settings(this);
}

QString
Book::Save(const QFile &target)
{
	QString save_dir = temp_dir_path_;
	SaveMimeTypeFile(save_dir);
	QString err;

	if (content_ != nullptr)
		content_->Save(save_dir, err);
	if (!err.isEmpty())
		return err;

	if (style_manager_ != nullptr)
		style_manager_->Save(save_dir, err);
	if (!err.isEmpty())
		return err;

	if (manifest_ != nullptr)
		manifest_->Save(save_dir, err);
	if (!err.isEmpty())
		return err;

	if (meta_ != nullptr)
		meta_->Save(save_dir, err);
	if (!err.isEmpty())
		return err;

	if (settings_ != nullptr)
	{
		settings_->Save(save_dir, err);
		if (!err.isEmpty())
			return err;
	}

	QString ods_path = target.fileName();
	if (!JlCompress::compressDir(ods_path, save_dir))
		return "Failed to compress dir";

	return err;
}

void
Book::SaveMimeTypeFile(const QString &dir_path)
{
	QFile file(dir_path + QStringLiteral("/") + ods::filename::kMimeType);
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QTextStream out(&file);
	out << QStringLiteral("application/vnd.oasis.opendocument.spreadsheet");
	file.close(); 
}

void
Book::WriteStartDocument(QXmlStreamWriter &xml)
{
	xml.setAutoFormatting(true);
	xml.setAutoFormattingIndent(-1);
	xml.writeStartDocument(QStringLiteral("1.0"), true);
}

} // namespace ods















