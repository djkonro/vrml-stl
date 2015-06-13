#ifndef pa
#define pa

#include <iostream>
#include <vector> // list class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator
#include "headers.h"


using namespace std;

#define KWDEF 	0
#define KWUSE 	1
#define KWPROTO  2
#define MAXSTRSIZE 512


char *getNextWord(char * instring, char *nextword);
char *getNextWord( char *nextword);
bool findKeyWord(char *inputstring, int kw);
void stringcopy(string &str1, char *str2);
int stringcompare(string &str1, char *str2);
int findFieldName(char *instring);
 
class PARSER
{	
	public:
	vector<string> userdeftypes;//list of userdefined types this is for when you see the USE keyword
	vector<string> protodeftypes;//list of proto types thsi is for  when you see a strange node 
	vector<NODE*> nodelist; //list of all node with root node to identify the begining of a node and are chronological
	vector<NODE *> protonodelist;							//that is added as nodes are added to the root node					
	vector<NODE *> defnodelist;
	vector<NODE*> scenenodelist;
	vector<double> scenevert;
	bool completetransform;
	
	NODE rootnode;
	int ntopchild; // Number of direct children to the root node
	
	
	void parseScene(char *string){
	#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	char nextwd[MAXSTRSIZE];
	
		while(getNextWord(string, nextwd)){
			NODE *node = NULL;

			if(node = parseNodeString(nextwd, node)){
				if(node != NULL){
				
					rootnode.children.push_back(node);
					//cout << "Adding to child\n\n";
					ntopchild++;
					//NOTE but first get node in place
					continue;
				}
			}
			
		}
		// cout << "DEF node list with " << defnodelist.size(); 
	}

	NODE *parseNodeString(char *instring, NODE * node){
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
		if(findKeyWord(instring , KWDEF)){
			if(node = parsekwdef(instring, node))
			return node;
		}
		
		if(findKeyWord(instring , KWUSE)){
			if(node = parsekwuse(instring, node))
			return node;
		}
		
		if(findKeyWord(instring , KWPROTO)){
			char protoname[MAXSTRSIZE];
			string protostring;
			
			
			getNextWord(protoname);
			stringcopy(protostring , protoname);
			
			while(getNextWord(protoname)){
				//cout << "In proto " << protoname << endl;
				if(*protoname == ']')
					break;
			}
			
			
			if(node = parseNode(instring, node)){
				protodeftypes.push_back(protostring);
				protonodelist.push_back(node);
				//cout << "Pushing back "<<node->nodetypename << endl;
				return NULL;
			}
		}
		
		if(node = parseProtoNode(instring, node)){
			return node;
		}
		
		
		if(node = parseNode(instring, node)){
			return node;
		}
		
		return NULL;
			
		//cout << instring << "\n\n\n\n";
	}
	
	NODE *parsekwdef(char *instring, NODE * node)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		char nextwd[MAXSTRSIZE];
		string defstring;
		
		getNextWord(nextwd); //get the defnode idname

		stringcopy(defstring , nextwd);// convert defnode idname from type char * to c++ string
		
		
		getNextWord(nextwd); //get childnode x3d node found def
		//cout << "found DEF "<< defstring <<" with node " << nextwd << endl;
		node = parseNode(nextwd, node);
		if(node != NULL){
			userdeftypes.push_back(defstring); // save defnode idname in userdeftype vector
			defnodelist.push_back(node);
			//cout << "found DEF "<< defstring <<" with node " << node->nodetypename << endl;
		}else
			return NULL;
			
