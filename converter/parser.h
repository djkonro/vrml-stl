/**
 *
 * Author: Djimeli Konrad
 *
 */

#ifndef PARSER_H
#define PARSER_H

#include <vector> 
#include "string_util.h"

using namespace std;

class PARSER
{	
	public:
	vector<string> userdeftypes; //Store DEF node names
	vector<string> protodeftypes; //Store PROTO node names
	vector<NODE *> protonodelist; //Stores pointer to PROTO nodes
	vector<NODE *> defnodelist;  //Stores pointer to DEF nodes
	vector<double> scenevert;  //Store all vertices in the scenegraph
	NODE rootnode;   //Parent scene node
	int ntopchild; // Number of direct children to the root node
	
	void parseScene(char *string);
	NODE *parseNodeString(char *instring, NODE * node);
	NODE *parsekwdef(NODE * node);
	NODE *parsekwuse(char *instring, NODE * node);
	NODE *parseNode(char *instring, NODE * node);
	int getChildNodeList(NODE *rtnode, vector<NODE*> &childlist);
	int copyNode(NODE * destnode , NODE * sourcenode);
	void transformChild(NODE * pnode);
	NODE * parseProtoNode(char *instring, NODE * node);
	void getSceneVert(vector<NODE*> &childlist, vector<double> &svert);
	void freeSceneNode(vector<NODE*> &childlist);
	
};

#endif
