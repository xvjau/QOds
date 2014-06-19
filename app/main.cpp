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

#include <ods/ods>
#include <mtl/err.hpp>
#include <cstdio>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <QtCore>
#include <QtGui>
#include "Invoice.hpp"

void		Save(ods::Book&);

void
Lesson1CreateEmptyBook()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0); // create first/top row
	
	// Indices are zero based.
	// Create a cell at index 0
	auto *cell = row->CreateCell(0);
	cell->SetValue("cell at 0");
	
	// another cell, at index 5,
	// since it's zero based it's the 6th cell (column)
	cell = row->CreateCell(5);
	cell->SetValue("cell at 5");
	
	Save(book);
}

void
Lesson2CreateCellsOfDifferentTypes()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	// will hold a string value
	cell->SetValue("string");
	
	cell = row->CreateCell(1);
	// will hold a float value
	// Note: internally the API stores/uses numbers as doubles, but the
	// ODF standard seems to use/store as floats
	cell->SetValue(3.14);
	
	Save(book);
}

void
Lesson3UseFontsAndStyles()
{
	/** Note: when applying same style to many cells - don't create a new
	style for each cell, instead use the same style for them. For example:
	
	WRONG:
	for(int i=0; i<10; i++)
	{
		auto *style = book.CreateCellStyle();
		style->SetBackground(QColor(200, 0, 0));
		auto *cell = row->CreateCell(i);
		cell->SetStyle(style);
	}
	
	RIGHT:
	auto *style = book.CreateCellStyle();
	style->SetBackground(QColor(200, 0, 0));
	for(int i=0; i<10; i++)
	{
		auto *cell = row->CreateCell(i);
		cell->SetStyle(style);
	}
	**/
	
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	cell->SetValue("string");
	
	auto *style = book.CreateCellStyle();
	style->SetFontName("Verdana");
	style->SetFontSize(20.0);
	style->SetTextColor(QColor(200, 0, 0));
	cell->SetStyle(style);
	row->SetOptimalHeightStyle();
	
	cell = row->CreateCell(1);
	//derive a new style from parent style and set yellow background
	style = style->Derive();
	style->SetBackgroundColor(QColor(255, 255, 0));
	cell->SetValue(3.14f);
	cell->SetStyle(style);
	
	Save(book);
}

void
Lesson4Alignment()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	cell->SetValue("string");
	auto *style = book.CreateCellStyle();
	style->SetHAlignment(ods::HAlign::Center);
	//aligns the string value "string" of the cell to the center
	cell->SetStyle(style);
	
	cell = row->CreateCell(1);
	cell->SetValue(3.14);
	style = book.CreateCellStyle();
	//aligns the number value "3.14" of the cell to the right
	style->SetHAlignment(ods::HAlign::Right);
	cell->SetStyle(style);
	
	Save(book);
}

void
Lesson5Borders()
{
	// Borders are used by creating a border class and then applying it
	// to a style which then gets applied to the cell
	
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(1);
	
	auto *cell = row->CreateCell(1);
	cell->SetValue("string");
	
	auto *style = book.CreateCellStyle();
	
	auto *base_border = new ods::style::Border();// thin solid black by default
	base_border->SetColor(QColor(0, 0, 255)); // make the border blue
	base_border->SetStyle(ods::BorderStyle::Solid);
	base_border->SetWidth(ods::BorderWidth::Medium);
	style->SetBorder(base_border);
	// cell which contains "string" will have solid blue border all around it
	cell->SetStyle(style);
		
	cell = row->CreateCell(5);
	cell->SetValue(3.14);
	
	auto *top_border = base_border->Derive();
	top_border->sides_set(ods::BorderSideTop);
	top_border->SetColor(QColor(0, 255, 0)); // (top) green border
	top_border->SetWidth("0.05in");
	
	style = book.CreateCellStyle();
	style->SetBorder(top_border);
	// cell which contains "3.14" will only have a (very) thick top green border
	cell->SetStyle(style);
	
	Save(book);
}

void
Lesson6CellSpan()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	cell->SetValue("string");
	// The cell will span over 2 rows and 4 columns.
	cell->SetRowColSpan(2, 4);
	
	Save(book);
}

void
Lesson7UsingImages()
{
	// Images are set on the sheet relative to a cell
	
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(3);
	auto *cell = row->CreateCell(2);
	
	//let's load a .png image "image.png" from the home dir into this cell
	QFile file(QDir(QDir::home()).filePath("image.png"));
	ods::DrawFrame *draw_frame = cell->CreateDrawFrame(file);
	if (draw_frame == nullptr)
	{
		qDebug() << "DrawFrame == nullptr";
		return;
	}
	// optional: resize it
	draw_frame->SetSize(QSize(40, 80));
	// optional: move the image by x,y points relative to the cell
	draw_frame->SetOffset(QPoint(60, 0));
	
	Save(book);
}

void
Lesson8UsingFormulas()
{
	// only very basic formula functionality is supported
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	
	for (int i=2; i<10; i++)
	{
		auto *row = sheet->CreateRow(i);
		
		auto *cell1 = row->CreateCell(1);
		cell1->SetValue(15);
		
		auto *cell2 = row->CreateCell(2);
		cell2->SetValue(i);
		
		// Create a formula that adds the numbers from cell1 and cell2,
		// multiplies that sum by two and applies the
		// resulting formula to cell3.
		// Schematically the formula looks
		// like this: cell3 = "(cell1 + cell2) * 2"
		auto *formula = new ods::Formula();
		formula->Add(ods::Grouping::Open);
		formula->Add(cell1);
		formula->Add(ods::Op::Add);
		formula->Add(cell2);
		formula->Add(ods::Grouping::Close);
		formula->Add(ods::Op::Mult);
		formula->Add(2);
		
		auto *cell3 = row->CreateCell(3);
		cell3->SetFormula(formula);
	}
	
	Save(book);
}

void
Lesson9CreateSampleInvoice()
{
	new app::Invoice();
}

void
Lesson10ReadFile()
{
	auto path = QDir(QDir::homePath()).filePath("ReadFile.ods");
	ods::Book book(path);
	
	// display value of cell at row kRowIndex and column kColIndex:
	const int kRowIndex = 5;
	const int kColIndex = 2;
	auto *sheet = book.sheet(0);
	if (sheet == nullptr)
	{
		qDebug() << "No sheet at 0";
		return;
	}
	auto *row = sheet->row(kRowIndex);
	if (row == nullptr)
	{
		qDebug() << "No row at" << kRowIndex;
		return;
	}
	auto *cell = row->cell(kColIndex);
	if (cell == nullptr)
	{
		qDebug() << "No cell at" << kColIndex;
		return;
	}
	
	if (cell->HasFormula())
	{
		auto *formula = cell->formula();
		auto &value = formula->value();
		qDebug() << "formula value: " << *value.AsDouble();
	} else {
		const ods::Value &value = cell->value();
		if (value.IsDouble())
			qDebug() << "Cell value as double:" << *value.AsDouble();
		else if (value.IsString())
			qDebug() << "Cell value as string:" << *value.AsString();
		else
			qDebug() << "Unknown cell type";
		
	}
}

int
main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	qDebug().nospace() << "ods version: " << ods::version_major() << "."
		<< ods::version_minor();
	
	Lesson9CreateSampleInvoice();
	return 0;
}

void
Save(ods::Book &book)
{
	auto path = QDir(QDir::homePath()).filePath("file.ods");
	QFile target(path);
	QString err = book.Save(target);
	if (!err.isEmpty())
		qDebug() << "Error saving ods file:" << err;
	else
		qDebug() << "Saved to" << target.fileName();
}
