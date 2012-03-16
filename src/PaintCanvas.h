#ifndef _PAINTCANVAS_H_
#define _PAINTCANVAS_H_

#include <QWidget>

class ImageCore;

class PaintCanvas : public QWidget {
	Q_OBJECT
public:
	PaintCanvas(QWidget *parent = 0);
public slots:
	void drawImage(const ImageCore &imageCore);
	void paintEvent(QPaintEvent *event);
private:
	QImage m_image;
};

#endif /* _PAINTCANVAS_H_ */
