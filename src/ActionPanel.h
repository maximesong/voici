#ifndef _ACTIONPANEL_H_
#define _ACTIONPANEL_H_

#include <QWidget>
#include <QVector>

#include "Process.h"

class ActionButton;

class ActionPanel : public QWidget {
	Q_OBJECT
public:
	ActionPanel(QWidget *parent = 0);
signals:
	void newProcess(SharedProcess process);		
public slots:
	virtual void processButtonClicked(int action);
protected:
	virtual void init();
	virtual void doCreation();
	virtual void doLayout();
	virtual void doConnections();
	virtual void connectActionButtons();
	QVector<ActionButton*> m_buttons;
};

#endif /* _ACTIONPANEL_H_ */
