/**
 *
 * Author: Djimeli Konrad
 *
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include "file_util.h"

using namespace std;
//Constructor with filename a parameter
FileUtil::FileUtil(const char *fname)
{	int len;
	len = strlen(fname);
	this->filename = new char[len];
	strcpy(this->filename,fname);
}

FileUtil::~FileUtil()
{
}

//checks file type to note the format being processed and returns an int corresponding to file type
int 
FileUtil::getFileType() 
{	
	unsigned char format[10]; 
	
	FILE *fp = fopen(filename, "rb"); 
	
	if (!fp)
		return FILE_TYPE_UNKNOWN; //return with unknown type if it could not open file
	if (fread(format, sizeof(unsigned char), 10, fp) != 10) {
		fclose(fp);
		return FILE_TYPE_UNKNOWN;
	}

	fclose(fp);

	int fileType = FILE_TYPE_UNKNOWN;
	
	//compares file formate with known formats to check for vrml version 1 or 2
	if (strncmp((char *)format,"#VRML V2.0",10) == 0) {
			fileType = FILE_TYPE_VRML;//vrml version 2
		}
	if (strncmp((char *)format,"#VRML V1.0",10) == 0) {
			fileType = FILE_TYPE_VRML1;//vrml version 1
			
		}
		
	return fileType;
}

//Stores the file input in a char * 
char *
FileUtil::storeFileInput()
{	
	int size, i;
	ifstream infile(filename, ios::in);
	
	infile.seekg(0, ios::end);
	size = infile.tellg();  //Get file size
	infile.seekg(0, ios::beg);
	
	fileinput = new char[(2*size) + 1];
	
	for(i = 0; i < size; i++){
		fileinput[i] = infile.get();
	}
	fileinput[i] = '\0';
	
	infile.close();
	
	return fileinput;
}

char *
FileUtil::getFileData()
{
	return this->fileinput;
}

void
FileUtil::freeFileInput()
{	
	delete [] fileinput;
}
