/**
 *
 * Author: Djimeli Konrad
 *
 */

#ifndef NODE_TYPE_H
#define NODE_TYPE_H

#include "node.h"

#define NODETYPEMAX       14

using namespace std;

class NODE;  //foward declaration of class
 
class NODETYPE
{
	public:
	int findNodeType(string instring);
	int findNodeType(NODE *innode);
};

#endif

