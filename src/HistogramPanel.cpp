#include "HistogramPanel.h"

#include "ImageCore.h"
#include "HistogramChart.h"
#include "ThresholdPanel.h"

HistogramPanel::HistogramPanel(ImageCore *imageCore, QWidget *parent)
	: QWidget(parent) {
	histogramChart = new HistogramChart();
	thresholdPanel = new ThresholdPanel();
	connect(thresholdPanel, SIGNAL(lowBoundChanged(int)), 
		histogramChart, SLOT(setLowThreshold(int)));
	connect(thresholdPanel, SIGNAL(highBoundChanged(int)), 
		histogramChart, SLOT(setHighThreshold(int)));

}

void HistogramPanel::updateHistogramPanel(const ImageCore &imageCore)
{
	histogramChart->drawChart(imageCore);
}
