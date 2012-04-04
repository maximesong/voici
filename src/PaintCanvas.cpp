#include <QPainter>

#include "PaintCanvas.h"
#include "ImageCore.h"

#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMouseEvent>

PaintCanvas::PaintCanvas(QWidget *parent):
	QWidget(parent)
{
	setMouseTracking(1);
	canvas = new QLabel();
	canvas->setMouseTracking(1);

	scrollable_canvas = new QScrollArea();
	scrollable_canvas->setWidget(canvas);
	scrollable_canvas->setMouseTracking(1);

	pixel_bar = new QLabel("");
	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(scrollable_canvas);
	layout->addWidget(pixel_bar);

	setLayout(layout);
}

void PaintCanvas::drawImage(const ImageCore &imageCore)
{
	image = imageCore.getCurrentImage();
	QPixmap pixmap = QPixmap::fromImage(image);
	canvas->setPixmap(pixmap);
	canvas->setMinimumSize(pixmap.width(), pixmap.height());
	update();
}

void PaintCanvas::mouseMoveEvent (QMouseEvent * event)
{
	QPoint pixel_point = canvas->mapFrom(scrollable_canvas, event->pos());
	if (pixel_point.x() < 0)
		pixel_point.rx() = 0;
	if (pixel_point.x() >= image.width())
		pixel_point.rx() = image.width() - 1;
	if (pixel_point.y() < 0)
		pixel_point.ry() = 0;
	if (pixel_point.y() >= image.height())
		pixel_point.ry() = image.height() - 1;

	QRgb rgb = image.pixel(pixel_point.x(), pixel_point.y());
	
	QString label;
	label += QString::number(image.width()) + 
		" * " + QString::number(image.height()) + " " + tr("Pixels");
	label += "    " + tr("X:") + QString::number(pixel_point.x());
	label += "  " + tr("Y:") + QString::number(pixel_point.y());
	label += "    " + tr("R:") + QString::number(qRed(rgb));
	label += "    " + tr("G:") + QString::number(qGreen(rgb));
	label += "    " + tr("B:") + QString::number(qBlue(rgb));
	pixel_bar->setText(label);
}
