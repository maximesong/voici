#include "SliderPanel.h"

#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSizePolicy>

#include "VoiciGlobal.h"

SliderPanel::SliderPanel(const QString &str, QWidget *parent)
	: QWidget(parent)
{
	label = new QLabel(str);
	label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	slider = new QSlider(Qt::Horizontal);
	slider->setRange(0, MAX_PIXEL_VALUE);
	slider->setSizePolicy(QSizePolicy::Minimum, 
			      QSizePolicy::Fixed);
	spinBox = new QSpinBox();
	spinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	spinBox->setRange(0, MAX_PIXEL_VALUE);

	slider->setValue(spinBox->value());

	connect(slider, SIGNAL(valueChanged(int)), 
		this, SLOT(updateValue(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), 
		this, SLOT(updateValue(int)));

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(label);
	layout->addWidget(slider);
	layout->addWidget(spinBox);
	setLayout(layout);
}

SliderPanel::SliderPanel(QWidget *parent)
{ 
	SliderPanel("", parent);
}

void SliderPanel::setValue(int value)
{
	if (value != getValue()) {
		spinBox->setValue(value);
		slider->setValue(value);
		emit valueChanged(value);
	}
}

int SliderPanel::getValue()
{
	return spinBox->value();
}

void SliderPanel::updateValue(int value)
{
	spinBox->setValue(value);
	slider->setValue(value);
	emit valueChanged(value);
}

void SliderPanel::setMaximum(int value)
{
	slider->setMaximum(value);
	spinBox->setMaximum(value);
}

void SliderPanel::setMinimum(int value)
{
	slider->setMinimum(value);
	spinBox->setMinimum(value);
}

void SliderPanel::setRange(int min, int max)
{
	slider->setRange(min, max);
	spinBox->setRange(min, max);
}
