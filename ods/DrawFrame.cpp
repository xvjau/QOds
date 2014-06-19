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

#include "DrawFrame.hpp"
#include "Book.hpp"
#include "Cell.hpp"
#include "filename.hxx"
#include "Ns.hpp"
#include "ns.hxx"
#include "Row.hpp"
#include "Sheet.hpp"
#include "style/style.hxx"
#include "util.hh"
#include <QDir>
#include <QImageReader>

namespace ods	{ // ods::

static const auto in = QStringLiteral("in");

DrawFrame::DrawFrame(ods::Cell *cell, const QFile &file) :
cell_(cell)
{
	Init(file);
}

DrawFrame::~DrawFrame()
{}

QString
DrawFrame::GetRelativeUri() {
	return QString(ods::filename::kMediaDirName) + QStringLiteral("/")
		+ file_name_;
}

ods::Tag*
DrawFrame::GetTag(ods::tag::func f)
{
	auto *tag = tag_->GetSubtag(f);
	if (tag == nullptr)
	{
		tag = f(tag_->ns(), nullptr);
		tag_->SubtagAdd(tag);
	}
	return tag;
}

void
DrawFrame::Init(const QFile &file)
{
	state_ = ods::State::Ok;
	auto *book = cell_->row()->sheet()->book();
	QString *media_dir_path = book->GetMediaDirPath();
	if (media_dir_path == nullptr)
	{
		mtl_warn("media_dir_path == nullptr");
		state_ = ods::State::Fail;
		return;
	}
	//const auto kMimeType = ods::util::GetMimeType(file.fileName());
	auto info = QFileInfo(file.fileName());
	const auto kMaxSize = 1024 * 1024 * 100; // 100MB
	if (info.size() > kMaxSize)
	{
		state_ = ods::State::FileTooLarge;
		return;
	}
	const auto kExt = QStringLiteral(".") + info.suffix();
	static const auto kImg = QStringLiteral("image");
	QDir dir(*media_dir_path);
	qint32 i = 0;
	while (true)
	{
		const auto kFileName = kImg + QString::number(i++) + kExt;
		file_.setFileName(dir.filePath(kFileName));
		if (!file_.exists())
		{
			file_name_ = kFileName;
			break;
		}
	}
	const bool ok = QFile::copy(file.fileName(), file_.fileName());
	if (ok) {
		cell_->row()->sheet()->book()->Add(this);
		UpdateTag();
	} else {
		state_ = ods::State::FailCopy;
	}
}

void
DrawFrame::SetOffset(const QPoint &p)
{
	QString x = QString::number(p.x() * ods::kInchesInAPoint) + in;
	QString y = QString::number(p.y() * ods::kInchesInAPoint) + in;
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.svg(), ods::ns::kX, x);
	tag_->AttrSet(ns.svg(), ods::ns::kY, y);
}

void
DrawFrame::SetSize(const QSize &size)
{
	current_image_size_ = size;
	QString w = QString::number(size.width() * ods::kInchesInAPoint) + in;
	QString h = QString::number(size.height() * ods::kInchesInAPoint) + in;
	auto &ns = tag_->ns();
	tag_->AttrSet(ns.svg(), ods::style::kWidth, w);
	tag_->AttrSet(ns.svg(), ods::style::kHeight, h);
}

void
DrawFrame::UpdateTag()
{
	auto &ns = cell_->tag()->ns();
	if (tag_ == nullptr)
	{
		tag_ = cell_->GetDrawFrameTag();
	}
	tag_->AttrSet(ns.draw(), ods::style::kZIndex, QString::number(zindex_));
	tag_->AttrSet(ns.draw(), ods::ns::kId, id_);
	tag_->AttrSet(ns.draw(), ods::ns::kName, file_name_);
	// no style name
	SetOffset(QPoint(0, 0));
	
	mime_type_ = ods::util::GetMimeType(file_.fileName());

	QImageReader reader(&file_);
	real_image_size_ = reader.size();
	current_image_size_ = real_image_size_;
	SetSize(real_image_size_);
	
	static const auto kScale = QStringLiteral("scale");
	tag_->AttrSet(ns.style(), ods::style::kRelWidth, kScale);
	tag_->AttrSet(ns.style(), ods::style::kRelHeight, kScale);
	
	auto *img_tag = GetTag(ods::tag::DrawImage);
	img_tag->AttrSet(ns.xlink(), ods::ns::kHref, GetRelativeUri());
	img_tag->AttrSet(ns.xlink(), ods::ns::kType, QStringLiteral("simple"));
	img_tag->AttrSet(ns.xlink(), ods::ns::kShow, QStringLiteral("embed"));
	img_tag->AttrSet(ns.xlink(), ods::ns::kActuate, QStringLiteral("onLoad"));
	
	GetTag(ods::tag::SvgDesc);
	GetTag(ods::tag::SvgTitle);
}

} // ods::
