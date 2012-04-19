#include "TransformPanel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>
#include <QGridLayout>

#include "ProcessFactory.h"
#include "SliderPanel.h"
#include "DoubleSliderPanel.h"
#include "VoiciMainWindow.h"

TransformPanel::TransformPanel(int defaultImageWidth, int defaultImageHeight,
			       QWidget *parent)
	: QWidget(parent)
{
	scaleWidthBox = new SliderPanel(tr("Width"));
	scaleWidthBox->setMaximum(9999);
	scaleWidthBox->setValue(defaultImageWidth);

	scaleHeightBox = new SliderPanel(tr("Height"));
	scaleHeightBox->setMaximum(9999);
	scaleHeightBox->setValue(defaultImageHeight);

	nearestNeighbourScaleButton = new QPushButton(tr("Nearest Neighbour Scale"));
	connect(nearestNeighbourScaleButton, SIGNAL(clicked()), 
		this, SLOT(sendNearestNeighbourScaleProcess()));

	bilinearScaleButton = new QPushButton(tr("Bilinear Scale"));
	connect(bilinearScaleButton, SIGNAL(clicked()), 
		this, SLOT(sendBilinearScaleProcess()));


	QPushButton *nearestNeighbourRotateButton = new QPushButton(tr("Nearest Neighbour Rotate"));

	rotateAngleBox = new DoubleSliderPanel("Angle");
	rotateAngleBox->setMaximum(360);
	rotateAngleBox->setValue(90);
	connect(nearestNeighbourRotateButton, SIGNAL(clicked()), 
		this, SLOT(sendNearestNeighbourRotateProcess()));


	QGroupBox *scaleGroupBox = new QGroupBox(tr("Scale"));
	QGridLayout *scaleLayout = new QGridLayout();
	scaleLayout->addWidget(scaleWidthBox, 0, 0, 2, 1);
	scaleLayout->addWidget(scaleHeightBox, 1, 0, 2, 1);
	scaleLayout->addWidget(nearestNeighbourScaleButton, 2, 0, 1, 1);
	scaleLayout->addWidget(bilinearScaleButton, 2, 1, 1, 1);
	scaleGroupBox->setLayout(scaleLayout);
	
	QGroupBox *rotateGroupBox = new QGroupBox(tr("Rotate"));
	QGridLayout *rotateLayout = new QGridLayout();
	rotateLayout->addWidget(rotateAngleBox, 0, 0);
	rotateLayout->addWidget(nearestNeighbourRotateButton, 1, 0);
	rotateGroupBox->setLayout(rotateLayout);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(scaleGroupBox);
	layout->addWidget(rotateGroupBox);

	setLayout(layout);
}

void TransformPanel::sendBilinearScaleProcess()
{
	SharedProcess process = ProcessFactory::getBilinearScaleProcess(
		getScaleWidth(), 
		getScaleHeight());

	emit newProcess(process);
}

void TransformPanel::sendNearestNeighbourScaleProcess()
{
	SharedProcess process = ProcessFactory::getNearestNeighbourScaleProcess(
		getScaleWidth(), 
		getScaleHeight());

	emit newProcess(process);
}

void TransformPanel::sendNearestNeighbourRotateProcess()
{
	SharedProcess process = ProcessFactory::getNearestNeighbourRotateProcess(
		getRotateAngle());

	emit newProcess(process);
}


int TransformPanel::getScaleWidth()
{
	return scaleWidthBox->getValue();
}

int TransformPanel::getScaleHeight()
{
	return scaleHeightBox->getValue();
}


double TransformPanel::getRotateAngle()
{
	return rotateAngleBox->getValue();
}
