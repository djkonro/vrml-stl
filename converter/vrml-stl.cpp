/**
 *
 * Author: Djimeli Konrad
 *
 */

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include "file_util.h"
#include "node_type.h"
#include "node.h"
#include "parser.h"
#include "transform_node.h"

#define LEN 20

static const char *keyword[]= { "DEF", "USE", "PROTO" };
char *nextWord(char *inputstring, char * nextwd);
bool  findKeyWord(char *inputstring, int kw);
char *getNextWord(char * instring, char *nextword);
char *getNextWord( char *nextword);
void formatString(char *instring);
void get4vec(float *p);
void get3vec(float *p);

using namespace std;

void 
printVertices(vector<double> &svert, char *fname, int scale)
{	
	int i;
	float point[3];
	ofstream output(fname);
	int indx=0;
	
	output << "solid s0" << endl;
	output << "  facet normal 0 0 0" << endl;
	output << "    outer loop";
	
	for(int x = 0; x < svert.size() ; x++){
		if(((x)%3) == 0){
			output << endl;
			output << "      vertex ";
		}
		
		if(((x)%3) == 0){
			output << (svert[x]) << " ";
		}else{
			output << (svert[x]) << " ";
		}
				
		if(x == (svert.size()-1)){
			output << endl <<"    endloop"<< endl;
			output << "  endfacet"<< endl;
			output << "endsolid s0" << endl;
			break;
		}
		
		if(((1+x)%9) == 0){
			output << endl <<"    endloop"<< endl;
			output << "  endfacet"<< endl;
			output << "  facet normal 0 0 0"<< endl;
			output << "    outer loop";
		}	 	
	}
}


int main(int argc,char **argv)
{
	int type;
	char *tptr, *tempptr;
	char nextword[LEN];
	int i;
	int scale = 1;
	
	if(argc < 3){
		printf("Please enter :  %s  infile.wrl outfile.stl\n", argv[0]);
		return 0;
	}
	
	//add handle for pointer to no open valid file
	FileUtil test(argv[1]);
	
	type = test.getFileType();
	tptr = test.storeFileInput();
	tempptr = tptr;
	 
	
	if(type == 1){
		cout << "Does not yet have support for vrml version 1" << endl;
	}else if(type == 2){
		cout << "Vrml version 2" << endl;
	}else {
		cout << "Can not open or identify the file type" << endl; 
	}
	
	formatString(tempptr);
	
	vector<NODE*> childlist;
	PARSER parse;
	TRANSFORM trans;
	NODETYPE node;
	vector<NODE*> parent;
	
	parse.parseScene(tempptr);
	
	parse.getChildNodeList(&parse.rootnode , childlist);
	int j;
	
	cout << childlist.size() <<" Nodes found"<< endl;
	
	for(i = 0; i < childlist.size(); i++){	
		if(strcmp(childlist[i]->nodetypename.c_str(), "Cone") == 0){
			childlist[i]->sliceCone(childlist[i]);
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Box") == 0){
			childlist[i]->sliceBox (childlist[i]);
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Cylinder") == 0){
			childlist[i]->sliceCylinder(childlist[i]);
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Sphere") == 0){
			childlist[i]->sliceSphere(childlist[i]);
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedLineSet") == 0){
			childlist[i]->getPolyRep(childlist[i]);
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedFaceSet") == 0){
			childlist[i]->getPolyRep(childlist[i]);
		}
		
	}
	
	//Apply node transformations
	for(i = childlist.size() - 1; i >= 0; i--){
		if(strcmp(childlist[i]->nodetypename.c_str() , "Transform") == 0)	
			trans.transformChild(childlist[i]);
		
	}
	
	
	
	for(i = 0; i < childlist.size(); i++){
		if(strcmp(childlist[i]->nodetypename.c_str(), "Cone") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Box") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Cylinder") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "Sphere") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedFaceSet") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedLineSet") == 0){
			for(int l = 0; l < childlist[i]->vertics.size(); l++){
				parse.scenevert.push_back(childlist[i]->vertics[l]);
			}
		}
		
	}
	
	//Write vertices to outputfile
	printVertices(parse.scenevert , argv[2], scale);
				
	for(i = 0; i < childlist.size(); i++){
		delete childlist[i];
	}
	 
	 
	return 0;
} 

void get3vec(float *p){
	cout << p[0] << " " << p[1] << " "<< p[2] << endl;
}

void get4vec(float *p){
	cout << p[0] << " " << p[1] << " "<< p[2] << " "<< p[3] << endl;
}
