#include "TransformPanel.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QGridLayout>

#include "ImageProcess.h"
#include "ProcessFactory.h"

TransformPanel::TransformPanel(int defaultImageWidth, int defaultImageHeight,
			       QWidget *parent)
	: QWidget(parent)
{
	scaleWidthBox = new QSpinBox();
	scaleWidthBox->setPrefix(tr("Width:"));
	scaleWidthBox->setMaximum(9999);
	scaleWidthBox->setValue(defaultImageWidth);

	scaleHeightBox = new QSpinBox();
	scaleHeightBox->setPrefix(tr("Height:"));
	scaleHeightBox->setMaximum(9999);
	scaleHeightBox->setValue(defaultImageHeight);

	nearestNeighbourScaleButton = new QPushButton(tr("Nearest Neighbour Scale"));
	connect(nearestNeighbourScaleButton, SIGNAL(clicked()), 
		this, SLOT(sendNearestNeighbourScaleProcess()));

	bilinearScaleButton = new QPushButton(tr("Bilinear Scale"));
	connect(bilinearScaleButton, SIGNAL(clicked()), 
		this, SLOT(sendBilinearScaleProcess()));


	QGroupBox *scaleGroupBox = new QGroupBox(tr("Scale"));
	QGridLayout *scaleLayout = new QGridLayout();
	scaleLayout->addWidget(scaleWidthBox, 0, 0);
	scaleLayout->addWidget(scaleHeightBox, 0, 1);
	scaleLayout->addWidget(nearestNeighbourScaleButton, 1, 0);
	scaleLayout->addWidget(bilinearScaleButton, 1, 1);
	scaleGroupBox->setLayout(scaleLayout);
	
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(scaleGroupBox);

	setLayout(layout);
}

void TransformPanel::sendBilinearScaleProcess()
{
	ImageProcess *process = ProcessFactory::getBilinearScaleProcess(
		getScaleWidth(), 
		getScaleHeight());

	emit newProcess(process);
}

void TransformPanel::sendNearestNeighbourScaleProcess()
{
	ImageProcess *process = ProcessFactory::getNearestNeighbourScaleProcess(
		getScaleWidth(), 
		getScaleHeight());

	emit newProcess(process);
}


int TransformPanel::getScaleWidth()
{
	return scaleWidthBox->value();
}

int TransformPanel::getScaleHeight()
{
	return scaleHeightBox->value();
}
