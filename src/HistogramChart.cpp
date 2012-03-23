#include "HistogramChart.h"

#include <iostream>

#include <QPainter>

#include "ImageCore.h"
#include "Histogram.h"
#include "VoiciGlobal.h"

HistogramChart::HistogramChart(QWidget *parent) :
	QWidget(parent), m_histogram(QImage())
{
	m_low = 0;
	m_high = MAX_PIXEL_VALUE;
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

void HistogramChart::paintEvent(QPaintEvent *)
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


void HistogramChart::setThreshold(int low, int high)
{
	if (low != m_low || high != m_high) {
		m_low = low;
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
	for (int i = 0; i <= MAX_PIXEL_VALUE; ++i) {
		painter.drawLine(i, 300 - m_histogram.getCount(i, Histogram::Gray) / 10, i, 300);
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
