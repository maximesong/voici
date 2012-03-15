#include "HistogramChart.h"

#include <iostream>

#include <QPainter>

#include "ImageCore.h"

HistogramChart::HistogramChart(QWidget *parent) :
	QWidget(parent), m_histogram(QImage())
{
	m_low = 30; 	/* for test */
	m_high = 100; 	/* for test */
}


void HistogramChart::drawChart(const ImageCore &imageCore)
{
	m_histogram = imageCore.getHistogram();
	this->update();
}

void HistogramChart::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(QColor(255, 1, 255));
	painter.drawRect(m_low, 0, m_high - m_low, 300);
	painter.setBrush(QColor(255, 255, 255));
	painter.setPen(QColor(0, 0, 0));
	const int *grayHistogram = m_histogram.getGrayHistogram();
	painter.drawRect(0, 0, 256, 300);
	for (int i = 0; i != SCALE_DEPTH; ++i) {
		painter.drawLine(i, 300 - grayHistogram[i] / 10, i, 300);
	}
	painter.setPen(QColor(1, 1, 100));
	painter.drawLine(m_low, 0, m_low, 300);
	painter.drawLine(m_high, 0, m_high, 300);
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
