#include <QPainter>

#include "PaintCanvas.h"

PaintCanvas::PaintCanvas(QWidget *parent, const QImage &image):
	QWidget(parent), m_image(image)
{
	/* empty */
}

void PaintCanvas::redraw()
{
	this->update();
}

void PaintCanvas::paintEvent(QPaintEvent *event)
{
	if (isChanged) {
		QPainter painter(this);
		painter.drawImage(QPoint(0,0), m_image);
	}
}
