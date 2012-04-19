#include "PaintOperator.h"

#include <cmath>
#include <iostream>
using namespace std;

#include <QMouseEvent>
#include <QPoint>

#include "ProcessFactory.h"


PaintOperator::PaintOperator()
{
	m_state = Normal;
}

void PaintOperator::mousePressed(QMouseEvent *event)
{
	switch (m_state) {
	case SelectRectangle:
		switch (m_points.size()) {
		case 0:
			m_points.push_back(event->pos());
			break;
		case 1:
			int x1 = m_points[0].x();
			int y1 = m_points[0].y();
			int x2 = event->pos().x();
			int y2 = event->pos().y();
			IteratorArea *area = new RectangleIteratorArea(x1, y1,
								       x2 - x1,
								       y2 - y1);
			emit areaChanged(area);
			m_state = Normal;
			m_points.clear();
			break;			
		}
		break;
	case SelectCircle:
		switch (m_points.size()) {
		case 0:
			m_points.push_back(event->pos());
			break;
		case 1:
			int cx = m_points[0].x();
			int cy = m_points[0].y();
			int x0 = event->pos().x();
			int y0 = event->pos().y();
			int r = sqrt((cx - x0) * (cx - x0) + 
				     (cy - y0) * (cy - y0));
			IteratorArea *area = new EllipseIteratorArea(cx, cy,
								     r, r);

			emit areaChanged(area);
			m_state = Normal;
			m_points.clear();
			break;		
		}
		break;
	}
}

void PaintOperator::mouseMoved(QMouseEvent *event)
{
	switch (m_state) {
	case SelectRectangle:
		switch (m_points.size()) {
		case 1:
			QVector<QPoint> rect_points;
			int x1 = m_points[0].x();
			int y1 = m_points[0].y();
			int x2 = event->pos().x();
			int y2 = event->pos().y();
			rect_points.push_back(QPoint(x1, y1));
			rect_points.push_back(QPoint(x1, y2));
			rect_points.push_back(QPoint(x2, y2));
			rect_points.push_back(QPoint(x2, y1));
			SharedProcess process = 
				ProcessFactory::getPolygonSelectionProcess(
					rect_points);
			emit newProcess(process);
			break;
		}
		break;
	case SelectCircle:
		switch (m_points.size()) {
		case 1:
			int cx = m_points[0].x();
			int cy = m_points[0].y();
			int x0 = event->pos().x();
			int y0 = event->pos().y();
			int r = sqrt((cx - x0) * (cx - x0) + 
				     (cy - y0) * (cy - y0));
			SharedProcess process = 
				ProcessFactory::getEllipseSelectionProcess(
					cx, cy, r, r);
			emit newProcess(process);
			break;
		}
		break;
	default:
		break;
	}
}

void PaintOperator::mouseReleased(QMouseEvent *)
{
	/* empty */
}

void PaintOperator::setState(State state)
{
	m_state = state;
	m_points.clear();
	SharedProcess process = 
		ProcessFactory::getPolygonSelectionProcess(m_points);
	emit newProcess(process);
}
