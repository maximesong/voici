#include "ActionPanel.h"

#include <iostream>
using namespace std;

#include <QVBoxLayout>

#include "ActionButton.h"

void ActionPanel::init()
{
	doCreation();
	doLayout();
	doConnections();
}

ActionPanel::ActionPanel(QWidget *parent)
	: QWidget(parent)
{
	/* empty */
}

void ActionPanel::doCreation()
{
	/* empty */
}

void ActionPanel::doLayout()
{
	QVBoxLayout *layout = new QVBoxLayout();
	for (int i = 0; i != m_buttons.size(); ++i)
		if (m_buttons[i] != 0)
			layout->addWidget(m_buttons[i]);
	setLayout(layout);
}

void ActionPanel::doConnections()
{
	connectActionButtons();
}

void ActionPanel::connectActionButtons()
{
	for (int i = 0; i != m_buttons.size(); ++i)
		if (m_buttons[i] != 0)
			connect(m_buttons[i], SIGNAL(clicked(int)), 
				this, SLOT(processButtonClicked(int)));
}

void ActionPanel::processButtonClicked(int)
{
	/* empty */
}

void ActionPanel::addActionButton(const QString &text, int action)
{
	m_buttons[action] = new ActionButton(text, action);
}
