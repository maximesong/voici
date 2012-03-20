#include "ImageProcess.h"

#include <QImage>

#include "ImageCore.h"

void ImageProcess::processImage(ImageCore *imageCore) {
	const QImage &currentImage = imageCore->getCurrentImage();
	imageCore->updateCurrentImage(generateNewImage(currentImage));
}
