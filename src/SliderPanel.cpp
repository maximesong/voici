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
	QLabel *label = new QLabel(str);
	label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QSlider *slider = new QSlider(Qt::Horizontal);
	slider->setRange(0, MAX_PIXEL_VALUE);
	slider->setSizePolicy(QSizePolicy::Minimum, 
			      QSizePolicy::Fixed);
	QSpinBox *spinBox = new QSpinBox();
	spinBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	spinBox->setRange(0, MAX_PIXEL_VALUE);

	connect(slider, SIGNAL(valueChanged(int)), 
		this, SLOT(setValue(int)));
	connect(spinBox, SIGNAL(valueChanged(int)), 
		this, SLOT(setValue(int)));
	connect(this, SIGNAL(valueChanged(int)), 
		slider, SLOT(setValue(int)));
	connect(this, SIGNAL(valueChanged(int)), 
		spinBox, SLOT(setValue(int)));

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
	if (m_value != value) {
		m_value = value;
		emit valueChanged(m_value);
	}
}
