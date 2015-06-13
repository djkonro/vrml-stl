#ifndef HEADERS_H
#define HEADERS_H

#define KWDEF 	0
#define KWUSE 	1
#define KWPROTO  2
#define MAXSTRSIZE 512

#include <iostream>
#include <string>


using namespace std;

static const char *keyword[]= { "DEF", "USE", "PROTO"};
char *nextWord(char *inputstring, char * nextwd);
bool findKeyWord(char *inputstring, int kw);
void stringcopy(string &str1, char *str2);
int stringcompare(string &str1, char *str2);
char *getNextWord(char * instring, char *nextword);
char *getNextWord(char *nextword);
void replaceStringChars(string &str, char ch,const char *rstring);
void formatString(char *instring);
int findFieldName(char *instring);

#endif
