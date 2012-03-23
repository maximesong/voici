#include "HistogramPanel.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>

#include "ImageCore.h"
#include "HistogramChart.h"
#include "ThresholdPanel.h"
#include "OtsuAlgorithm.h"

HistogramPanel::HistogramPanel(ImageCore *imageCore, QWidget *parent)
	: QWidget(parent) {
	histogramChart = new HistogramChart();
	thresholdPanel = new ThresholdPanel();
	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		histogramChart, SLOT(setThreshold(int, int)));

	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		this, SLOT(setThreshold(int, int)));
	
	otsuButton = new QPushButton("OTSU");
	connect(otsuButton, SIGNAL(clicked()), 
		this, SLOT(setOtsu()));

	entropyButton = new QPushButton("Entropy");

	checkbox = new QCheckBox("Apply Threshold");
	connect(checkbox, SIGNAL(stateChanged(int)), 
		this, SLOT(enableThreshold(int)));

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(histogramChart);
	layout->addWidget(thresholdPanel);
	layout->addWidget(otsuButton);
	layout->addWidget(entropyButton);
	layout->addWidget(checkbox);
	setLayout(layout);

	updateHistogramPanel(*imageCore);
}

void HistogramPanel::updateHistogramPanel(const ImageCore &imageCore)
{
	histogramChart->drawChart(imageCore);
}

void HistogramPanel::enableThreshold(int state)
{
	if (state == Qt::Checked) {
		thresholdPanel->refreshThreshold();
		emit thresholdChanged(thresholdPanel->getLow(),
				      thresholdPanel->getHigh());
	}
	else 
		emit unsetThreshold();
}

void HistogramPanel::setThreshold(int low, int high)
{
	if (checkbox->checkState()== Qt::Checked) {
		thresholdPanel->setThreshold(low, high);
		emit thresholdChanged(low, high);
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
	
}
