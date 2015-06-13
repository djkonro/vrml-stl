#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include "file_util.h"

using namespace std;

FileUtil::FileUtil(const char *filename)
{	int len;
	len = strlen(filename);
	this->filename = new char[len];
	strcpy(this->filename,filename);
}

FileUtil::~FileUtil()
{
	//delete [] fileinput;
}

//checks file type to note the format being processed and returns an int corresponding to file type
int 
FileUtil::getFileType() 
{	
	unsigned char format[10]; //string to hold file format
	char file[10000];
	
	
	FILE *fp = fopen(filename, "rb"); //pointer to file to be read
	
	if (!fp)	
		return FILE_TYPE_UNKNOWN; //return with unknown type if it could not open file
	if (fread(format, sizeof(unsigned char), 10, fp) != 10) {//read the file and store the first 10 char int format[]
		fclose(fp);
		return FILE_TYPE_UNKNOWN;
	}
	
	//fscanf(fp,"%s",file);
	//cout << file<<endl;
	
	fclose(fp);

	int fileType = FILE_TYPE_UNKNOWN;
	
	//compares file formate with known formats co check for vrml version 1 or 2
	if (strncmp((char *)format,"#VRML V2.0",10) == 0) {
			fileType = FILE_TYPE_VRML;//vrml version 2
		}
	if (strncmp((char *)format,"#VRML V1.0",10) == 0) {
			fileType = FILE_TYPE_VRML1;//vrml version 1
			
		}
		
	return fileType;
}

char *
FileUtil::storeFileInput()
{	
	int size, i;
	ifstream infile(filename, ios::in);
	
	infile.seekg(0, ios::end);
	size = infile.tellg();
	infile.seekg(0, ios::beg);
	
	fileinput = new char[(2*size) + 1];
	
	for(i = 0; i < size; i++){
		fileinput[i] = infile.get();
	}
	fileinput[i] = '\0';
	return fileinput;
}

char *
FileUtil::getFileData()
{
	return this->fileinput;
}


