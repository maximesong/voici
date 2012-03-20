#ifndef _PAINTCANVAS_H_
#define _PAINTCANVAS_H_

#include <QScrollArea>

class QLabel;

class ImageCore;

class PaintCanvas : public QScrollArea {
	Q_OBJECT
public:
	PaintCanvas(QWidget *parent = 0);
public slots:
	virtual void drawImage(const ImageCore &imageCore);
private:
	QLabel *canvas;
};

#endif /* _PAINTCANVAS_H_ */
