#include "RotateProcess.h"

RotateProcess::RotateProcess(double rotateAngle, const QString &processName)
	: ImageProcess(processName)
{
	counter_clock_rotate_angle = rotateAngle;
}

