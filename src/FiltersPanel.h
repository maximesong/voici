#ifndef _FILTERSPANEL_H_
#define _FILTERSPANEL_H_

#include "ActionPanel.h"

class FiltersPanel : public ActionPanel {
	Q_OBJECT
public:
	enum Action {Test};
	FiltersPanel(QWidget *parent = 0);
public slots:

protected:
	virtual void doCreation();
	virtual void processButtonClicked(int action);
};

#endif /* _FILTERSPANEL_H_ */
