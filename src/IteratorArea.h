#ifndef _ITERATORAREA_H_
#define _ITERATORAREA_H_

class IteratorArea {
public:
	virtual int startX() = 0;
	virtual int startY() = 0;
	virtual int endX() = 0;
	virtual int endY() = 0;
	virtual bool contains(int x, int y) = 0;
	virtual bool inside_contains(int x, int y) = 0;
};

class RectangleIteratorArea : public IteratorArea {
public:
	RectangleIteratorArea(int x, int y, int width, int height);
	virtual int startX();
	virtual int startY();
	virtual int endX();
	virtual int endY();
	virtual bool contains(int x, int y) = 0;
	virtual bool inside_contains(int x, int y) = 0;
private:
	int m_start_x;
	int m_start_y;
	int m_end_x;
	int m_end_y;
};

#endif /* _ITERATORAREA_H_ */
