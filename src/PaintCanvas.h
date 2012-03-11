#include <QWidget>
#include <QImage>

class QImage;

class PaintCanvas : public QWidget {
public:
	PaintCanvas();
	~PaintCanvas();
	void loadImage(const QString &filename);
protected:
	virtual void paintEvent(QPaintEvent *event);
private:
	QImage displayImage;
	bool isChanged;
};
