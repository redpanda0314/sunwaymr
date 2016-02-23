/*
 * TextFileBlock.h
 *
 *  Created on: Jan 15, 2016
 *      Author: yupeng
 */

#ifndef HEADERS_TEXTFILEBLOCK_H_
#define HEADERS_TEXTFILEBLOCK_H_

#include <string>
#include "FileSource.h"
#include "Messaging.h"
using std::string;

int MAX_TEXT_FILE_BLOCK_SIZE = 3 * 1024 * 1024; // TODO configuration out of code

class TextFileBlock : public Messaging {
public:
	TextFileBlock();
	TextFileBlock(FileSource file, string location, int offset, int length);
	TextFileBlock(const TextFileBlock &tfb);
	virtual void messageReceived(int localListenPort, string fromHost, int msgType, string msg);
	string blockData(); // retrieve file data

	FileSource file;
	string location;
	int offset, length;


};

#endif /* HEADERS_TEXTFILEBLOCK_H_ */