#include "ProcessPanel.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>

#include "FilterPanel.h"
#include "TransformPanel.h"
#include "PointOperatorPanel.h"

ProcessPanel::ProcessPanel(const QImage &image, QWidget *parent)
	: QWidget(parent)
{
	filterPanel = new FilterPanel();
	connect(filterPanel, SIGNAL(newProcess(SharedProcess )), 
		this, SIGNAL(newProcess(SharedProcess)));

	transformPanel = new TransformPanel(image.width(), image.height());
	connect(transformPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SIGNAL(newProcess(SharedProcess)));

	pointOperatorPanel = new PointOperatorPanel();
	connect(pointOperatorPanel, SIGNAL(newProcess(SharedProcess)), 
		this, SIGNAL(newProcess(ImageProcess*)));


	filterPanelButton = new QPushButton(tr("Filter Panel"));
	filterPanelButton->setCheckable(1);
	filterPanelButton->setChecked(1);
	connect(filterPanelButton, SIGNAL(clicked()), 
		this, SLOT(switchToFilterPanel()));

	transformPanelButton = new QPushButton(tr("Transform Panel"));
	transformPanelButton->setCheckable(1);
	connect(transformPanelButton, SIGNAL(clicked()), 
		this, SLOT(switchToTransformPanel()));

	
	
	pointOperatorPanelButton = new QPushButton(tr("Point Operator Panel"));
	pointOperatorPanelButton->setCheckable(1);
	connect(pointOperatorPanelButton, SIGNAL(clicked()), 
		this, SLOT(switchToPointOperatorPanel()));

        /* Buttons Layout */
	buttonsWidget = new QWidget();
	QHBoxLayout *buttonsLayout = new QHBoxLayout();
	buttonsWidget->setLayout(buttonsLayout);	


	buttonsLayout->addWidget(filterPanelButton);
	buttonsLayout->addWidget(transformPanelButton);
	buttonsLayout->addWidget(pointOperatorPanelButton);

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(filterPanel);
	stackedWidget->addWidget(transformPanel);
	stackedWidget->addWidget(pointOperatorPanel);

	QVBoxLayout *panelLayout = new QVBoxLayout();
	QSplitter *splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(buttonsWidget);
	splitter->addWidget(stackedWidget);
	panelLayout->addWidget(splitter);
	setLayout(panelLayout);
}

void ProcessPanel::switchToFilterPanel()
{
	uncheckAllButton();
	filterPanelButton->setChecked(1);
	stackedWidget->setCurrentWidget(filterPanel);
}

void ProcessPanel::switchToTransformPanel()
{
	uncheckAllButton();
	transformPanelButton->setChecked(1);
	stackedWidget->setCurrentWidget(transformPanel);
}

void ProcessPanel::switchToPointOperatorPanel()
{
	uncheckAllButton();
	pointOperatorPanelButton->setChecked(1);
	stackedWidget->setCurrentWidget(pointOperatorPanel);
}

void ProcessPanel::uncheckAllButton()
{
	filterPanelButton->setChecked(0);
	transformPanelButton->setChecked(0);
	pointOperatorPanelButton->setChecked(0);
}
