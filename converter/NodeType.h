#ifndef nt
#define nt

#include <iostream>
#include <vector> // list class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator
#include <cstring>
#include "headers.h"
#include "NODE.h"


#define NODE_APPEARANCE         1
#define NODE_BOX                2
#define NODE_CONE               3
#define NODE_COORDINATE         4
#define NODE_CYLINDER           5
#define NODE_GROUP              6
#define NODE_INDEXEDFACESET     7
#define NODE_INDEXEDLINESET     8
#define NODE_MATERIAL           9
#define NODE_SHAPE              10
#define NODE_SPHERE             11
#define NODE_TRANSFORM          12
#define NODE_PROTO              13

#define NODETYPEMAX             14

using namespace std;

static const char *nodeTypeString[] = {
"",
"Appearance", 
"Box",
"Cone",
"Coordinate",
"Cylinder",
"Group",
"IndexedFaceSet",
"IndexedLineSet",
"Material",
"Shape",
"Sphere",
"Transform",
"PROTO"
};

 
class NODETYPE
{
public:
//have all the diffent type of nodes

//have function to find node type with returns the int representation for the node

int findNodeType(string instring)
{	
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	int i;

	for(i = 1; i < NODETYPEMAX; i++){
	//cout << "string = " << instring.c_str() << " nodetypes = " << nodeTypeString[i] << endl;
		if(strcmp(instring.c_str(), nodeTypeString[i]) == 0){
			return i;
		}
	}
	
	return 0;
}

int findNodeType(NODE *innode)
{	
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	if(innode){
		return findNodeType(innode->nodetypename);
	}
	return 0;
}
//This node have to be stored in a char array and then also have to be #defined, with unique numbers


};

#endif
