#include "PointOperatorPanel.h"

#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>

#include "ProcessFactory.h"

PointOperatorPanel::PointOperatorPanel(QWidget *parent)
	: QWidget(parent)
{
	/* first the linear operator group */
	kBox = new QDoubleSpinBox();
	kBox->setPrefix(tr("ratio:"));
	kBox->setMinimum(-999);
	kBox->setMaximum(999);
	kBox->setValue(1.0);

	bBox = new QDoubleSpinBox();
	bBox->setPrefix(tr("offset:"));
	bBox->setMinimum(-999);
	bBox->setMaximum(999);
	bBox->setValue(0.0);

	pointLinearButton = new QPushButton(tr("Linear Operator"));
	QGridLayout *linearOperatorGroupLayout = new QGridLayout();
	linearOperatorGroupLayout->addWidget(kBox, 0, 0);
	linearOperatorGroupLayout->addWidget(bBox, 0, 1);
	linearOperatorGroupLayout->addWidget(pointLinearButton, 1, 0);

	QGroupBox *linearOperatorGroup = new QGroupBox(tr("Linear Operator"));
	linearOperatorGroup->setLayout(linearOperatorGroupLayout);


	/* second the linear operator group */
	cBox = new QDoubleSpinBox();
	cBox->setPrefix(tr("c:"));
	cBox->setMaximum(999);
	cBox->setMinimum(-999);
	cBox->setValue(1.0);

	maxLevelBox = new QSpinBox();
	maxLevelBox->setPrefix(tr("max:"));
	maxLevelBox->setMaximum(999);
	maxLevelBox->setMinimum(-999);
	maxLevelBox->setValue(255);


	midlevelNonlinearButton = new QPushButton(tr("Midlevel Nonlinear"));

	QGridLayout *nonlinearOperatorGroupLayout = new QGridLayout();
	nonlinearOperatorGroupLayout->addWidget(cBox, 0, 0);
	nonlinearOperatorGroupLayout->addWidget(maxLevelBox, 0, 1);
	nonlinearOperatorGroupLayout->addWidget(midlevelNonlinearButton, 1, 0);

	QGroupBox *nonlinearOperatorGroup = new QGroupBox(tr("Nonlinear Operator"));
	nonlinearOperatorGroup->setLayout(nonlinearOperatorGroupLayout);

	/* finally set the panel layout */
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(linearOperatorGroup);
	layout->addWidget(nonlinearOperatorGroup);
	setLayout(layout);

	connect(pointLinearButton, SIGNAL(clicked()), 
		this, SLOT(sendPointLinearProcess()));

	connect(midlevelNonlinearButton, SIGNAL(clicked()), 
		this, SLOT(sendMidlevelNonlinearProcess()));
}

void PointOperatorPanel::sendPointLinearProcess()
{
	SharedProcess process = ProcessFactory::getLinearProcess(kBox->value(),
								 bBox->value());

	emit newProcess(process);
}

void PointOperatorPanel::sendMidlevelNonlinearProcess()
{
	SharedProcess process = ProcessFactory::getMidlevelNonlinearMap(
		cBox->value(),
		maxLevelBox->value());

	emit newProcess(process);
}
