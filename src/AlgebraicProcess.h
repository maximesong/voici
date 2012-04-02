#ifndef _ALGEBRAICPROCESS_H_
#define _ALGEBRAICPROCESS_H_

#include "PixelProcess.h"

class QImage;
class ImagePixelMap;
class PixelIterator;

class AlgebraicProcess : public ImageProcess {
public:
	AlgebraicProcess(ImagePixelMap *map, const QString &processName = "Algebraic Process");
	~AlgebraicProcess();
	void setImagePixelMap(ImagePixelMap *map);
	void setPixelIterator(PixelIterator *iter);
		
protected:
	virtual QImage generateNewImage(const QImage &image);
private:
	ImagePixelMap *m_map;
	PixelIterator *m_iter;
};

#endif /* _ALGEBRAICPROCESS_H_ */
