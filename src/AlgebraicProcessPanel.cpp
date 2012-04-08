#include "AlgebraicProcessPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QFileDialog>
#include <QImage>

#include "PreviewCanvas.h"
#include "VoiciGlobal.h"

AlgebraicProcessPanel::AlgebraicProcessPanel(QWidget *parent)
	: QWidget(parent)
{
	opImageCanvas = new PreviewCanvas();
	selectImageButton = new QPushButton(tr("select"));
	QGridLayout *layout = new QGridLayout();
	layout->addWidget(opImageCanvas, 0, 0);
	layout->addWidget(selectImageButton, 1, 0);
	setLayout(layout);

	connect(selectImageButton, SIGNAL(clicked()), 
		this, SLOT(selectImage()));
}

void AlgebraicProcessPanel::selectImage()
{
	QString filename = QFileDialog::getOpenFileName(this,
						      tr("Open Image"), 
						      ".", 
						      tr(acceptImageLabel));
	if (!filename.isEmpty()) {
		QImage image = QImage(filename);
		opImageCanvas->drawImage(image);
	}
}
