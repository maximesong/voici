#ifndef _PROCESSFACTORY_H_
#define _PROCESSFACTORY_H_

#include <QVector>
#include <QImage>
#include <QRect>
#include <QPoint>
#include <QSharedPointer>

#include "VoiciGlobal.h"
#include "Process.h"
#include "IteratorArea.h"

class ProcessFactory : public QObject {
	Q_OBJECT
public:
	ProcessFactory();
	static SharedProcess getStandardGrayProcess(QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getBinaryProcess(int low = 0, 
					      int high = MAX_PIXEL_VALUE,
					      QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getConvolutionProcess(int rows, int columns, 
						   int centerRow, int centerColumn,
						   const QVector<double> &matrix,
						   QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getLinearProcess(double k, double b,
					      QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getMidlevelNonlinearMap(double c, double max,
						     QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	
	static SharedProcess getImageLinearBlendProcess(const QImage &image,
							double rate1, 
							double rate2,
							QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));

	static SharedProcess getImageProductProcess(const QImage &image,
						    double coefficient = 1.0,
						    QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getImageQuotientProcess(const QImage &image,
						     double coefficient = 1.0,
						     QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	
	static SharedProcess getQuickGaussBlurProcess(double vert, double horz);

	static SharedProcess getBilinearScaleProcess(int width, int height);

	static SharedProcess getNearestNeighbourScaleProcess(int width, 
							     int height);

	static SharedProcess getNearestNeighbourRotateProcess(double rotateAngle);

	static SharedProcess getMedianFilterProcess(int m, int n,
						    QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));
	static SharedProcess getMeanFilterProcess(int m, int n,
						  QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));

	static SharedProcess getThresholdProcess(int low, int high,
						 QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));

	static SharedProcess getUnsetThredsholdProcess();

	static SharedProcess getHistogramEqualizationProcess(const QImage &image,
							     QSharedPointer<IteratorArea> area = QSharedPointer<IteratorArea>(0));

	static SharedProcess getPolygonSelectionProcess(QVector<QPoint> points);

	static SharedProcess getPolylineSelectionProcess(QVector<QPoint> points);
private:
	static SharedProcess buildDynamicProcess(SharedImageProcesser processer);
	static SharedProcess buildPreProcess(PreProcesser id,
					     SharedImageProcesser processer);
	static SharedProcess buildPostProcess(PostProcesser id,
					      SharedImageProcesser processer);
};

#endif /* _PROCESSFACTORY_H_ */
