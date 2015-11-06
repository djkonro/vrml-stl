/**
 *
 * Author: Djimeli Konrad
 *
 */

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#define KWDEF		0
#define KWUSE		1
#define KWPROTO	2
#define MAXSTRSIZE	512

#include <iostream>
#include <vector>
#include <string>

using namespace std;

char *nextWord(char *inputstring, char * nextwd);
bool findKeyWord(char *inputstring, int kw);
void stringcopy(string &str1, char *str2);
int stringcompare(string &str1, char *str2);
char *getNextWord(char * instring, char *nextword);
char *getNextWord(char *nextword);
void replaceStringChars(string &str, char ch,const char *rstring);
void formatString(char *instring);
int findFieldName(char *instring);
void getSFVec4f(float *p);
void getInt(int &n);
void getFloat(float &n);
void getCoordIndex(vector<int> &ccoordindex);
void getPoint(vector<float> &cpoint);

#endif

