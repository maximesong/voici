#include "ContrastPanel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QGridLayout>

#include "ProcessFactory.h"
#include "VoiciGlobal.h"
#include "VoiciMainWindow.h"

ContrastPanel::ContrastPanel(QWidget *parent)
	: QWidget(parent)
{
	QPushButton *histogramEqualizationButton =
		new QPushButton(tr("Histogram Equalization"));

	connect(histogramEqualizationButton, SIGNAL(clicked()), 
		this, SLOT(sendHistogramEqualizationProcess()));

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(histogramEqualizationButton);

	setLayout(layout);
}


void ContrastPanel::sendHistogramEqualizationProcess()
{
	SharedProcess process = ProcessFactory::getHistogramEqualizationProcess(
		mainWindow->getCurrentImage());

	emit newProcess(process);
}

