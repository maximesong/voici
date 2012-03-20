#include "BlockProcess.h"

#include "BlockMap.h"
#include "BlockIterator.h"

BlockProcess::BlockProcess(BlockIterator *iter, BlockMap *map,
			   const QString &processName)
	: ImageProcess(processName)
{
	m_map = map;
	m_iter = iter;
}

QImage BlockProcess::generateNewImage(const QImage &image)
{
	QImage newImage = image;
	m_iter->iterate(&newImage, m_map);
	return newImage;
}

void BlockProcess::setBlockMap(BlockMap *map)
{
	delete m_map;
	m_map = map;
}

void BlockProcess::setBlockIterator(BlockIterator *iter)
{
	delete m_iter;
	m_iter = iter;
}
