#ifndef _PAINTOPERATOR_H_
#define _PAINTOPERATOR_H_

#include <QObject>
#include <QVector>
#include <QPoint>

#include "Process.h"
#include "PaintCanvas.h"

class IteratorArea;
class QMouseEvent;

class PaintOperator : public QObject {
	Q_OBJECT
public:
	enum State {Normal, SelectRectangle, SelectCircle, SelectTriangle,
		    WaitClick};
	PaintOperator();
signals:
	void areaChanged(IteratorArea *area);
	void newProcess(SharedProcess process);
	void canvasStateChanged(PaintCanvas::State state);
public slots:
	void mousePressed(QMouseEvent *event);
	void mouseMoved(QMouseEvent *event);
	void mouseReleased(QMouseEvent *event);
	void setState(State state);
private:
	QVector<QPoint> m_points;
	State m_state;
};

#endif /* _PAINTOPERATOR_H_ */
