/**
 *
 * Author: Djimeli Konrad
 *
 */

#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>

#define FILE_TYPE_UNKNOWN    0
#define FILE_TYPE_VRML1      1
#define FILE_TYPE_VRML       2

using namespace std;

class FileUtil
{
private:
	char *filename;
	char *fileinput;

public:
	FileUtil(const char *filename);
	~FileUtil();
	int getFileType();
	char *storeFileInput();
	char *getFileData();
	void freeFileInput();
};

#endif
