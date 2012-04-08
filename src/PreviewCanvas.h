#ifndef _PREVIEWCANVAS_H_
#define _PREVIEWCANVAS_H_

#include <QLabel>
#include <QImage>

class ImageCore;

class PreviewCanvas : public QLabel {
	Q_OBJECT
public:
	PreviewCanvas(QWidget *parent = 0);
//	virtual ~PreviewCanvas();
public slots:
	virtual void drawImage(const ImageCore &imageCore);
	virtual void drawImage(const QImage &image);
	void setStandardSize(int width, int height);
	void setStandardWidth(int width);
	void setStandardHeight(int height);
private:
	int standard_width;
	int standard_height;
};

#endif /* _PREVIEWCANVAS_H_ */
