#include "AlgebraicProcessPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QGroupBox>
#include <QVBoxLayout>

#include "PreviewCanvas.h"
#include "VoiciGlobal.h"
#include "ProcessFactory.h"

AlgebraicProcessPanel::AlgebraicProcessPanel(QWidget *parent)
	: QWidget(parent)
{
	opImageCanvas = new PreviewCanvas();
	selectImageButton = new QPushButton(tr("Select"));

	imageAddButton = new QPushButton(tr("Add"));
	imageSubstractButton = new QPushButton(tr("Substract"));
	imageProductButton = new QPushButton(tr("Product"));
	imageQuotientButton = new QPushButton(tr("Quotient"));


	QGroupBox *canvasGroup = new QGroupBox(tr("Select An Image"));
	QVBoxLayout *canvasGroupLayout = new QVBoxLayout();
	canvasGroupLayout->addWidget(opImageCanvas);
	canvasGroupLayout->addWidget(selectImageButton);
	canvasGroup->setLayout(canvasGroupLayout);

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(canvasGroup);
	layout->addWidget(imageAddButton, 2, 0);
	layout->addWidget(imageSubstractButton, 2, 1);
	layout->addWidget(imageProductButton, 3, 0);
	layout->addWidget(imageQuotientButton, 3, 1);
	setLayout(layout);

	connect(selectImageButton, SIGNAL(clicked()), 
		this, SLOT(selectImage()));
	connect(imageAddButton, SIGNAL(clicked()), 
		this, SLOT(sendAddProcess()));
	connect(imageSubstractButton, SIGNAL(clicked()), 
		this, SLOT(sendSubstractProcess()));
	connect(imageProductButton, SIGNAL(clicked()), 
		this, SLOT(sendProductProcess()));
	connect(imageQuotientButton, SIGNAL(clicked()), 
		this, SLOT(sendQuotientProcess()));
}

void AlgebraicProcessPanel::selectImage()
{
	QString filename = QFileDialog::getOpenFileName(this,
						      tr("Open Image"), 
						      ".", 
						      tr(acceptImageLabel));
	if (!filename.isEmpty()) {
		previewImage = QImage(filename);
		opImageCanvas->drawImage(previewImage);
	}
}

void AlgebraicProcessPanel::sendAddProcess()
{
	if (previewImage.isNull())
		return;
	SharedProcess process = 
		ProcessFactory::getImageLinearBlendProcess(previewImage, 1, 1);
	emit newProcess(process);
}

void AlgebraicProcessPanel::sendSubstractProcess()
{
	if (previewImage.isNull())
		return;
	SharedProcess process = 
		ProcessFactory::getImageLinearBlendProcess(previewImage, 1, -1);
	emit newProcess(process);
}

void AlgebraicProcessPanel::sendProductProcess()
{
	if (previewImage.isNull())
		return;
	SharedProcess process = ProcessFactory::getImageProductProcess(previewImage);
	emit newProcess(process);
}

void AlgebraicProcessPanel::sendQuotientProcess()
{
	if (previewImage.isNull())
		return;
	SharedProcess process = ProcessFactory::getImageQuotientProcess(previewImage);
	emit newProcess(process);
}