		//cout << "found DEF "<< defstring <<" with node " << node->nodetypename << endl;
		return node;
		//node = parseNode(&defnode);
			
	}
	
	
	NODE *parsekwuse(char *instring, NODE * node)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		int i, ntype;
		
		getNextWord(instring);
		
		//cout << "found USE "<< instring <<endl << endl;
		for(i = userdeftypes.size() - 1; i >= 0 ; i--){
			//cout << "found USE "<< userdeftypes[i] << " and instring with " << instring << " and i = " << i <<endl << endl;
			
			if(stringcompare(userdeftypes[i], instring) == 0){
				NODETYPE tnode;
				ntype = tnode.findNodeType(defnodelist[i]);
				//node = defnodelist[i];
				node = new NODE;
				node = node->createNewNode(ntype , node);
				node->copyNodeData(node, defnodelist[i], ntype);
				
				copyNode( node , defnodelist[i]);
				//cout << "this USE node has " << node->nodetypename << endl;
				//node->nodetypename = "Appearance";
				//cout << "found USE "<< instring <<" with node " << defnodelist[i]->nodetypename  << endl;
				
				
				return node;
			}
		}
		
		return NULL;
	}
	
	NODE *parseNode(char *instring, NODE * node)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		string nextwd;
		NODETYPE ntype;
		NODE tempnode;
		int nodeid, curly = 0;
		//int i = 0;
		char nextstr[MAXSTRSIZE];
		
		
		stringcopy( nextwd, instring);
		
		
		nodeid = ntype.findNodeType(nextwd);
		node = parseProtoNode(instring, node);
		
		if(node != NULL){
			return node;
		}  
		
		if(!nodeid) return NULL;
		//cout << "inst = " << instring << " nextword(stcpy) = " << nextwd << " nodeid = " << nodeid << endl;
		node = tempnode.createNewNode(nodeid, node);
		getNextWord(nextstr);
		
		//node->parent = NULL;
		
		if(strcmp("{", nextstr) == 0)
		{
			curly++;
			//cout << "Found open curly for " << nextwd << endl;
		}else{
			cout << "Experted open curly bracket at " << nextstr << endl; 
			return NULL;
		}
		
		while(getNextWord(nextstr)){
			NODE *tnodeptr;
			
			if(int n = node->findFieldName(nextstr)){
				//cout << "Found field name " << nextstr << endl;
				node->getField(n , node);
			}
			//if (parseField(nextstr)){}
			
			if(tnodeptr = parseNodeString(nextstr, tnodeptr)){
				if(tnodeptr != NULL){
				//node->children.push_back(new NODE*);
				node->children.push_back(tnodeptr);
				//tnodeptr->parent = node;
				//cout << tnodeptr->nodetypename << " has parent " << tnodeptr->parent->nodetypename << endl;
				//node->nchild++;
				continue;}
				//delete tempnode;
			}
			
			if(strcmp("{", nextstr) == 0)
			{
				curly++;
				continue;
			//cout << "Found open curly brakects\n" << endl;
			}

			if(strcmp("}", nextstr) == 0)
			{
				curly--;
				if(curly == 0){
					//cout << "0 curly returning from " << node->nodetypename << endl;
					break;
				}
			//cout << "Found open curly brakects\n" << endl;
			}
		
		}
		
		return node;
	}
	
	int getChildNodeList(NODE *rtnode, vector<NODE*> &childlist){
		int i; 
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
		if(rtnode->children.size()){
			for(i = 0; i < rtnode->children.size(); i++){
				//cout << endl << "Getting child " << rtnode->children[i]->nodetypename << endl;
				childlist.push_back(rtnode->children[i]);
				getChildNodeList(rtnode->children[i], childlist);
				//cout << "There are chilldren\n\n";
			}
		}else{
			//childlist.push_back(rtnode);
			return 0;
		}
		
		return 1;
	
	}
	
	int copyNode(NODE * destnode , NODE * sourcenode){
	
		int i, ntype; 
		
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
		//cout << endl << "Source node " << sourcenode->nodetypename << " child " << sourcenode->children.size() << endl << endl;
		
		if(sourcenode->children.size()){
		
			for(i = 0; i < sourcenode->children.size(); i++){
				NODE * nptr;
				NODETYPE tnode;
				nptr = new NODE;
				ntype = tnode.findNodeType(sourcenode->children[i]);
				nptr =  nptr->createNewNode(ntype, nptr);
				nptr->copyNodeData(nptr, sourcenode->children[i], ntype);
				
				destnode->children.push_back(nptr);
				
				//cout << "this USE node has " << nptr->nodetypename << endl;
				//nptr->nodetypename = "Appearance";
				copyNode(destnode->children[i] , sourcenode->children[i]);
				
			}
			
		}else{
			//childlist.push_back(rtnode);
			return 0;
		}
		
	}
	
	void getSceneNode(vector<NODE*> &vec)
	{
		//getChildNodeList(&rootnode, vec);
	}
	
	void transformChild(NODE * pnode)
	{
	 cout << "trans called " << endl;
		vector<NODE*> mychildlist;
		int count;
		double temprotmat[16] ;//= {1,2,3,4};
		
		vector<double> tempvec;
		
		getChildNodeList(pnode, mychildlist);
		
		for(count = 0; count < mychildlist.size(); count++){
		
			if(mychildlist[count]->vertics.size()){
				
				for(int i = 0; i < (mychildlist[count]->vertics.size()); i+=3 ){
					//double temp[16] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };
					
					//pnode->matmultiply(temp , temp , pnode->rotmat);	
					temprotmat[0] = mychildlist[count]->vertics[i];
					temprotmat[1] = mychildlist[count]->vertics[i+1];
					temprotmat[2] = mychildlist[count]->vertics[i+2];
					temprotmat[3] = 1;
					//cout << "before " <<mychildlist[count]->vertics[i] << " "<< mychildlist[count]->vertics[i+1] << " " << mychildlist[count]->vertics[i+2] << endl; 
					pnode->matmultiply(temprotmat , temprotmat , pnode->rotmat);
					mychildlist[count]->vertics[i] = (temprotmat[0]*pnode->scale[0])+pnode->translation[0] ;
					mychildlist[count]->vertics[i+1] = (temprotmat[1]*pnode->scale[1])+pnode->translation[1];
					mychildlist[count]->vertics[i+2] = (temprotmat[2]*pnode->scale[2])+pnode->translation[2];
					//cout << "after " <<mychildlist[count]->vertics[i] << " "<< mychildlist[count]->vertics[i+1] << " " << mychildlist[count]->vertics[i+2] << endl; 
				}
					
			}
		}	
		
	}
	
	void doTransformChild(NODE *parent, NODE * child){
		
	}
	
	
	NODE * parseProtoNode(char *instring, NODE * node)
	{
		#ifdef FUNCLINE
			cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		int i;
		
			//cout << instring << endl;
		
		for(i = protodeftypes.size() - 1; i >= 0 ; i--){
			
			
			if(stringcompare(protodeftypes[i], instring) == 0){
				//cout << "found PROTO "<< protodeftypes[i] << " and instring with " << instring << " and i = " << i <<endl << endl;
				//node = defnodelist[i];
				NODETYPE tnode;
				node = new NODE;
				node = node->createNewNode(tnode.findNodeType(protonodelist[i]), node);
				cout << protonodelist[i]->nodetypename << endl;
				copyNode( node , protonodelist[i]);
				//cout << "this PROTO node has " << node->nodetypename << endl;
				//node->nodetypename = "";
				//cout << "found USE "<< instring <<" with node " << defnodelist[i]->nodetypename  << endl;
				
				
				return node;
			}
		}
		
		return NULL;
	}
	
	int doRotation(float *rot)
	{
		return (rot[0] || rot[1] || rot[2]);
	}
	
};

#endif
