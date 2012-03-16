#include "HistogramChart.h"

#include <iostream>

#include <QPainter>

#include "ImageCore.h"
#include "Histogram.h"

HistogramChart::HistogramChart(QWidget *parent) :
	QWidget(parent), m_histogram(QImage())
{
	m_low = 30; 	/* for test */
	m_high = 100; 	/* for test */
	background.setRgb(255, 255, 255);
	threshold_brush_color.setRgb(100, 100, 100, 100);
	threshold_pen_color.setRgb(200, 200, 200);
	histogram_pen_color.setRgb(150, 150, 150);
}


void HistogramChart::drawChart(const ImageCore &imageCore)
{
	m_histogram = Histogram(imageCore.getCurrentImage());
	this->update();
}

void HistogramChart::paintEvent(QPaintEvent *event)
{
	drawBackground();
	drawAxis();
	drawData();
	drawThreshold();
}

void HistogramChart::setLowThreshold(int low)
{
	if (low != m_low) {
		m_low = low;
		this->update();
	}
}

void HistogramChart::setHighThreshold(int high)
{
	if (high != m_high) {
		m_high = high;
		this->update();
	}
}

void HistogramChart::drawBackground()
{
	QPainter painter(this);
	painter.setBrush(QColor(255, 255, 255));
	painter.drawRect(0, 0, 256, 300);
}

void HistogramChart::drawAxis()
{
}

void HistogramChart::drawData()
{
	QPainter painter(this);
	painter.setPen(histogram_pen_color);
	const int *grayHistogram = m_histogram.getGrayHistogram();
	for (int i = 0; i != SCALE_DEPTH; ++i) {
		painter.drawLine(i, 300 - grayHistogram[i] / 10, i, 300);
	}
}

void HistogramChart::drawThreshold()
{
	QPainter painter(this);

	painter.setBrush(threshold_brush_color);
	painter.drawRect(m_low, 0, m_high - m_low, 300);

	painter.setPen(threshold_pen_color);
	painter.drawLine(m_low, 0, m_low, 300);
	painter.drawLine(m_high, 0, m_high, 300);
}
