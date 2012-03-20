#include <QPainter>

#include "PaintCanvas.h"
#include "ImageCore.h"

#include <QPixmap>
#include <QImage>
#include <QLabel>

PaintCanvas::PaintCanvas(QWidget *parent):
	QScrollArea(parent)
{
	canvas = new QLabel(this);
	setWidget(canvas);
}

void PaintCanvas::drawImage(const ImageCore &imageCore)
{
	const QImage &image = imageCore.getCurrentImage();
	QPixmap pixmap = QPixmap::fromImage(image);
	canvas->setPixmap(pixmap);
	canvas->setMinimumSize(pixmap.width(), pixmap.height());
	update();
}
