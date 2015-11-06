#include <iostream>
#include <stdio.h>
#include <fstream>
#include "file_util.h"
#include "NodeType.h"
#include "NODE.h"
#include "Parser.h"

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

int main(int argc,char **argv)
{
	int type;
	char *tptr, *tempptr;
	char nextword[LEN];
	int i;
	
	if(argc < 2){
		printf("Please enter %s and file name\n", argv[0]);
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
	
	/*while(true){
		tempptr = findKeyWord(tempptr, 0);
		tempptr = nextWord( tempptr,nextword);
		if(*tempptr == '\0')
			break;  
		
		//printf("%s\n", nextword);	
	} */
	
	
	vector<NODE*> childlist;
	PARSER parse;
	NODETYPE node;
	vector<NODE*> parent;
	
	parse.parseScene(tempptr);
	
	parse.getChildNodeList(&parse.rootnode , childlist);
	int j;
	
	//cout << "childlist -> " <<childlist.size() << endl;
	cout << "Rootnode child size " << parse.rootnode.children.size() << endl;
	
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
		
		for(i = childlist.size() - 1; i >= 0; i--){
			/*vector<NODE*> child;
			cout << "Node are -> " << childlist[i]->nodetypename << endl;
			parse.getChildNodeList( childlist[i], child);
			for(j = 0; j < child.size(); j++){
				cout << "	Has childern "<< child[j]->nodetypename << endl;
			}*/
			
			
			
			if(strcmp(childlist[i]->nodetypename.c_str() , "Transform") == 0){
				
				//cout << "Node are -> " << childlist[i]->nodetypename << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
				
				parse.transformChild(childlist[i]);
				
				vector<NODE*> tempch;
				
				//parse.getChildNodeList(childlist[i] , tempch);
				
				for(int p = 0; p < tempch.size(); p++){
				;
				//cout << "This node has child " << tempch[p]->nodetypename << endl;
				}
			//	cout << endl;
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "Cone") == 0){
				//cout << "Node are -> " << childlist[i]->nodetypename << endl;
				//cout << "Bottomradius : " <<childlist[i]->bottomradius << endl;
				//cout << "Height : " << childlist[i]->height << endl;
				
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
				
				 //return 0;
			
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "Sphere") == 0){
				//cout << "Node are -> " << childlist[i]->nodetypename << endl;
				//cout << "Radius : " <<childlist[i]->radius << endl;
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "Cylinder") == 0){
				//cout << "Node are -> " << childlist[i]->nodetypename << endl;
				//cout << "Radius : " <<childlist[i]->radius << endl;
				//cout << "Height : " << childlist[i]->height << endl;
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "Box") == 0){
				//cout << "Node are -> " << childlist[i]->nodetypename << endl;
				//cout << "Size : ";get3vec(childlist[i]->size);
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedFaceSet") == 0){
				/*cout << "Node are -> " << childlist[i]->nodetypename << endl;
				cout << "This node has " << childlist[i]->children.size() << endl;
				int c = childlist[i]->coordindex.size();
				int cc;
				cout << "Coordindex : ";
				for(cc = 0; cc < c; cc++){
					cout << childlist[i]->coordindex[cc] << " ";
					if((cc % 3) == 0)
					cout << endl;
				}
				
				c = childlist[i]->children[0]->point.size();
				cout << "\nPoint : ";
				for(cc = 0; cc < c; cc++){
					cout << childlist[i]->children[0]->point[cc] << " ";
					if((cc % 3) == 0)
						cout << endl;
				}
				
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
			
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "IndexedLineSet") == 0){
				cout << "Node are -> " << childlist[i]->nodetypename << endl;
				int l = childlist[i]->coordindex.size();
				int ll;
				cout << "Coordindex : ";
				for(ll = 0; ll < l; ll++){
					cout << childlist[i]->coordindex[ll] << " ";
					if((ll % 3) == 0)
						cout << endl;
				}
				
				
				l = childlist[i]->children[0]->point.size();
				cout << "\nPoint : ";
				for(ll = 0; ll < l; ll++){
					cout << childlist[i]->children[0]->point[ll] << " ";
					if((ll % 3) == 0)
						cout << endl;
				}
				
				//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);
			*/
			}else if(strcmp(childlist[i]->nodetypename.c_str(), "Coordinate") == 0){
				/*cout << "Node are -> " << childlist[i]->nodetypename << endl;
				int l = childlist[i]->coordindex.size();
				int ll;
				l = childlist[i]->point.size();
				cout << "\nPoint : ";
				for(ll = 0; ll < l; ll++){
					cout << childlist[i]->point[ll] << " ";
					if((ll % 3) == 0)
						cout << endl;
				}*/
			}
			
			//cout << endl;
			
			//cout << "This node has transform : " << endl;
				//cout << "Rotation : ";get4vec(childlist[i]->rotation);
				//cout << "Translation : "; get3vec(childlist[i]->translation);
				//cout << "Scale : "; get3vec(childlist[i]->scale);	
		}
		int scale = 1;
		
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
		
		
		
		cout << "Argv2 is" << argv[2] << endl;
		childlist[0]->vertics.clear();
		childlist[0]->vertics = parse.scenevert;
	
		childlist[0]->printConeSlice(childlist[0] , argv[2], scale);
		

		
	for(i = 0; i < childlist.size(); i++){
		delete childlist[i];
	}
	
	for(i = 0 ; i < parse.userdeftypes.size() ; i++){
				///cout << "found USE with node " << parse.userdeftypes[i]  << endl;
		
		}
	
	
	/*char word[MAXSTRSIZE]= "k";
	getNextWord(tptr, word);
		findKeyWord( word, 0);
		cout << (word) << endl;
		
	while (getNextWord(word)){
		
		findKeyWord( word, 0);
		cout << (word) << endl;
	}*/
	
	
	//nextPtr(tempptr);nextPtr(tempptr);nextPtr(tempptr);nextPtr(tempptr);
	
	//printf("%s\n", tptr);
	 
	 
	return 0;
} 

void get3vec(float *p){
	cout << p[0] << " " << p[1] << " "<< p[2] << endl;
}

void get4vec(float *p){
	cout << p[0] << " " << p[1] << " "<< p[2] << " "<< p[3] << endl;
}
