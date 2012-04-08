#include "FilterPanel.h"

#include <QGridLayout>
#include <QPushButton>
#include <QDoubleSpinBox>

#include "ProcessFactory.h"

FilterPanel::FilterPanel(QWidget *parent)
	: QWidget(parent)
{
	QGridLayout *layout = new QGridLayout();
	quickGaussBlurButton = new QPushButton(tr("Quick Gauss Blur"));

	gaussVerticalBox = new QDoubleSpinBox();
	gaussVerticalBox->setPrefix(tr("Vertical:"));
	gaussVerticalBox->setValue(3.0);

	gaussHorizontalBox = new QDoubleSpinBox();
	gaussHorizontalBox->setPrefix(tr("Horizontal:"));
	gaussHorizontalBox->setValue(3.0);

	layout->addWidget(quickGaussBlurButton, 0, 0);
	layout->addWidget(gaussVerticalBox);
	layout->addWidget(gaussHorizontalBox);
	setLayout(layout);

	connect(quickGaussBlurButton, SIGNAL(clicked()), 
		this, SLOT(addGaussProcess()));
}

void FilterPanel::addGaussProcess()
{
	double horz = gaussHorizontalBox->value();
	double vert = gaussVerticalBox->value();
	ImageProcess *process = ProcessFactory::getQuickGaussBlurProcess(horz,
									 vert);
	emit newProcess(process);
}
