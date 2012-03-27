######################################################################
# Automatically generated by qmake (2.01a) Mon Mar 26 23:04:25 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . ../
INCLUDEPATH += . ../
OBJECTS_DIR += ./objs
MOC_DIR += ./tmp

# Input

HEADERS += src/Exceptions.h \
           src/PaintCanvas.h \
           src/VoiciMainWindow.h \
           src/Histogram.h \
           src/ImageCore.h \
           src/HistogramChart.h \
           src/ThresholdPanel.h \
           src/SliderPanel.h src/VoiciGlobal.h \
           src/ImageProcess.h \
           src/HistogramPanel.h \
           src/GrayPixelMap.h \
           src/PixelIterator.h \
           src/PixelMap.h \
           src/RatePixelMap.h \
           src/ProcessFactory.h \
           src/PixelProcess.h \
           src/GrayImageCore.h \
           src/RangeThresholdMap.h \
           src/MatrixBlockMap.h \
           src/BlockIterator.h \
           src/BlockProcess.h \
           src/BlockMap.h \
           src/OtsuAlgorithm.h \
           src/EntropyMethod.h \
           src/KernelTable.h \
           src/ConvolutionPanel.h

SOURCES += src/PaintCanvas.cpp \
           src/VoiciMainWindow.cpp \
           src/Histogram.cpp \
           src/ImageCore.cpp \
           src/HistogramChart.cpp \
           src/ThresholdPanel.cpp \
           src/SliderPanel.cpp \
           src/ImageProcess.cpp \
           src/HistogramPanel.cpp \
           src/GrayPixelMap.cpp \
           src/PixelIterator.cpp \
           src/PixelMap.cpp \
           src/RatePixelMap.cpp \
           src/ProcessFactory.cpp \
           src/PixelProcess.cpp \
           src/GrayImageCore.cpp \
           src/RangeThresholdMap.cpp \
           src/MatrixBlockMap.cpp \
           src/BlockIterator.cpp \
           src/BlockProcess.cpp \
           src/OtsuAlgorithm.cpp \
           src/EntropyMethod.cpp \
           src/KernelTable.cpp \
           src/ConvolutionPanel.cpp

SOURCES += test.cpp \
           process_test.cpp \


QMAKE_LFLAGS+= -Wl,-rpath=/usr/local/lib

LIBS += /usr/local/lib/libboost_unit_test_framework.so
