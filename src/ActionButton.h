#ifndef _ACTIONBUTTON_H_
#define _ACTIONBUTTON_H_

#include <QWidget>
#include <QPushButton>

class ActionButton : public QPushButton {
	Q_OBJECT
public:
	ActionButton(const QString &text, int action, QWidget *parent = 0);
//	virtual ~ActionButton();
signals:
	void clicked(int action);
private slots:
	void is_clicked();
private:
	int m_action;
};

#endif /* _ACTIONBUTTON_H_ */
