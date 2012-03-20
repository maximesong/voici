#include "ThresholdPanel.h"

#include <QVBoxLayout>

#include "SliderPanel.h"
#include "VoiciGlobal.h"

ThresholdPanel::ThresholdPanel(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
	SliderPanel *lowSlider = new SliderPanel("Low");
	SliderPanel *highSlider = new SliderPanel("High");
	m_low = 0;
	m_high = MAX_PIXEL_VALUE;
	lowSlider->setValue(m_low);
	highSlider->setValue(m_high);

	connect(lowSlider, SIGNAL(valueChanged(int)),
		this, SLOT(setLow(int)));
	connect(highSlider, SIGNAL(valueChanged(int)), 
		this, SLOT(setHigh(int)));

	layout->addWidget(lowSlider);
	layout->addWidget(highSlider);
	setLayout(layout);
}

void ThresholdPanel::setLow(int low)
{
	if (m_low != low) {
		m_low = low;
		emit thresholdChanged(m_low, m_high);
	}
}

void ThresholdPanel::setHigh(int high)
{
	if (m_high != high) {
		m_high = high;
		emit thresholdChanged(m_low, m_high);
	}
}
