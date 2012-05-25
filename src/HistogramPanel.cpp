#include "HistogramPanel.h"

#include <iostream>
using namespace std;

#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>

#include "ImageFamily.h"
#include "HistogramChart.h"
#include "ThresholdPanel.h"
#include "OtsuAlgorithm.h"
#include "EntropyMethod.h"
#include "ProcessFactory.h"
#include "VoiciMainWindow.h"
#include "KapurAlgorithm.h"

HistogramPanel::HistogramPanel(ImageFamily *imageCore, QWidget *parent)
	: QWidget(parent) {
	histogramChart = new HistogramChart();
	thresholdPanel = new ThresholdPanel();
	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		histogramChart, SLOT(setThreshold(int, int)));

	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		this, SLOT(setThreshold(int, int)));
	
	otsuButton = new QPushButton(tr("OTSU"));
	connect(otsuButton, SIGNAL(clicked()), 
		this, SLOT(setOtsu()));

	entropyButton = new QPushButton(tr("Entropy"));
	connect(entropyButton, SIGNAL(clicked()), 
		this, SLOT(setEntropy()));

	kapurButton = new QPushButton(tr("KAPUR"));
	connect(kapurButton, SIGNAL(clicked()), 
		this, SLOT(setKapur()));

	checkbox = new QCheckBox(tr("Apply Threshold"));
	connect(checkbox, SIGNAL(stateChanged(int)), 
		this, SLOT(enableThreshold(int)));

	QGroupBox *buttonGroup = new QGroupBox(tr("Threshold Algorithms"));
	QVBoxLayout *groupBoxLayout = new QVBoxLayout();
	buttonGroup->setLayout(groupBoxLayout);
	groupBoxLayout->addWidget(otsuButton);
	groupBoxLayout->addWidget(entropyButton);
	groupBoxLayout->addWidget(kapurButton);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(histogramChart);
	layout->addWidget(thresholdPanel);
	layout->addWidget(buttonGroup);
	layout->addWidget(checkbox);
	setLayout(layout);

	updateHistogramPanel(*imageCore);
}

void HistogramPanel::updateHistogramPanel(const ImageFamily &imageCore)
{
	histogramChart->drawChart(imageCore);
}

void HistogramPanel::enableThreshold(int state)
{
	if (state == Qt::Checked) {
		thresholdPanel->refreshThreshold();
		SharedProcess process = ProcessFactory::getBinaryProcess(
			thresholdPanel->getLow(),
			thresholdPanel->getHigh(),
			mainWindow->getArea());
		emit newProcess(process);
	}
	else {
		SharedProcess process = 
			ProcessFactory::getUnsetThredsholdProcess();
		emit newProcess(process);
	}
}

void HistogramPanel::setThreshold(int low, int high)
{
	if (checkbox->checkState()== Qt::Checked) {
		thresholdPanel->setThreshold(low, high);
		SharedProcess process = 
			ProcessFactory::getBinaryProcess(low,
							 high,
							 mainWindow->getArea());
		emit newProcess(process);
	} else {
		thresholdPanel->quietlySetThreshold(low, high);
	}
}

void HistogramPanel::setOtsu()
{
	Histogram histogram = histogramChart->getHistogram();
	int threshold = OtsuAlgorithm::computeThreshold(histogram);
	setThreshold(0, threshold);
}

void HistogramPanel::setEntropy()
{
	Histogram histogram = histogramChart->getHistogram();
	int threshold = EntropyMethod::computeThreshold(histogram);
	setThreshold(0, threshold);
}

void HistogramPanel::setKapur()
{
	Histogram histogram = histogramChart->getHistogram();
	int threshold = KapurAlgorithm::computeThreshold(histogram);
	setThreshold(0, threshold);
}
