#include "ConvolutionPanel.h"

#include <QGridLayout>
#include <QPushButton>

#include "KernelTable.h"

ConvolutionPanel::ConvolutionPanel(QWidget *parent)
	: QWidget(parent)
{
	kernelTable = new KernelTable();
	edgeButton = new QPushButton("Edge");
	applyButton = new QPushButton("Apply");

	QGridLayout *layout = new QGridLayout();
	layout->addWidget(kernelTable, 0, 0, 4, 6);
	layout->addWidget(edgeButton, 5, 0, 1, 1);
	layout->addWidget(applyButton, 9, 0, 1, 1);
	
	setLayout(layout);
}
