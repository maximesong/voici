#include <QPainter>

#include "PaintCanvas.h"
#include "ImageCore.h"

PaintCanvas::PaintCanvas(QWidget *parent):
	QWidget(parent)
{
	/* empty */
}

void PaintCanvas::drawImage(const ImageCore &imageCore)
{
	m_image = imageCore.getImage();
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.drawImage(QPoint(0,0), m_image);
}
