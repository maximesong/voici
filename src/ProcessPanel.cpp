#include "ProcessPanel.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QSplitter>

#include "ImageProcess.h"
#include "FilterPanel.h"
#include "TransformPanel.h"

ProcessPanel::ProcessPanel(QWidget *parent)
	: QWidget(parent)
{
	filterPanel = new FilterPanel();
	connect(filterPanel, SIGNAL(newProcess(ImageProcess *)), 
		this, SIGNAL(newProcess(ImageProcess *)));

	transformPanel = new TransformPanel();
	connect(transformPanel, SIGNAL(newProcess(ImageProcess *)), 
		this, SIGNAL(newProcess(ImageProcess *)));



	QPushButton *filterPanelButton = new QPushButton(tr("Filter Panel"));
	connect(filterPanelButton, SIGNAL(clicked()), 
		this, SLOT(switchToFilterPanel()));

	QPushButton *transformPanelButton = new QPushButton(tr("Transform Panel"));
	connect(transformPanelButton, SIGNAL(clicked()), 
		this, SLOT(switchToTransformPanel()));


        /* Buttons Layout */
	buttonsWidget = new QWidget();
	QVBoxLayout *buttonsLayout = new QVBoxLayout();
	buttonsWidget->setLayout(buttonsLayout);	


	buttonsLayout->addWidget(filterPanelButton);
	buttonsLayout->addWidget(transformPanelButton);

	stackedWidget = new QStackedWidget();
	stackedWidget->addWidget(filterPanel);
	stackedWidget->addWidget(transformPanel);

	QVBoxLayout *panelLayout = new QVBoxLayout();
	QSplitter *splitter = new QSplitter(Qt::Vertical);
	splitter->addWidget(buttonsWidget);
	splitter->addWidget(stackedWidget);
	panelLayout->addWidget(splitter);
	setLayout(panelLayout);
}

void ProcessPanel::switchToFilterPanel()
{
	stackedWidget->setCurrentWidget(filterPanel);
}

void ProcessPanel::switchToTransformPanel()
{
	stackedWidget->setCurrentWidget(transformPanel);
}
