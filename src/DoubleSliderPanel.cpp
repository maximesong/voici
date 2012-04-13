#include "DoubleSliderPanel.h"

#include <QSlider>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QSizePolicy>

#include "VoiciGlobal.h"

DoubleSliderPanel::DoubleSliderPanel(const QString &str, QWidget *parent)
	: QWidget(parent)
{
	label = new QLabel(str);
	label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	slider = new QSlider(Qt::Horizontal);
	slider->setRange(0, MAX_PIXEL_VALUE);
	slider->setSizePolicy(QSizePolicy::Minimum, 
			      QSizePolicy::Fixed);
	spinBox = new QDoubleSpinBox();
	spinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	spinBox->setRange(0, MAX_PIXEL_VALUE);

	slider->setValue(spinBox->value());

	connect(slider, SIGNAL(valueChanged(int)), 
		this, SLOT(updateValue(int)));
	connect(spinBox, SIGNAL(valueChanged(double)), 
		this, SLOT(updateValue(double)));

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(label);
	layout->addWidget(slider);
	layout->addWidget(spinBox);
	setLayout(layout);
}

DoubleSliderPanel::DoubleSliderPanel(QWidget *parent)
{ 
	DoubleSliderPanel("", parent);
}

void DoubleSliderPanel::setValue(double value)
{
	if (value != getValue()) {
		spinBox->setValue(value);
		slider->setValue(value);
		emit valueChanged(value);
	}
}

int DoubleSliderPanel::getValue()
{
	return spinBox->value();
}

void DoubleSliderPanel::updateValue(int value)
{
	spinBox->setValue(value);
	slider->setValue(value);
	emit valueChanged(value);
}

void DoubleSliderPanel::updateValue(double value)
{
	spinBox->setValue(value);
	slider->setValue(value);
	emit valueChanged(value);
}

void DoubleSliderPanel::setMaximum(double value)
{
	slider->setMaximum(value);
	spinBox->setMaximum(value);
}

void DoubleSliderPanel::setMinimum(double value)
{
	slider->setMinimum(value);
	spinBox->setMinimum(value);
}

void DoubleSliderPanel::setRange(double min, double max)
{
	slider->setRange(min, max);
	spinBox->setRange(min, max);
}

