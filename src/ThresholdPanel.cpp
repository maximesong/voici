#include "ThresholdPanel.h"

#include <QVBoxLayout>

#include "SliderPanel.h"
#include "VoiciGlobal.h"

ThresholdPanel::ThresholdPanel(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
	lowSlider = new SliderPanel("Low");
	highSlider = new SliderPanel("High");

	lowSlider->setValue(0);
	highSlider->setValue(MAX_PIXEL_VALUE);

	connect(lowSlider, SIGNAL(valueChanged(int)),
		this, SLOT(setLow(int)));
	connect(highSlider, SIGNAL(valueChanged(int)), 
		this, SLOT(setHigh(int)));

	layout->addWidget(lowSlider);
	layout->addWidget(highSlider);
	setLayout(layout);
}

void ThresholdPanel::setLow(int low) {
	lowSlider->setValue(low);
	emit thresholdChanged(getLow(), getHigh());
}

void ThresholdPanel::setHigh(int high)
{
	highSlider->setValue(high);
	emit thresholdChanged(getLow(), getHigh());
}

void ThresholdPanel::setThreshold(int low, int high)
{
	lowSlider->setValue(low);
	highSlider->setValue(high);
	emit thresholdChanged(getLow(), getHigh());
}

int ThresholdPanel::getLow() 
{ 
	return lowSlider->getValue(); 
}

int ThresholdPanel::getHigh() 
{ 
	return highSlider->getValue(); 
}
