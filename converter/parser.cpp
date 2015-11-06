/**
 *
 * Author: Djimeli Konrad
 *
 */


#include <vector> 
#include <algorithm> 
#include <iterator> 
#include <cstring>
#include "string_util.h"
#include "node.h"
#include "node_type.h"
#include "parser.h"
#include "transform_node.h"

using namespace std;

char *getNextWord(char * instring, char *nextword);
char *getNextWord( char *nextword);
bool findKeyWord(char *inputstring, int kw);
void stringcopy(string &str1, char *str2);
int stringcompare(string &str1, char *str2);
int findFieldName(char *instring);
 

//Main parser which calls sub parsers and stores parent node of
//the scenegraph as children of rootnode
void
PARSER::parseScene(char *string){
	char nextwd[MAXSTRSIZE];

	while(getNextWord(string, nextwd)){
		NODE *node = NULL;
		
		if((node = parseNodeString(nextwd, node))){
			if(node != NULL){
				rootnode.children.push_back(node);
				ntopchild++;
				continue;
			}
		}
	}
}

//Calls parsers for different keywords
NODE *
PARSER::parseNodeString(char *instring, NODE * node){
	if(findKeyWord(instring , KWDEF)){
		if((node = parsekwdef(node)))
		return node;
	}
	
	if(findKeyWord(instring , KWUSE)){
		if((node = parsekwuse(instring, node)))
		return node;
	}
	
	if(findKeyWord(instring , KWPROTO)){
		char protoname[MAXSTRSIZE];
		int sqbrcount = 0;
		string protostring;

		getNextWord(protoname);
		stringcopy(protostring , protoname);
		
		while(getNextWord(protoname)){
			if(*protoname == '['){
				sqbrcount++;
			}

			if(*protoname == ']'){
				sqbrcount--;
				if(sqbrcount == 0){
					break;
				}
			}
		}
		
		if((node = parseNode(instring, node))){
			protodeftypes.push_back(protostring);
			protonodelist.push_back(node);
			return NULL;
		}
	}
	
	if((node = parseProtoNode(instring, node))){
		return node;
	}
	
	
	if((node = parseNode(instring, node))){
		return node;
	}
	
	return NULL;
}

//Parses the DEF keyword
NODE *
PARSER::parsekwdef(NODE * node)
{
	char nextwd[MAXSTRSIZE];
	string defstring;
	
	getNextWord(nextwd); //get the defnode idname
	stringcopy(defstring , nextwd);// convert defnode idname from type char * to c++ string
	getNextWord(nextwd);
	
	node = parseNode(nextwd, node);
	if(node != NULL){
		userdeftypes.push_back(defstring); // save defnode idname in userdeftype vector
		defnodelist.push_back(node); //stores pointer to node found in defnodelist 
	}else
		return NULL;

	return node;

}

//Parser for the USE keyword
NODE *
PARSER::parsekwuse(char *instring, NODE * node)
{
	int i, ntype;
	
	getNextWord(instring);
	
	for(i = userdeftypes.size() - 1; i >= 0 ; i--){
		if(stringcompare(userdeftypes[i], instring) == 0){ //Search for node in userdeftype vector
			NODETYPE tnode;
			ntype = tnode.findNodeType(defnodelist[i]);
			node = new NODE;
			node = node->createNewNode(ntype , node);  //Create instances of node and copies node data
			node->copyNodeData(node, defnodelist[i], ntype); 
			node->copyNode( node , defnodelist[i]);
			return node;
		}
	}
	
	return NULL;
}

//Final parser, parses node and get data/fields
NODE *
PARSER::parseNode(char *instring, NODE * node)
{
	
	string nextwd;
	NODETYPE ntype;
	NODE tempnode;
	int nodeid, curly = 0;
	char nextstr[MAXSTRSIZE];

	stringcopy( nextwd, instring);
	nodeid = ntype.findNodeType(nextwd);
	node = parseProtoNode(instring, node);//Check first for PROTO  node
	
	if(node != NULL){
		return node; // If node is  PROTO then return pointer to node
	}  
	
	if(!nodeid) return NULL;

	node = tempnode.createNewNode(nodeid, node);
	getNextWord(nextstr);

	
	if(strcmp("{", nextstr) == 0) //Ensure open curly bracket after node name
	{
		curly++;
	}else{
		cout << "Experted open curly bracket at " << nextstr << endl; 
		return NULL;
	}
	
	while(getNextWord(nextstr)){
		NODE *tnodeptr;
		
		if(int n = node->findFieldName(nextstr)){  //Get field for node
			node->getField(n , node);
		}
		
		if((tnodeptr = parseNodeString(nextstr, tnodeptr))){  //Parse children node and store in scenegraph
			if(tnodeptr != NULL){
				node->children.push_back(tnodeptr);
				continue;
			}
		}
		
		if(strcmp("{", nextstr) == 0){
			curly++;
			continue;
		}

		if(strcmp("}", nextstr) == 0){
			curly--;
			if(curly == 0){
				break;
			}
		}
	}
	return node;
}

//Get list of children for specified node
int 
PARSER::getChildNodeList(NODE *rtnode, vector<NODE*> &childlist)
{
	unsigned int i; 

	if(rtnode->children.size()){
		for(i = 0; i < rtnode->children.size(); i++){
		childlist.push_back(rtnode->children[i]);
		getChildNodeList(rtnode->children[i], childlist);
		}
	}else{
		return 0;
	}
	
	return 1;
}

//Parser for PROTO node
NODE *
PARSER::parseProtoNode(char *instring, NODE * node)
{
	int i;

	for(i = protodeftypes.size() - 1; i >= 0 ; i--){  //Searches for node in protodeftypes vector
		if(stringcompare(protodeftypes[i], instring) == 0){
			NODETYPE tnode;
			node = new NODE;
			node = node->createNewNode(tnode.findNodeType(protonodelist[i]), node);
			node->copyNode(node , protonodelist[i]);
			return node;
		}
	}
	return NULL;
}

//Stores all vertices found in parser vector
void
PARSER::getSceneVert(vector<NODE*> &childlist, vector<double> &svert){
	
	int size = static_cast<int>(childlist.size());
	int i;
	unsigned int l;
	
	for(i = 0; i < size; i++){
		if(childlist[i]->nnodetype == NODE_CONE){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}else if(childlist[i]->nnodetype == NODE_BOX){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}else if(childlist[i]->nnodetype == NODE_CYLINDER){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}else if(childlist[i]->nnodetype == NODE_SPHERE){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}else if(childlist[i]->nnodetype == NODE_INDEXEDFACESET){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}else if(childlist[i]->nnodetype == NODE_INDEXEDLINESET){
			for(l = 0; l < childlist[i]->vertics.size(); l++){
				svert.push_back(childlist[i]->vertics[l]);
			}
		}
	}
}

void
PARSER::freeSceneNode(vector<NODE*> &childlist){
	
	int size = static_cast<int>(childlist.size());
	int i;

	for(i = size-1; i >= 0; i--){
		delete childlist[i];
	}
}


