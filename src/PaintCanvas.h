#include <QWidget>

class QImage;

class PaintCanvas : public QWidget {
public:
	PaintCanvas(QWidget *parent, const QImage &image);
slots:
	void redraw();
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	const QImage &m_image;
};
