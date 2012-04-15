#ifndef _ALGEBRAICPROCESS_H_
#define _ALGEBRAICPROCESS_H_

#include "ImageProcesser.h"
#include "Map.h"
#include "Iterator.h"

class QImage;

class AlgebraicProcess : public ImageProcesser {
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
