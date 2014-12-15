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
#include <QtCore>
#include "Invoice.hpp"

// ==> Utility functions
void
Save(ods::Book&);

void
PrintOut(ods::Sheet *sheet, const qint32 kRowIndex, const qint32 kColIndex);
// <== Utility functions

void
Lesson1_CreateEmptyBook()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("Sheet1");
	auto *row = sheet->CreateRow(0); // create first/top row

	// Column (cell) count is zero-based, e.g. 0 = 1, 4 = 5.
	
	// Cell with a string value of "cell at 0"
	// Create a cell at column 0 (first column)
	auto *cell = row->CreateCell(0);
	cell->SetValue("cell at 0");

	Save(book);
}

void
Lesson2_CreateCellsOfDifferentTypes()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("Sheet1");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	// will hold a string value
	cell->SetValue("string");
	
	cell = row->CreateCell(1);
	// will hold a float value
	// Note: internally the API stores/uses numbers as doubles, but the
	// ODF standard seems to use/store as floats
	cell->SetValue(3.14);
	
	// Cell with percentage value
	cell = row->CreateCell(2);
	cell->SetPercentageValue(0.8, 2); // 0.8 = 80.00%, second param (2) is
	// the number of leading zeroes after the dot, in this case
	// it's ".00" from "80.00%"
	
	// Cell with another percentage value
	cell = row->CreateCell(3);
	cell->SetPercentageValue(17.2); // 17.2 = 1720%, the second param
	// by default is zero, hence it'll will show up as "1720%" and not
	// as "1720.0%" or "1720.00%".
	
	Save(book);
}

void
Lesson3_UseFontsAndStyles()
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
	
	// We got a big font size in a cell, so when done creating all the cells
	// of the row tell the row to resize itself vertically for the contents
	// of the cell with the biggest font size to be fully visible by default
	// when opened with an office suite like LibreOffice or MS Office.
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
Lesson4_Alignment()
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
Lesson5_Borders()
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
Lesson6_CellSpan()
{
	ods::Book book;
	auto *sheet = book.CreateSheet("name");
	auto *row = sheet->CreateRow(0);
	
	auto *cell = row->CreateCell(0);
	cell->SetValue("string");
	// By default a cell spans over 1 row and 1 column.
	// Make the cell span over 2 rows and 4 columns:
	cell->SetRowColSpan(2, 4);
	
	Save(book);
}

void
Lesson7_UsingImages()
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
Lesson8_UsingFormulas()
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
Lesson9_CreateSampleInvoice()
{
	new app::Invoice();
}

void
Lesson10_ReadFile()
{
	auto path = QDir(QDir::homePath()).filePath("ReadFile.ods");
	ods::Book book(path);
	qDebug() << "";
	
	// print out the value of cell at given row and column indexes:
	auto *sheet = book.sheet(0);
	if (sheet == nullptr)
	{
		qDebug() << "No sheet at 0";
		return;
	}
	
	// print out the values of the first cell of first 5 rows:
	for(int i = 0; i <= 5; i++)
		PrintOut(sheet, i, 0);
}

void
Lesson11_CreateFormulaWithPercentage()
{
	const int col = 2;
	int row = 0;
	ods::Book book;
	auto *sheet = book.CreateSheet("Sheet1");
	
	sheet->CreateRow(row++)->CreateCell(0)->SetValue("My weight");
	sheet->CreateRow(row++)->CreateCell(0)->SetValue("My preferred weight");
	sheet->CreateRow(row++)->CreateCell(0)->SetValue("Percentage I need to lose");
	
	row = 0;
	auto *cell1 = sheet->row(row++)->CreateCell(col);
	auto *cell2 = sheet->row(row++)->CreateCell(col);
	auto *cell3 = sheet->row(row++)->CreateCell(col);
	
	cell1->SetValue(100);
	cell2->SetValue(80);
	
	auto *formula = new ods::Formula();
	formula->Add(ods::Grouping::Open);
	formula->Add(cell1);
	formula->Add(ods::Op::Subtract);
	formula->Add(cell2);
	formula->Add(ods::Grouping::Close);
	formula->Add(ods::Op::Divide);
	formula->Add(cell1);
	
	cell3->SetFormula(formula);
	// Notes:
	// SetPercentageType(..) just like SetPercentageValue(..) under the hood
	// apply a style to the cell so after calling this method you
	// should use the existing style instead of setting a new one.
	// SetPercentageType(1) sets cell type to "percentage", one decimal place
	// after the dot, defaults to zero
	cell3->SetPercentageType(1);
	auto *style = cell3->style();
	// also make the cell's text bold with a yellow background
	style->SetBold();
	style->SetBackgroundColor(QColor(255, 255, 0));
	
	// setting a style on a non-percentage cell:
	style = book.CreateCellStyle();
	cell1->SetStyle(style);
	style->SetBold();
	style->SetBackgroundColor(QColor(215, 255, 215));
	
	Save(book);
}

void
PrintOut(ods::Sheet *sheet, const qint32 kRowIndex, const qint32 kColIndex)
{
	qDebug().nospace() << "Querying cell at row/col: "
		<< kRowIndex << "/" << kColIndex;
	
	auto *row = sheet->row(kRowIndex);
	if (row == nullptr)
	{
		qDebug() << "No row at" << kRowIndex << "\n";
		return;
	}
	auto *cell = row->cell(kColIndex);
	if (cell == nullptr)
	{
		qDebug() << "No cell at" << kColIndex << "\n";
		return;
	}
	
	if (cell->HasFormula())
	{
		auto *formula = cell->formula();
		auto &value = formula->value();
		qDebug() << "formula value: " << *value.AsDouble();
	} else {
		const ods::Value &value = cell->value();
		if (value.IsEmpty())
			qDebug() << "Cell value is empty";
		else if (value.IsDouble())
			qDebug() << "Cell value as double:" << *value.AsDouble();
		else if (value.IsPercentage())
			qDebug() << "Cell value as percentage: " << *value.AsPercentage();
		else if (value.IsString())
			qDebug() << "Cell value as string:" << *value.AsString();
		else
			qDebug() << "Unknown cell type";
		
	}
	qDebug() << "";
}

int
main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	
	qDebug().nospace() << "ods version: " << ods::version_major() << "."
		<< ods::version_minor();
	
	Lesson11_CreateFormulaWithPercentage();
	return 0;
}

void
Save(ods::Book &book)
{
	auto path = QDir(QDir::homePath()).filePath("file.ods");
	QFile target(path);
	QString err = book.Save(target);
	if (err.isEmpty())
		qDebug() << "Saved to" << target.fileName();
	else
		qDebug() << "Error saving ods file:" << err;
}
