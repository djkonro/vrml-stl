/**
 *
 * Author: Djimeli Konrad
 *
 */

#include <cstring>
#include "string_util.h"
#include "node.h"
#include "node_type.h"

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


int
NODETYPE::findNodeType(string instring)
{
	int i;

	for(i = 1; i < NODETYPEMAX; i++){
		if(strcmp(instring.c_str(), nodeTypeString[i]) == 0){
			return i;
		}
	}
	
	return 0;
}

int
NODETYPE::findNodeType(NODE *innode)
{
	if(innode){
		return innode->nnodetype;
	}
	return 0;
}

