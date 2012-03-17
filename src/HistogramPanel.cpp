#include "HistogramPanel.h"

#include "ImageCore.h"
#include "HistogramChart.h"
#include "ThresholdPanel.h"

#include <QVBoxLayout>

HistogramPanel::HistogramPanel(ImageCore *imageCore, QWidget *parent)
	: QWidget(parent) {
	histogramChart = new HistogramChart();
	thresholdPanel = new ThresholdPanel();
	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		histogramChart, SLOT(setThreshold(int, int)));

	connect(thresholdPanel, SIGNAL(thresholdChanged(int, int)), 
		this, SIGNAL(thresholdChanged(int, int)));
	
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(histogramChart);
	layout->addWidget(thresholdPanel);
	setLayout(layout);

	updateHistogramPanel(*imageCore);
}

void HistogramPanel::updateHistogramPanel(const ImageCore &imageCore)
{
	histogramChart->drawChart(imageCore);
}
