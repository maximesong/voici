#include "KernelTable.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QTableWidget>
#include <QSize>
#include <QVBoxLayout>

#include <iostream>
using namespace std;

KernelTable::KernelTable(int rows, int columns, int centerRow, int centerColumn,
			 QWidget *parent)
	: QWidget(parent) {
	init(rows, columns, centerRow, centerColumn);
}

KernelTable::KernelTable(QWidget *parent)
	: QWidget(parent) {
	init(3, 3, 2, 2);
}

void KernelTable::init(int rows, int columns, int centerRow, int centerColumn)
{
	tableWidget = new QTableWidget(rows, columns);
	for (int i = 0; i != rows; ++i)
		for (int j = 0; j != columns; ++j)
			tableWidget->setItem(i, j, new QTableWidgetItem("0.0"));
	rowsBox = new QSpinBox();
	rowsBox->setValue(rows);
	rowsBox->setPrefix(tr("rows:"));
	columnsBox = new QSpinBox();
	columnsBox->setValue(columns);
	columnsBox->setPrefix(tr("columns:"));
	centerRowBox = new QSpinBox();
	centerRowBox->setPrefix(tr("center row:"));
	centerColumnBox = new QSpinBox();
	centerColumnBox->setPrefix(tr("center column:"));
	setCenter(centerRow, centerColumn);

	connect(rowsBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setRows(int)));

	connect(columnsBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setColumns(int)));

	connect(centerRowBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setCenterRow(int)));

	connect(centerColumnBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setCenterColumn(int)));

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(tableWidget, 0, 0, 4, 4);
	layout->addWidget(rowsBox, 5, 0, 1, 1);
	layout->addWidget(columnsBox, 5, 1, 1, 1);
	layout->addWidget(centerRowBox, 5, 2, 1, 1);
	layout->addWidget(centerColumnBox, 5, 3, 1, 1);

	setLayout(layout);
}

void KernelTable::setRows(int rows)
{
	if (rows <= 0)
		rows = 1;
	rowsBox->setValue(rows);
	tableWidget->setRowCount(rows);
	setCenter(getCenterRow(), getCenterColumn());
}

void KernelTable::setColumns(int columns)
{
	if (columns <= 0)
		columns = 1;
	columnsBox->setValue(columns);
	tableWidget->setColumnCount(columns);
	setCenter(getCenterRow(), getCenterColumn());
}

void KernelTable::setTableSize(int rows, int columns)
{
	setRows(rows);
	setColumns(columns);
}

QVector<double> KernelTable::getMatrix()
{
	QVector<double> matrix;
	int rows = tableWidget->rowCount();
	int columns = tableWidget->columnCount();
	for (int i = 0; i != rows; ++i)
		for (int j = 0; j != columns; ++j) {
			QTableWidgetItem *item = tableWidget->item(i, j);
			double item_value = 0;
			if (item != 0)
				item_value = item->text().toDouble();
			matrix.push_back(item_value);
		}
	return matrix;
}

int KernelTable::getCenterRow()
{
	return centerRowBox->value();
}

int KernelTable::getCenterColumn()
{
	return centerColumnBox->value();
}

void KernelTable::setKernel(int m, int n, int x, int y, const QVector<double> &matrix)
{
	setTableSize(m, n);
	for (int i = 0; i != m; ++i)
		for (int j = 0; j != n; ++j) {
			QTableWidgetItem *item = 
				new QTableWidgetItem(QString::number(matrix[i * n + j]));
			tableWidget->setItem(i, j, item); 
		}
	setCenter(x, y);
}


void KernelTable::setCenterRow(int row)
{
	setCenter(row, getCenterColumn());
}

void KernelTable::setCenterColumn(int column)
{
	setCenter(getCenterRow(), column);
}

void KernelTable::setCenter(int row, int column)
{
	if (row <= 0)
		row = 1;
	if (row > getRows())
		row = getRows();
	if (column <= 0)
		column = 1;
	if (column > getColumns())
		column = getColumns();

	centerRowBox->setValue(row);
	centerColumnBox->setValue(column);

	QTableWidgetItem *item;
	for (int i = 0; i < getRows(); ++i)
		for (int j = 0; j < getColumns(); ++j) {
			item = tableWidget->item(i, j);
			if (item == 0) {
				item = new QTableWidgetItem("0.0");
				tableWidget->setItem(i, j, item);
			}
			if (i + 1 == row && j + 1 == column)
				item->setBackground(QBrush(Qt::gray));
			else
				item->setBackground(QBrush(Qt::white));
		}
}

int KernelTable::getRows()
{
	return rowsBox->value();
}

int KernelTable::getColumns()
{
	return columnsBox->value();
}
