#ifndef _PAINTCANVAS_H_
#define _PAINTCANVAS_H_

#include <QWidget>

class QLabel;
class QScrollArea;
class QMouseEvent;
class QImage;

class ImageCore;

class PaintCanvas : public QWidget {
	Q_OBJECT
public:
	PaintCanvas(QWidget *parent = 0);
public slots:
	virtual void drawImage(const ImageCore &imageCore);
protected:
	virtual void mouseMoveEvent (QMouseEvent *event);
private:
	QLabel *canvas;
	QLabel *pixel_bar;
	QScrollArea *scrollable_canvas;
	QImage image;
};

#endif /* _PAINTCANVAS_H_ */
