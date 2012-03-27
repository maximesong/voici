#include "boost/test/unit_test.hpp"

#include "src/BlockIterator.h"
#include "src/MatrixBlockMap.h"
#include "src/ProcessFactory.h"
#include "src/ImageProcess.h"

#include <QImage>

BOOST_AUTO_TEST_CASE(my_test2)
{
	BOOST_CHECK(true);
	ImageProcess *process = ProcessFactory::getBinaryProcess(10, 11);
	QImage image;
	process->generateNewImage(image);
/*	BlockIterator *iter = new BlockIterator(1, 1, 1 ,1);
	iter->iterate(image, 
*/
}



	
