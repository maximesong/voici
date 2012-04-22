#include "ProcessPanel.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>

#include "ActionButton.h"
#include "FilterPanel.h"
#include "TransformPanel.h"
#include "PointOperatorPanel.h"
#include "ContrastPanel.h"
#include "FiltersPanel.h"

ProcessPanel::ProcessPanel(const QImage &image, QWidget *parent)
	: ActionPanel(parent)
{
	init();
}

void ProcessPanel::doCreation()
{
	/* create buttons */
	m_buttons.resize(10);
	m_panels.resize(10);

	addPanel(tr("FilterPanel"), Filter, new FilterPanel());
	addPanel(tr("FiltersPanel"), Filters, new FiltersPanel());
	addPanel(tr("TransformPanel"), Transform, new TransformPanel(800, 600));
	addPanel(tr("Point Operator Panel"), PointOperator,
		 new PointOperatorPanel());
	addPanel(tr("Contrast Panel"), Contrast, new ContrastPanel());

	/* create panels */
}

void ProcessPanel::uncheckAllButton()
{
	for (int i = 0; i != m_buttons.size(); ++i)
		if (m_buttons[i] != 0)
			m_buttons[i]->setChecked(0);
}


void ProcessPanel::addPanel(const QString &text, int action, QWidget *panel)
{
	m_buttons[action] = new ActionButton(text, action);
	m_buttons[action]->setCheckable(1);
	if (action == 0)
		m_buttons[action]->setChecked(1);
	m_panels[action] = panel;
}

void ProcessPanel::doConnections()
{
	ActionPanel::doConnections();
	for (int i = 0; i != m_panels.size(); ++i)
		if (m_panels[i] != 0)
			connect(m_panels[i], SIGNAL(newProcess(SharedProcess)), 
				this, SIGNAL(newProcess(SharedProcess)));
}

void ProcessPanel::doLayout()
{
        /* Buttons Layout */
	buttonsWidget = new QWidget();
	QGridLayout *buttonsLayout = new QGridLayout();
	buttonsWidget->setLayout(buttonsLayout);	

	for (int i = 0; i != m_buttons.size(); ++i)
		if (m_buttons[i] != 0)
			buttonsLayout->addWidget(m_buttons[i], i / 2, i % 2);

	/* Put panels into the stacked widget */
	stackedWidget = new QStackedWidget();
	for (int i = 0; i != m_panels.size(); ++i)
		if (m_panels[i] != 0)
			stackedWidget->addWidget(m_panels[i]);

	QVBoxLayout *panelLayout = new QVBoxLayout();
	QSplitter *splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(buttonsWidget);
	splitter->addWidget(stackedWidget);
	panelLayout->addWidget(splitter);
	setLayout(panelLayout);
}

void ProcessPanel::switchToPanel(int action)
{
	uncheckAllButton();
	m_buttons[action]->setChecked(1);
	stackedWidget->setCurrentWidget(m_panels[action]);
}

void ProcessPanel::processButtonClicked(int action)
{
	switchToPanel(action);
}
