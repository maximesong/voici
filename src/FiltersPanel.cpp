#include "FiltersPanel.h"

#include <iostream>
using namespace std;

#include "ActionButton.h"

FiltersPanel::FiltersPanel(QWidget *parent)
	: ActionPanel(parent)
{
	init();
	/* empty */
}

void FiltersPanel::doCreation()
{
	m_buttons.resize(10);
	m_buttons[Test] = new ActionButton(tr("Test Button"), Test);
}

void FiltersPanel::processButtonClicked(int action)
{
	switch (action) {
	case Test:
		cout << "Test Button Clicked" << endl;
		break;
	}
}
