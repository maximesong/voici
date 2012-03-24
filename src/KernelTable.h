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
signals:
	void kernelChanged(int rows, int columns, QVector<double> matrix);	
public slots:
	void setRows(int rows);
	void setColumns(int columns);
	void setTableSize(int rows, int columns);
private:
	void init(int rows, int columns, int centerRow, int centerColumn);
	QTableWidget *tableWidget;
	QSpinBox *rowsBox;
	QSpinBox *columnsBox;
	QSpinBox *centerRowBox;
	QSpinBox *centerColumnBox;
};

#endif /* _KERNELTABLE_H_ */
