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
	static SharedProcess getStandardGrayProcess(SharedArea area = ALL_AREA);
	static SharedProcess getBinaryProcess(int low = 0, 
					      int high = MAX_PIXEL_VALUE,
					      SharedArea area = ALL_AREA);
	static SharedProcess getConvolutionProcess(int rows, int columns, 
						   int centerRow, int centerColumn,
						   const QVector<double> &matrix,
						   SharedArea area = ALL_AREA);
	static SharedProcess getLinearProcess(double k, double b,
					      SharedArea area = ALL_AREA);
	static SharedProcess getMidlevelNonlinearMap(double c, double max,
						     SharedArea area = ALL_AREA);
	
	static SharedProcess getImageLinearBlendProcess(const QImage &image,
							double rate1, 
							double rate2,
							SharedArea area = ALL_AREA);

	static SharedProcess getImageProductProcess(const QImage &image,
						    double coefficient = 1.0,
						    SharedArea area = ALL_AREA);
	static SharedProcess getImageQuotientProcess(const QImage &image,
						     double coefficient = 1.0,
						     SharedArea area = ALL_AREA);
	
	static SharedProcess getQuickGaussBlurProcess(double vert, double horz);

	static SharedProcess getBilinearScaleProcess(int width, int height);

	static SharedProcess getNearestNeighbourScaleProcess(int width, 
							     int height);

	static SharedProcess getNearestNeighbourRotateProcess(double rotateAngle);

	static SharedProcess getMedianFilterProcess(int m, int n,
						    SharedArea area = ALL_AREA);
	static SharedProcess getMeanFilterProcess(int m, int n,
						  SharedArea area = ALL_AREA);

	static SharedProcess getThresholdProcess(int low, int high,
						 SharedArea area = ALL_AREA);

	static SharedProcess getUnsetThredsholdProcess();

	static SharedProcess getHistogramEqualizationProcess(const QImage &image,
							     SharedArea area = ALL_AREA);

	static SharedProcess getPolygonSelectionProcess(QVector<QPoint> points);

	static SharedProcess getEllipseSelectionProcess(int cx, int cy,
							int rx, int ry);


	static SharedProcess getErosionProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);
	static SharedProcess getDilationProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getOpenProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getCloseProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getGrayErosionProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);
	static SharedProcess getGrayDilationProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getGrayOpenProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getGrayCloseProcess(int rows, int columns, 
					       int centerRow, int centerColumn,
					       const QVector<int> &matrix,
					       SharedArea area = ALL_AREA);

	static SharedProcess getMorphoSkeletonProcess();
	static SharedProcess getMorphoDistanceProcess();

private:
	static SharedProcess buildDynamicProcess(SharedImageProcesser processer);
	static SharedProcess buildPreProcess(PreProcesser id,
					     SharedImageProcesser processer);
	static SharedProcess buildPostProcess(PostProcesser id,
					      SharedImageProcesser processer);
};

#endif /* _PROCESSFACTORY_H_ */
