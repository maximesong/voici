#include <QPainter>

#include "PaintCanvas.h"
#include "ImageCore.h"

#include <QPixmap>
#include <QImage>

PaintCanvas::PaintCanvas(QWidget *parent):
	QLabel(parent)
{
	/* empty */
}

void PaintCanvas::drawImage(const ImageCore &imageCore)
{
	const QImage &image = imageCore.getCurrentImage();
	setPixmap(QPixmap::fromImage(image));
	update();
}
