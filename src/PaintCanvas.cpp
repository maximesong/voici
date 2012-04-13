#include "PaintCanvas.h"

#include <iostream>
using namespace std;

#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMouseEvent>
#include <QCursor>
#include <QSizePolicy>

#include "ImageCore.h"

const int MAX_BORDER_DISTANCE = 5;

PaintCanvas::PaintCanvas(QWidget *parent):
	QWidget(parent)
{
	setMouseTracking(1);
	canvas = new QLabel();
	canvas->setMouseTracking(1);
	canvas->setCursor(QCursor(Qt::CrossCursor));
	QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
	canvas->setSizePolicy(sizePolicy);

	scrollable_canvas = new QScrollArea();
	scrollable_canvas->setWidget(canvas);
	scrollable_canvas->setMouseTracking(1);
	scrollable_canvas->setWidgetResizable(1);

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

void PaintCanvas::mouseMoveEvent (QMouseEvent *event)
{
	QPoint pixel_point = canvas->mapFrom(scrollable_canvas, event->pos());
	QString label;
	label += QString::number(image.width()) + 
		" * " + QString::number(image.height()) + " " + tr("Pixels");

	/* Mouse out of the painting border */
	if (pixel_point.x() < -MAX_BORDER_DISTANCE ||
	    pixel_point.x() >= image.width() + MAX_BORDER_DISTANCE ||
	    pixel_point.y() < -MAX_BORDER_DISTANCE ||
	    pixel_point.y() >= image.height() + MAX_BORDER_DISTANCE) {
		pixel_bar->setText(label);
		return;
	}

	if (pixel_point.x() < 0)
		pixel_point.rx() = 0;
	if (pixel_point.x() >= image.width())
		pixel_point.rx() = image.width() - 1;
	if (pixel_point.y() < 0)
		pixel_point.ry() = 0;
	if (pixel_point.y() >= image.height())
		pixel_point.ry() = image.height() - 1;

	QRgb rgb = image.pixel(pixel_point.x(), pixel_point.y());
	
	label += "    " + tr("X:") + QString::number(pixel_point.x());
	label += "  " + tr("Y:") + QString::number(pixel_point.y());
	label += "    " + tr("R:") + QString::number(qRed(rgb));
	label += "    " + tr("G:") + QString::number(qGreen(rgb));
	label += "    " + tr("B:") + QString::number(qBlue(rgb));
	pixel_bar->setText(label);
}
