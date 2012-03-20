#ifndef _BLOCKPROCESS_H_
#define _BLOCKPROCESS_H_

#include "ImageProcess.h"

class BlockMap;
class BlockIterator;

class BlockProcess : public ImageProcess {
public: 
	BlockProcess(BlockIterator *iter, BlockMap *map, 
		     const QString &processName = "Block Process");
	~BlockProcess();
	void setBlockMap(BlockMap *map);
	void setBlockIterator(BlockIterator *iter);
		
protected:
	virtual QImage generateNewImage(const QImage &image);
private:
	BlockMap *m_map;
	BlockIterator *m_iter;
};

#endif /* _BLOCKPROCESS_H_ */
