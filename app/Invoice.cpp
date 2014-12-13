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

#include "Invoice.hpp"
#include "Item.hpp"
#include <QtCore>

namespace app	{ // app::

Invoice::Invoice()
{
	Init();
}

Invoice::~Invoice()
{}

int
Invoice::CreateBillToHeader(const int kLastRow)
{
	int last_row_index = kLastRow + 1;
	auto *row = sheet_->CreateRow(last_row_index);
	
	auto *cell = row->CreateCell(0);
	auto *style = book_.CreateCellStyle();
	style->SetBold(true);
	cell->SetStyle(style);
	cell->SetValue("Bill To:");
	
	const int col1 = 1;
	const int col2 = 5;
	
	row->CreateCell(col1)->SetValue("C20423");
	
	cell = row->CreateCell(col2 - 1);
	cell->SetValue("Ship To:");
	cell->SetStyle(style);
	row->CreateCell(col2)->SetValue("Ship name 1");
	
	row = sheet_->CreateRow(++last_row_index);
	row->CreateCell(col1)->SetValue("ABC company");
	row->CreateCell(col2)->SetValue("Ship Address 1");
	
	row = sheet_->CreateRow(++last_row_index);
	row->CreateCell(col1)->SetValue("232 Brooklyn street");
	row->CreateCell(col2)->SetValue("SH Address 1");
	
	row = sheet_->CreateRow(++last_row_index);
	row->CreateCell(col1)->SetValue("New York");
	row->CreateCell(col2)->SetValue("Whatever");
	
	row = sheet_->CreateRow(++last_row_index);
	row->CreateCell(col1)->SetValue("USA");
	row->CreateCell(col2)->SetValue("Canada");
	
	return last_row_index;
}

int
Invoice::CreateNotes(const int kLastRow)
{
	int last_row_index = kLastRow + 1;
	
	auto *bold_style = book_.CreateCellStyle();
	bold_style->SetBold(true);
	
	auto *row = sheet_->CreateRow(last_row_index);
	auto *cell = row->CreateCell(0);
	cell->SetStyle(bold_style);
	cell->SetValue("Notes:");
	
	auto *border = new ods::style::Border();
	border->SetStyle(ods::BorderStyle::Dotted);
	border->SetWidth(ods::BorderWidth::Thin);
	
	auto *style = book_.CreateCellStyle();
	style->SetBorder(border);
	
	row = sheet_->CreateRow(++last_row_index);
	cell = row->CreateCell(0);
	cell->SetStyle(style);
	cell->SetRowColSpan(6, 5);
	
	last_row_index += cell->num_rows_spanned();
	last_row_index += 2;
	row = sheet_->CreateRow(last_row_index);
	cell = row->CreateCell(0);
	cell->SetValue("Thank You For Your Business!");
	cell->SetRowColSpan(2, 8);
	last_row_index += cell->num_rows_spanned();
	style = book_.CreateCellStyle();
	const int c = 230;
	style->SetBackgroundColor(QColor(c, c, c));
	style->SetHAlignment(ods::HAlign::Center);
	style->SetVAlignment(ods::VAlign::Middle);
	style->SetItalic(true);
	cell->SetStyle(style);
	
	return last_row_index;
}

int
Invoice::CreateSellerHeader()
{
	auto *row1 = sheet_->CreateRow(1);
	auto *cell = row1->CreateCell(0);
	const QString kName = "company-logo.png";
	auto path = QDir(QDir::homePath()).filePath(kName); 
	QFile file(path);
	if (!file.exists())
	{
		
		qDebug() << "If there was " << kName <<
			" in your home dir, I'd also display the \"company logo\".";
	} else {
		auto *draw_frame = cell->CreateDrawFrame(file);
		if (draw_frame == nullptr)
		{
			qDebug() << "draw_image == nullptr";
			return -1;
		}
		draw_frame->SetSize(QSize(60, 60));
	}
	
	auto *style = book_.CreateCellStyle();
	style->SetBold(true);
	style->SetFontSize(18);
	
	const int kCompanyCol = 1;
	const int kShipToCol = 5;
	
	cell = row1->CreateCell(kCompanyCol);
	cell->SetValue("Your company name");
	cell->SetRowColSpan(1, 4);
	cell->SetStyle(style);
	row1->SetOptimalHeightStyle();
	
	auto *row2 = sheet_->CreateRow(2);
	row2->CreateCell(kCompanyCol)->SetValue("Street Address");
	cell = row2->CreateCell(kShipToCol);
	cell->SetRowColSpan(1, 3);
	auto date = QDate::currentDate();
	cell->SetValue(QString("Date: ") + date.toString());
	
	auto *row = sheet_->CreateRow(3);
	row->CreateCell(kCompanyCol)->SetValue("City, ST, ZIP code");
	cell = row->CreateCell(kShipToCol);
	cell->SetRowColSpan(1, 3);
	cell->SetValue("INVOICE #: INVC4203");
	
	row = sheet_->CreateRow(4);
	row->CreateCell(kCompanyCol)->SetValue("Phone number, Web address");
	
	row = sheet_->CreateRow(6);
	auto *top_border = new ods::style::Border();
	top_border->sides_set(ods::BorderSideTop);
	top_border->SetColor(QColor(200, 200, 200));
	top_border->SetWidth("5pt");
	style = book_.CreateCellStyle();
	style->SetBorder(top_border);
	
	for (int i = 0; i <= kShipToCol+2; i++)
	{
		cell = row->CreateCell(i);
		cell->SetStyle(style);
	}
	return 6;
}

int
Invoice::CreateTable(QVector<app::Item*> *vec, const int kLastRow)
{
	int last_row_index = kLastRow + 1;
	
	auto *border = new ods::style::Border();
	border->sides_set(ods::BorderSideLeft | ods::BorderSideRight);
	auto *light_style = book_.CreateCellStyle();
	light_style->SetBorder(border);
	
	auto *dark_style = book_.CreateCellStyle();
	dark_style->SetBorder(border);
	const int c = 230;
	dark_style->SetBackgroundColor(QColor(c, c, c));
	QVector<ods::Cell*> line_total_cells;
	
	for(int i=0; i<vec->size(); i++, last_row_index++)
	{
		auto *item = vec->at(i);
		
		auto *style = (i % 2) ? dark_style : light_style;
		auto *row = sheet_->CreateRow(last_row_index);
		
		auto *cell = row->CreateCell(0);
		QString id_str = QString("IT0") + QString::number(item->id());
		cell->SetValue(id_str);
		cell->SetStyle(style);
		
		cell = row->CreateCell(cell->UpToColumn()+1);
		cell->SetRowColSpan(1, 3);
		cell->SetValue(item->description());
		cell->SetStyle(style);
		
		auto *qtty_cell = row->CreateCell(cell->UpToColumn()+1);
		qtty_cell->SetValue(item->qtty_ordered());
		qtty_cell->SetStyle(style);
		
		auto *price_cell = row->CreateCell(qtty_cell->UpToColumn()+1);
		price_cell->SetValue(item->unit_price());
		price_cell->SetStyle(style);
		
		// Next, one could compute the "line total" and insert the
		// resulting number into "line total", but to make the
		// invoice more fancy and to
		// show off "real world" usage of formulas let's use formulas instead.
		
		auto *formula = new ods::Formula();
		formula->Add(qtty_cell);
		formula->Add(ods::Op::Mult);
		formula->Add(price_cell);
		
		cell = row->CreateCell(price_cell->UpToColumn()+1);
		cell->SetRowColSpan(1, 2);
		cell->SetFormula(formula);
		cell->SetStyle(style);
		
		line_total_cells.append(cell);
	}
	
	auto *top_border = new ods::style::Border();
	top_border->sides_set(ods::BorderSideTop);
	auto *style = book_.CreateCellStyle();
	style->SetBorder(top_border);
	
	auto *row = sheet_->CreateRow(last_row_index++);
	
	auto *cell = row->CreateCell(0);
	cell->SetStyle(style);
	
	cell = row->CreateCell(cell->UpToColumn() + 1);
	cell->SetRowColSpan(1, 3);
	cell->SetStyle(style);
	
	cell = row->CreateCell(cell->UpToColumn() + 1);
	cell->SetStyle(style);
	
	auto *unit_price_cell = row->CreateCell(cell->UpToColumn() + 1);
	unit_price_cell->SetValue("TOTAL:");
	auto *unit_style = style->Derive();
	unit_style->SetHAlignment(ods::HAlign::Right);
	unit_price_cell->SetStyle(unit_style);
	
	
	auto *formula = new ods::Formula();
	const auto kCount = line_total_cells.size();
	for(int i = 0; i < kCount; i++)
	{
		formula->Add(line_total_cells[i]);
		if (i < kCount - 1)
			formula->Add(ods::Op::Add);
	}
	
	auto *total_cell = row->CreateCell(
		unit_price_cell->UpToColumn() + 1);
	total_cell->SetRowColSpan(1, 2);
	total_cell->SetFormula(formula);
	
	border = new ods::style::Border(); // all sides
	auto *total_style = style->Derive();
	total_style->SetBorder(border);
	total_cell->SetStyle(total_style);
	
	return last_row_index;
}

int
Invoice::CreateTableHeader(const int kLastRow)
{
	int last_row_index = kLastRow + 2;
	auto *row = sheet_->CreateRow(last_row_index);
	
	auto *style = book_.CreateCellStyle();
	style->SetBold(true);
	const int c = 220;
	style->SetBackgroundColor(QColor(c, c, c));
	style->SetHAlignment(ods::HAlign::Center);
	auto *border = new ods::style::Border();
	style->SetBorder(border);
	
	auto *cell = row->CreateCell(0);
	cell->SetStyle(style);
	cell->SetValue("ID");
	
	cell = row->CreateCell(cell->UpToColumn()+1);
	cell->SetRowColSpan(1, 3);
	cell->SetStyle(style);
	cell->SetValue("Description");
	
	cell = row->CreateCell(cell->UpToColumn()+1);
	cell->SetStyle(style);
	cell->SetValue("Qtty");
	
	cell = row->CreateCell(cell->UpToColumn()+1);
	cell->SetStyle(style);
	cell->SetValue("Price");
	
	cell = row->CreateCell(cell->UpToColumn()+1);
	cell->SetStyle(style);
	cell->SetRowColSpan(1, 2);
	cell->SetValue("Line Total");
	
	return last_row_index;
}

QVector<app::Item*>*
Invoice::GenItems()
{
	auto *vec = new QVector<app::Item*>();
	vec->append(new app::Item("Motorola F20", 225.5, 10));
	vec->append(new app::Item("Android 4", 310.0, 2));
	vec->append(new app::Item("Nokia MT", 400.0, 20));
	vec->append(new app::Item("MS Vaporware", 100.0, 10));
	vec->append(new app::Item("Intel SP", 180.0, 1));
	vec->append(new app::Item("GM FX 2", 360, 1));
	vec->append(new app::Item("PS 4", 300, 2));
	vec->append(new app::Item("Xbox 2", 150, 5));
	return vec;
}

void
Invoice::Init()
{
	sheet_ = book_.CreateSheet("Invoice");
	int last_index = CreateSellerHeader();
	if (last_index == -1)
	{
		qDebug() << "CreateSellerHeader() failed";
		return;
	}
	last_index = CreateBillToHeader(last_index);
	if (last_index == -1)
	{
		qDebug() << "CreateBillToHeader() failed";
		return;
	}
	last_index = CreateTableHeader(last_index);
	if (last_index == -1)
	{
		qDebug() << "CreateTableHeader() failed";
		return;
	}
	
	QVector<app::Item*> *items = GenItems();
	last_index = CreateTable(items, last_index);
	if (last_index == -1)
	{
		qDebug() << "CreateTable() failed";
		return;
	}
	
	last_index = CreateNotes(last_index);
	if (last_index == -1)
	{
		qDebug() << "CreateNotes() failed";
		return;
	}
	
	auto path = QDir(QDir::homePath()).filePath("Invoice.ods");
	QFile target(path);
	QString err = book_.Save(target);
	if (!err.isEmpty())
		qDebug() << "Error saving ods file:" << err;
	else
		qDebug() << "Saved to" << target.fileName();
}



} // app::
