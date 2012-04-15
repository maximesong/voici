#include "FilterPanel.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QGroupBox>

#include "ProcessFactory.h"

FilterPanel::FilterPanel(QWidget *parent)
	: QWidget(parent)
{
	/* first comes the gauss group */
	gaussHorizontalBox = new QDoubleSpinBox();
	gaussHorizontalBox->setPrefix(tr("Horizontal:"));
	gaussHorizontalBox->setMaximum(9999);
	gaussHorizontalBox->setValue(5.0);

	gaussVerticalBox = new QDoubleSpinBox();
	gaussVerticalBox->setPrefix(tr("Vertical:"));
	gaussVerticalBox->setMaximum(9999);
	gaussVerticalBox->setValue(5.0);

	quickGaussBlurButton = new QPushButton(tr("Quick Gauss Blur"));

	QGridLayout *gaussGroupLayout = new QGridLayout();
	gaussGroupLayout->addWidget(gaussHorizontalBox, 0, 0);
	gaussGroupLayout->addWidget(gaussVerticalBox, 0, 1);
	gaussGroupLayout->addWidget(quickGaussBlurButton, 1, 0);

	QGroupBox *gaussGroupBox = new QGroupBox(tr("Gauss Filter"));
	gaussGroupBox->setLayout(gaussGroupLayout);

	/* second comes the mean and median group */
	meanFilterButton = new QPushButton(tr("Mean Filter"));
	medianFilterButton = new QPushButton(tr("Meadian Filter"));

	rowCountBox = new QSpinBox();
	rowCountBox->setPrefix(tr("rows:"));
	rowCountBox->setValue(3);

	columnCountBox = new QSpinBox();
	columnCountBox->setPrefix(tr("cols:"));
	columnCountBox->setValue(3);

	QGridLayout *meanAndMedianGroupLayout = new QGridLayout();
	meanAndMedianGroupLayout->addWidget(rowCountBox, 0, 0);
	meanAndMedianGroupLayout->addWidget(columnCountBox, 0, 1);
	meanAndMedianGroupLayout->addWidget(meanFilterButton, 1, 0);
	meanAndMedianGroupLayout->addWidget(medianFilterButton, 2, 0);

	QGroupBox *meanAndMedianGroupBox = new QGroupBox(tr("Mean and Median Filter"));
	meanAndMedianGroupBox->setLayout(meanAndMedianGroupLayout);

	/* finally, the panel layout */
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(gaussGroupBox);
	layout->addWidget(meanAndMedianGroupBox);
	setLayout(layout);

	/* connect the button to their functions */
	connect(quickGaussBlurButton, SIGNAL(clicked()), 
		this, SLOT(addGaussProcess()));

	connect(meanFilterButton, SIGNAL(clicked()), 
		this, SLOT(addMeanFilterProcess()));

	connect(medianFilterButton, SIGNAL(clicked()), 
		this, SLOT(addMedianFilterProcess()));
}

void FilterPanel::addGaussProcess()
{
	double horz = gaussHorizontalBox->value();
	double vert = gaussVerticalBox->value();
	SharedProcess process = ProcessFactory::getQuickGaussBlurProcess(horz,
									 vert);
	emit newProcess(process);
}

void FilterPanel::addMeanFilterProcess()
{
	int row_count = rowCountBox->value();
	int column_count = columnCountBox->value();
	SharedProcess process = ProcessFactory::getMeanFilterProcess(row_count,
								     column_count);
	emit newProcess(process);
}

void FilterPanel::addMedianFilterProcess()
{
	int row_count = rowCountBox->value();
	int column_count = columnCountBox->value();
	SharedProcess process = ProcessFactory::getMedianFilterProcess(row_count,
								       column_count);
	emit newProcess(process);
}
