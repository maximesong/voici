#include "ActionButton.h"


ActionButton::ActionButton(const QString &text, int action, QWidget *parent)
	: QPushButton(text, parent)
{
	m_action = action;
	connect(this, SIGNAL(clicked()), 
		this, SLOT(is_clicked()));

}

void ActionButton::is_clicked()
{
	emit clicked(m_action);
}
