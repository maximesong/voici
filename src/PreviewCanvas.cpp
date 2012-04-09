#include "PreviewCanvas.h"

#include "ImageCore.h"

#include <iostream>
using namespace std;

PreviewCanvas::PreviewCanvas(QWidget *parent)
	:QLabel(parent)
{
	standard_width = 250;
	standard_height = 200;
	setMinimumSize(standard_width, standard_height);
}

void PreviewCanvas::drawImage(const ImageCore &imageCore)
{
	QImage image = imageCore.getCurrentImage();
	drawImage(image);
}

void PreviewCanvas::drawImage(const QImage &image)
{
	double widthScaledRate = double(standard_width) / image.width();
	double heightScaledRate = double(standard_height) / image.height();

	double scaledRate = qMin(widthScaledRate, heightScaledRate);
	
	QImage scaledImage = image.scaled (image.width() * scaledRate,
			      image.height() * scaledRate,
			      Qt::IgnoreAspectRatio, 
			      Qt::FastTransformation);
	QPixmap pixmap = QPixmap::fromImage(scaledImage);
	setPixmap(pixmap);
}

void PreviewCanvas::setStandardSize(int width, int height)
{
	standard_width = width;
	standard_height = height;
}
void PreviewCanvas::setStandardWidth(int width)
{
	standard_width = width;
}

void PreviewCanvas::setStandardHeight(int height)
{
	standard_height = height;
}
