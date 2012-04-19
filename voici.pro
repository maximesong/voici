######################################################################
# Automatically generated by qmake (2.01a) Sun Mar 11 21:28:15 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . src
INCLUDEPATH += . src
OBJECTS_DIR += ./objs
MOC_DIR += ./tmp
RCC_DIR += ./tmp
TRANSLATIONS = languages/voici_zh.ts
CODECFORSRC  = UTF-8
RESOURCES = voici.qrc

#DEFINES += LANGUAGE_ZH
DEFINES += QUICK_TEST
CONFIG += debug

# Input
HEADERS += src/Exceptions.h \
           src/PaintCanvas.h \
           src/VoiciMainWindow.h \
           src/Histogram.h \
           src/HistogramChart.h \
           src/ThresholdPanel.h \
           src/SliderPanel.h src/VoiciGlobal.h \
           src/HistogramPanel.h \
           src/ProcessFactory.h \
           src/OtsuAlgorithm.h \
           src/EntropyMethod.h \
           src/KernelTable.h \
           src/ConvolutionPanel.h \
           src/AlgebraicProcessPanel.h \
           src/PreviewCanvas.h \
           src/ImageUtility.h \
           src/FilterPanel.h \
           src/ProcessPanel.h \
           src/TransformPanel.h \
           src/PointOperatorPanel.h \
           src/DoubleSliderPanel.h \

SOURCES += src/main.cpp \
           src/PaintCanvas.cpp \
           src/VoiciMainWindow.cpp \
           src/Histogram.cpp \
           src/HistogramChart.cpp \
           src/ThresholdPanel.cpp \
           src/SliderPanel.cpp \
           src/HistogramPanel.cpp \
           src/ProcessFactory.cpp \
           src/OtsuAlgorithm.cpp \
           src/EntropyMethod.cpp \
           src/KernelTable.cpp \
           src/ConvolutionPanel.cpp \
           src/AlgebraicProcessPanel.cpp \
           src/PreviewCanvas.cpp \
           src/ImageUtility.cpp \
           src/FilterPanel.cpp \
           src/ProcessPanel.cpp \
           src/TransformPanel.cpp \
           src/PointOperatorPanel.cpp \
           src/DoubleSliderPanel.cpp \


HEADERS += src/Process.h \
           src/ImageFamily.h \
           src/ImageProcesser.h \
           src/AbstractMap.h \
           src/Iterator.h \
           src/IteratorArea.h \
           src/Map.h \
           src/ContrastPanel.h \
           src/PaintOperator.h \

SOURCES += src/Process.cpp \
           src/ImageFamily.cpp \
           src/ImageProcesser.cpp \
           src/AbstractMap.cpp \
           src/Iterator.cpp \
           src/IteratorArea.cpp \
           src/Map.cpp \
           src/ContrastPanel.cpp \
           src/PaintOperator.cpp \
