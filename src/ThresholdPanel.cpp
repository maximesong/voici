#include "ThresholdPanel.h"

#include <QVBoxLayout>

#include "SliderPanel.h"

ThresholdPanel::ThresholdPanel(QWidget *parent)
	: QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout();
	SliderPanel *lowSlider = new SliderPanel("Low");
	SliderPanel *highSlider = new SliderPanel("High");
	connect(lowSlider, SIGNAL(valueChanged(int)),
		this, SIGNAL(lowBoundChanged(int)));
	connect(highSlider, SIGNAL(valueChanged(int)), 
		this, SIGNAL(highBoundChanged(int)));

	layout->addWidget(lowSlider);
	layout->addWidget(highSlider);
	setLayout(layout);
}
