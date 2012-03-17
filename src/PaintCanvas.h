#ifndef _PAINTCANVAS_H_
#define _PAINTCANVAS_H_

#include <QLabel>

class ImageCore;

class PaintCanvas : public QLabel {
	Q_OBJECT
public:
	PaintCanvas(QWidget *parent = 0);
public slots:
	virtual void drawImage(const ImageCore &imageCore);
};

#endif /* _PAINTCANVAS_H_ */
