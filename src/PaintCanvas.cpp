#include <QPainter>

#include "PaintCanvas.h"
#include "Exceptions.h"

PaintCanvas::PaintCanvas()
{
	displayImage.fill(0);
	isChanged = 0;
}

PaintCanvas::~PaintCanvas()
{
}

void PaintCanvas::loadImage(const QString &filename)
{
	displayImage.load(filename);
	if (displayImage.isNull())
		throw FileError();

	isChanged = 1;
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
	if (isChanged) {
		QPainter painter(this);
		painter.drawImage(QPoint(0,0), displayImage);
//		for (int i = 0; i != displayImage.width(); ++i)
//			for (int j = 0; j != displayImage.with(); ++j)
				
	}
		
}
