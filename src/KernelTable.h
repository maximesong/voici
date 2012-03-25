#ifndef _KERNELTABLE_H_
#define _KERNELTABLE_H_

#include <QWidget>
#include <QVector>

class QTableWidget;
class QSpinBox;
class QSize;


class KernelTable : public QWidget {
	Q_OBJECT
public:
	KernelTable(int rows, int columns, int centerRow, int centerColumn,
		    QWidget *parent = 0);
	KernelTable(QWidget *parent = 0);
	QVector<double> getMatrix();
	int getCenterRow();
	int getCenterColumn();
	int getRows();
	int getColumns();
signals:
	void kernelChanged(int rows, int columns, QVector<double> matrix);	
public slots:
	void setRows(int rows);
	void setColumns(int columns);
	void setTableSize(int rows, int columns);
	void setCenterRow(int row);
	void setCenterColumn(int column);
	void setCenter(int row, int column);
	void setKernel(int m, int n, int x, int y, const QVector<double> &matrix);
private:
	void init(int rows, int columns, int centerRow, int centerColumn);
	QTableWidget *tableWidget;
	QSpinBox *rowsBox;
	QSpinBox *columnsBox;
	QSpinBox *centerRowBox;
	QSpinBox *centerColumnBox;
};

#endif /* _KERNELTABLE_H_ */
