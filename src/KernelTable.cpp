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
	rowsBox->setPrefix("r:");
	columnsBox = new QSpinBox();
	columnsBox->setValue(columns);
	columnsBox->setPrefix("c:");
	centerRowBox = new QSpinBox();
	centerRowBox->setValue(centerRow);
	centerRowBox->setPrefix("rx:");
	centerColumnBox = new QSpinBox();
	centerColumnBox->setValue(centerColumn);
	centerColumnBox->setPrefix("cx:");

	connect(rowsBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setRows(int)));

	connect(columnsBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setColumns(int)));

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
	rowsBox->setValue(rows);
	tableWidget->setRowCount(rows);
}

void KernelTable::setColumns(int columns)
{
	columnsBox->setValue(columns);
	tableWidget->setColumnCount(columns);
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
	centerRowBox->setValue(row);
}

void KernelTable::setCenterColumn(int column)
{
	centerColumnBox->setValue(column);
}

void KernelTable::setCenter(int row, int column)
{
	setCenterRow(row);
	setCenterColumn(column);
}

int KernelTable::getRows()
{
	return rowsBox->value();
}

int KernelTable::getColumns()
{
	return columnsBox->value();
}
