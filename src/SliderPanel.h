#ifndef _SLIDERPANEL_H_
#define _SLIDERPANEL_H_

#include <QWidget>

class SliderPanel : public QWidget {
	Q_OBJECT
public:
	SliderPanel(QWidget *parent);
	SliderPanel(const QString &str = "", QWidget *parent = 0);
	
signals:
	void valueChanged(int value);
public slots:
	void setValue(int value);
private:
	int m_value;
};

#endif /* _SLIDERPANEL_H_ */
