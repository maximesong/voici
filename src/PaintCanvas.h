#ifndef _PAINTCANVAS_H_
#define _PAINTCANVAS_H_

#include <QWidget>
#include <QPoint>

#include "ImageFamily.h"

class QLabel;
class QScrollArea;
class QMouseEvent;
class QImage;


class PaintCanvas : public QWidget {
	Q_OBJECT
public:
	PaintCanvas(QWidget *parent = 0);
public slots:
	virtual void drawImage(const ImageFamily &imageCore);
protected:
	virtual void mouseMoveEvent (QMouseEvent *event);
	void updateInfoLabel(QPoint pixel_point);
private:
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	QLabel *canvas;
	QLabel *pixel_bar;
	QScrollArea *scrollable_canvas;
	QImage image;
	QPoint drag_start_pos;
	bool is_in_drag;
};

#endif /* _PAINTCANVAS_H_ */
