#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "headers.h"

using namespace std;

//Take note that some node have been commented and would have to be undone then have the size of the string increased or dynamicaly allocated
//also i would have to reformat the file to avoid comments too long and joint char like }# instead of } # by replacing the former with the later using the c++ string function
static char *ptr = NULL;


char *nextWord(char *inputstring, char * nextwd){
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
		if((*inputstring) == '\0' ){
			 		//printf("End of file\n");
			 		return inputstring;
			 }
	char *strptr; //pointer to string
	char tempchar[50] = "";
	strptr = inputstring; 
	
	while(true){
	//strcpy(inputstring,strptr);
	switch(*strptr)
  {
   
   /* Whitespace:  Simply ignore. */
   case ' ':
   case '\n':
   case '\r': 
   case '\t':
   case ',':
   		strptr++;
   break;

   /* Comment:  Ignore until end of line. */
   case '#':
    do {
     strptr++;
    } while((*strptr) != '\n' && (*strptr) != '\r' && (*strptr) != EOF);
    break;
    
   default:
   		if((*strptr) == '\0' ){
			 		//printf("End of file\n");
			 		return strptr;
			 }
			 
			 int count = 0;
			 while(((*strptr) != ' ') && ((*strptr) != '\0') && ((*strptr) != '\n') && ((*strptr) != '\t')){
			 	
			 	tempchar[count] = (*strptr);
			 	//printf("%c\n", *strptr);
			 	strptr++;
			 	count++;	 	
			 }
			 
			 tempchar[count] = '\0';
			 strcpy(nextwd,tempchar);
			 #ifdef GETWORD
			 cout << nextwd << endl << endl;
			 #endif
			 return strptr;
			
			 //printf("found %s\n", tempchar);
			 	//printf("%s\n",strptr);
			 	
   	break;
  }
   		
	} 

}


bool findKeyWord(char *inputstring, int kw)
{
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	if(strcmp(inputstring , keyword[kw]) == 0){
		//printf("Found the %s keyword\n", inputstring);
		return 1; 
	}else{
		//printf("Not keyword\n");
		return 0;
	}

}

void stringcopy(string &str1, char *str2)
{
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	int i;
	
	for(i = 0; str2[i] != '\0'; i++){
		//cout << str1[i] << " " << str2[i] << endl;
		//str1[i] = str2[i];
			str1.push_back(str2[i]);
		
	}
		str1[i] = '\0';
		
		//cout << str1 << endl;
}

int stringcompare(string &str1, char *str2)
{
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	return strcmp(str1.c_str() , str2);
}

char *getNextWord(char * instring, char *nextword)
{
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	//get the next word;
	if(ptr == NULL){
		ptr = nextWord( instring ,nextword);
	}else {
		ptr = nextWord( ptr ,nextword);
	}
	
	if(*ptr == '\0')
		return 0;
	else 
		return ptr;
	//check if ptr is still null and return false	
}
 
char *getNextWord( char *nextword)
{	
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		ptr = nextWord( ptr ,nextword);
		
		if(*ptr == '\0')
			return 0;
		else 
			return ptr;

}

void replaceStringChars(string &str, char ch,const char *rstring)
{
	 int pos = str.find( ch );
	 
	 while ( pos != string::npos )
   {
   	//cout << "ch has "<< ch << "and rstring has " << rstring << endl;
      str.replace( pos, 1, rstring, 0,3 );
      pos = str.find( ch , pos + 2 );
   } 

}

void formatString(char *instring)
{
	string str;
	//cout << " before convetion "<< endl;
	//cout << instring << endl;
	stringcopy(str, instring);
	
   replaceStringChars(str ,'#', "\n# ");
   replaceStringChars(str ,'{', "\n{\n");
   replaceStringChars(str ,'}', "\n}\n");
   replaceStringChars(str ,'[', "\n[\n");
   replaceStringChars(str ,']', "\n]\n");
   replaceStringChars(str ,',', " , ");
   
  strcpy(instring, str.c_str());
  
  //cout << "After the convertion " << endl;
  //cout << instring << endl;


}
 
