/**
 *
 * Author: Djimeli Konrad
 *
 */

#include <vector>
#include <algorithm>
#include <iterator> 
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <fstream>

#include "string_util.h"
#include "node.h"
#include "node_type.h"
#include "transform_node.h"

using namespace std;

const double idmat[] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 };

static const char *fields[] = {
	"",
	"rotation",
	"scaleFactor",
	"translation",
	"set_orientation",
	"set_position",
	"solid",
	"tessellation",
	"scale",
	"radius",
	"point",
	"normal",
	"color",
	"index",
	"position",
	"scaleOrientation",
	"location",
	"colorPerVertex",
	"center",
	"normalPerVertex",
	"segments",
	"texture",
	"colorIndex",
	"geometry",
	"data",
	"string",
	"children",
	"bottomRadius",
	"name",
	"texCoord",
	"texCoordIndex",
	"url",
	"coord",
	"shaders",
	"coordIndex",
	"orientation",
	"appearance",
	"height",
	"size",
	"bottom",
	"side",
	"top"
};


char *getNextWord( char *nextword);
char *nextWord(char *inputstring, char * nextwd);
void getSFVec3f(float *p);
void getSFVec4f(float *p);
void getInt(int &n);
void getFloat(float &n);
void getCoordIndex(vector<int> &ccoordindex);
void getPoint(vector<float> &cpoint);

//Initialize transform node data
void
NODE::initTransform(NODE * node)
{
	node->scale[0] = 1; node->scale[1] = 1; node->scale[2] = 1;
	node->rotation[0] = 0; node->rotation[1] = 0; node->rotation[2] = 0; node->rotation[3] = 0;
	node->translation[0] = 0; node->translation[1] = 0; node->translation[2] = 0;	
}

	
NODE *
NODE::createNewNode(int nodetype, NODE *node)
{
	switch(nodetype){
		case NODE_APPEARANCE:
			node = new NODE;
			node->nnodetype = NODE_APPEARANCE;
			node->nodetypename = "Appearance"; 
			return node;   
		case NODE_BOX:
			node = new NODE;
			node->nnodetype = NODE_BOX;
			node->nodetypename = "Box";
			node->size[0] = 2.0f;node->size[1] = 2.0f;node->size[2] = 2.0f;
			return node;
		case NODE_CONE:
			node = new NODE;
			node->nnodetype = NODE_CONE;
			node->nodetypename = "Cone";
			node->height = 2.0f;
			node->bottomradius = 1.0f;
			return node;
		case NODE_COORDINATE:
			node = new NODE;
			node->nnodetype = NODE_COORDINATE;
			node->nodetypename = "Coordinate";
			return node;
		case NODE_CYLINDER:
			node = new NODE;
			node->nnodetype = NODE_CYLINDER;
			node->nodetypename = "Cylinder";
			node->radius = 1.0f;
			node->height = 2.0f;
			return node;
		case NODE_GROUP:
			node = new NODE;
			node->nnodetype = NODE_GROUP;
			node->nodetypename = "Group";
			return node;
		case NODE_INDEXEDFACESET:
			node = new NODE;
			node->nnodetype = NODE_INDEXEDFACESET;
			node->nodetypename = "IndexedFaceSet";
			return node;
		case NODE_INDEXEDLINESET:
			node = new NODE;
			node->nnodetype = NODE_INDEXEDLINESET;
			node->nodetypename = "IndexedLineSet";
			return node;
		case NODE_MATERIAL:
			node = new NODE;
			node->nnodetype = NODE_MATERIAL;
			node->nodetypename = "Material";
			return node;
		case NODE_SHAPE:
			node = new NODE;
			node->nnodetype = NODE_SHAPE;
			node->nodetypename = "Shape";
			return node;
		case NODE_SPHERE:
			node = new NODE;
			node->nnodetype = NODE_SPHERE;
			node->nodetypename = "Sphere";
			node->radius = 1.0f;
			return node;
		case NODE_TRANSFORM:
			node = new NODE;
			node->nnodetype = NODE_TRANSFORM;
			node->nodetypename = "Transform";
			memcpy(node->rotmat,idmat,sizeof(double)*16);
			initTransform(node);
			return node;
		case NODE_PROTO:
			node = new NODE;
			node->nnodetype = NODE_PROTO;
			node->nodetypename = "PROTO";
			node->isprotodef = 0;
			return node;
		default :
			return NULL;		  
	}
	
}

//Creates a copy of source node as destination node
//Uses by PROTO and DEF node to create instances of thier nodes 	
int
NODE::copyNode(NODE * destnode , NODE * sourcenode){
	unsigned int i;
	int ntype; 
		
	if(sourcenode->children.size()){
		for(i = 0; i < sourcenode->children.size(); i++){
			NODE * nptr;
			NODETYPE tnode;
			nptr = new NODE;
			ntype = tnode.findNodeType(sourcenode->children[i]);
			nptr =  nptr->createNewNode(ntype, nptr);
			nptr->copyNodeData(nptr, sourcenode->children[i], ntype);
			destnode->children.push_back(nptr);
			copyNode(destnode->children[i] , sourcenode->children[i]);
		}
	}else{
		return 0;
	}
	
	return 0;
}

//Copy data from source to destination node
int
NODE::copyNodeData(NODE *dnode, NODE *snode, int nodetype)
{
	dnode->nnodetype = snode->nnodetype;
		
	switch(nodetype){
		case NODE_APPEARANCE: 
			return 1;   
			break;
		case NODE_BOX:
			dnode->size[0] = snode->size[0];
			dnode->size[1] = snode->size[1];
			dnode->size[2] = snode->size[2];
			return 1;
			break;
		case NODE_CONE:
			dnode->height = snode->height;
			dnode->bottomradius = snode->bottomradius;
			return 1;
			break;
		case NODE_COORDINATE:
			dnode->point = snode->point;
			return 1;
			break;
		case NODE_CYLINDER:
			dnode->radius = snode->radius;
			dnode->height = snode->height;
			return 1;
			break;
		case NODE_GROUP:
			return 1;
			break;
		case NODE_INDEXEDFACESET:
			dnode->coordindex = snode->coordindex;
			return 1;
			break;
		case NODE_INDEXEDLINESET:
			dnode->coordindex = snode->coordindex;
			return 1;
			break;
		case NODE_MATERIAL:
			return 1;
			break;
		case NODE_SHAPE:
			return 1;
			break;
		case NODE_SPHERE:
			dnode->radius = snode->radius;
			return 1;
			break;
		case NODE_TRANSFORM:
			dnode->scale[0] = snode->scale[0]; 
			dnode->scale[1] = snode->scale[1];
			dnode->scale[2] = snode->scale[2];
			dnode->rotation[0] = snode->rotation[0]; 
			dnode->rotation[1] = snode->rotation[1]; 
			dnode->rotation[2] = snode->rotation[2]; 
			dnode->rotation[3] = snode->rotation[3];
			dnode->translation[0] = snode->translation[0]; 
			dnode->translation[1] = snode->translation[1]; 
			dnode->translation[2] = snode->translation[2];
			memcpy((void *)dnode->rotmat, (void *)snode->rotmat, sizeof(double)*16);
			return 1;
			break;
		case NODE_PROTO:
			return 1;
			break;
		default :
			return 0;
			break;		  
	 }
}

int
NODE::findFieldName(char *instring)
{
	int i;

		for(i = 1; i < FIELDNAMEMAX ; i++){
			if(strcmp(instring, fields[i]) == 0){
				return i;
			}
		}
		
		return 0; 
}
	
int 
NODE::getField(int fieldname, NODE * node)
{
	switch(fieldname){
		case FIELD_rotation:
			TRANSFORM trans;
			getSFVec4f(node->rotation);
			trans.matrotate(rotmat , node->rotation[3],node->rotation[0], node->rotation[1], node->rotation[2]);
			return 1; 
			break;
		case FIELD_scaleFactor:
			return 1;
			break;
		case FIELD_translation:
			getSFVec3f(node->translation);
			return 1;
			break;
		case FIELD_scale:
			getSFVec3f(node->scale);
			return 1;
			break;
		case FIELD_radius:
			getFloat(node->radius);
			return 1;
			break;
		case FIELD_point:
			getPoint(node->point);
			return 1;
			break;
		case FIELD_scaleOrientation:
			break;
		case FIELD_bottomRadius:
			getFloat(node->bottomradius);
			return 1;
			break;
		case FIELD_coord:
			break;
		case FIELD_coordIndex:
			getCoordIndex(node->coordindex);
			return 1;
			break;
		case FIELD_height:
			getFloat(node->height);
			return 1;
			break;
		case FIELD_size:
			getSFVec3f(node->size);
			return 1;
			break;
		case FIELD_bottom:
			break;
		case FIELD_side:
			break;
		case FIELD_top:
			break;
		}
		
		return 0;
}

//Splits cone primitive to polygons
void
NODE::sliceCone(NODE * node)
{
	float h = (node->height)/2;
	float r = node->bottomradius;
	float angle;
	int i;
	int coneslice = 20;
	
	for (i=0; i<coneslice; i++) {
		angle = PI*2*i/(double)coneslice;
		double next_angle = PI*2*(i+1)/(double)coneslice;
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
		node->vertics.push_back(0.0);
		node->vertics.push_back(-h);
		node->vertics.push_back(0.0);
		node->vertics.push_back(r*sin(next_angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(next_angle));
	}

	for (i=0; i<coneslice; i++) {
		angle = (double) (PI * 2 * (i+1.0f)) / (double) (coneslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
		angle = (float) (PI * 2 * (i+0.5f)) / (double)(coneslice);
		node->vertics.push_back(0.0);
		node->vertics.push_back(h);
		node->vertics.push_back(0.0);
		angle = (float) (PI * 2 * (i+0.0f)) / (double) (coneslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
	}
}

//Splits box primitive to polygons
void
NODE::sliceBox(NODE *node) {

	float x = node->size[0]/2;
	float y = node->size[1]/2;
	float z = node->size[2]/2;

	node->vertics.push_back(x);  node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(z);
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(z) ;
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z); 
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(-z); 
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(-z); 
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(-z); 
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(z); 
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(z) ;
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(z);
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(z) ;
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(z) ;
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
	node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(z); 
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(-z);
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z); 
	node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(z); 
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z);
	node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(z);


}

//Splits cylinder primitive to polygons
void
NODE::sliceCylinder (NODE *node) {
	
	float h = (node->height)/2;
	float r = node->radius;
	int i = 0;
	int cylinslice = 20;


	for (i = 0; i < cylinslice; i++) {
		double angle = PI*2*i/(double)cylinslice;
		double next_angle = PI*2*(i+1)/(double)cylinslice;
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
		node->vertics.push_back(0.0);
		node->vertics.push_back(-h);
		node->vertics.push_back(0.0);
		node->vertics.push_back(r*sin(next_angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(next_angle));
	}
	
	for (i = 0; i < cylinslice; i++) {
		double angle = PI*2*i/(double)cylinslice;
		double next_angle = PI*2*(i+1)/(double)cylinslice;
		node->vertics.push_back(r*sin(next_angle));
		node->vertics.push_back(h);
		node->vertics.push_back(r*cos(next_angle));
		node->vertics.push_back(0.0);
		node->vertics.push_back(h);
		node->vertics.push_back(0.0);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(h);
		node->vertics.push_back(r*cos(angle));
	}

	for (i=0; i<cylinslice; i++) {
		double angle;
		angle = (double) (PI * 2 * (i+1.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
		
		angle = (double) (PI * 2 * (i+0.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(h);
		node->vertics.push_back(r*cos(angle));
		
		angle = (double) (PI * 2 * (i+0.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));

		angle = (double) (PI * 2 * (i+1.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(-h);
		node->vertics.push_back(r*cos(angle));
		
		angle = (double) (PI * 2 * (i+1.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(h);
		node->vertics.push_back(r*cos(angle));
		
		angle = (float) (PI * 2 * (i+0.0f)) / (double) (cylinslice);
		node->vertics.push_back(r*sin(angle));
		node->vertics.push_back(h);
		node->vertics.push_back(r*cos(angle));
	}
}

//Splits sphere primitive to polygons
void
NODE::sliceSphere (NODE *node) {
	int split = 32;
	float rad = node->radius;
	int npoints = (1 + (split - 2) * split + 1) * 3;

	node->point.push_back(0.0);
	node->point.push_back(rad);
	node->point.push_back(0.0);
	
	int i = 0;
	for (i = 0; i < (split - 2); i++) {
		float phi = PI * (i + 1.0f) / (split - 1);
		for (int j = 0; j < split; j++) {
			float theta = 2.0f * PI * (j + (i % 2) * 0.5f) / split;
		   node->point.push_back(rad * sin(phi) * sin(theta));
		   node->point.push_back(rad * cos(phi));
		   node->point.push_back(rad * sin(phi) * cos(theta));	   
		}
	}
	
	node->point.push_back(0.0);
	node->point.push_back(-rad);
	node->point.push_back(0.0);
	
	for (i = 0; i < split; i++) {	
		node->coordindex.push_back(0);
		if (i == (split - 1)){
			node->coordindex.push_back(1);
		}
		else
			node->coordindex.push_back(1 + i + 1);
		node->coordindex.push_back(1 + i);
	}
	
  
	for (i = 0; i < (split - 3); i++) {
		for (int j = 0; j < split; j++) {
			int offset = 1 + i * split + j; 
			node->coordindex.push_back(offset);			
			if (j == split - 1)
				node->coordindex.push_back(offset - split + 1);			
			else
				node->coordindex.push_back(offset + 1);			
			if ((j == split - 1) && ((i % 2) == 1))
				node->coordindex.push_back(offset + i % 2);			
			else
				node->coordindex.push_back(offset + split + i % 2);			
			
			if (j == split - 1)
				node->coordindex.push_back(offset - split + 1);			
			else
				node->coordindex.push_back(offset + 1);			
			if ((j == split - 1) || ((j + 1 == split - 1) && (i % 2) == 1))
				node->coordindex.push_back(offset + 1 + i % 2);			
			else
				node->coordindex.push_back(offset + split + 1 + i % 2);			
			if ((j == split - 1) && ((i % 2) == 1))
				node->coordindex.push_back(offset + i % 2);			
			else
				node->coordindex.push_back(offset + split + i % 2);			
		}
	}
   
	for (i = 0; i < split; i++) {	
		int offset = npoints / 3 - 1 - split;
		node->coordindex.push_back(npoints / 3 - 1);
		node->coordindex.push_back(offset + i);
		if (i == (split - 1))
			node->coordindex.push_back(offset);
		else
			node->coordindex.push_back(offset + i + 1);
	   
	}
	
	getPolyRep(node);
}

//Stores vertice for polygonal nodes
void
NODE::getPolyRep(NODE *node) {
	
	int indexsize = static_cast<int>(node->coordindex.size());
	int i;
	if(node->nnodetype == NODE_SPHERE){
		for(i = 0; i < indexsize; i++){
			node->vertics.push_back(node->point[node->coordindex[i]*3]);
			node->vertics.push_back(node->point[node->coordindex[i]*3+1]);
			node->vertics.push_back(node->point[node->coordindex[i]*3+2]);
		}
	}else{
		for(i = 0; i < indexsize; i++){
			node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3]);
			node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3+1]);
			node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3+2]);
		}
	}
}

//Gets and stores vertices for nodes pointed to by noderef vector 
void
NODE::doMakePoly(vector<NODE*> &noderef)
{

	int ssize = static_cast<int>(noderef.size());
	int i;
	
	for(i = 0; i < ssize; i++){
		if(noderef[i]->nnodetype == NODE_CONE){
			noderef[i]->sliceCone(noderef[i]);
		}else if(noderef[i]->nnodetype == NODE_BOX){
			noderef[i]->sliceBox (noderef[i]);
		}else if(noderef[i]->nnodetype == NODE_CYLINDER){
			noderef[i]->sliceCylinder(noderef[i]);
		}else if(noderef[i]->nnodetype == NODE_SPHERE){
			noderef[i]->sliceSphere(noderef[i]);
		}else if(noderef[i]->nnodetype == NODE_INDEXEDLINESET){
			noderef[i]->point = noderef[i]->children[0]->point;
			noderef[i]->getPolyRep(noderef[i]);
		}else if(noderef[i]->nnodetype == NODE_INDEXEDFACESET){
			noderef[i]->point = noderef[i]->children[0]->point;
			noderef[i]->getPolyRep(noderef[i]);
		}	
	}	
}

int 
NODE::matmultiply(double * r, double * mm , double* nn)
{
   double tm[16],tn[16];
	double *m, *n;
	int i,j,k;
    /* prevent self-multiplication problems.*/
	m = mm;
	n = nn;
    if(r == m) {
	memcpy(tm,m,sizeof(double)*16);
	m = tm;
    }
    if(r == n) {
	memcpy(tn,n,sizeof(double)*16);
	n = tn;
    }
	/* assume 4x4 homgenous transform */
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			r[i*4+j] = 0.0;
			for(k=0;k<4;k++)
				r[i*4+j] += m[i*4+k]*n[k*4+j];
		}
	return 0;
	/* this method ignors the perspectives */
    r[0] = m[0]*n[0]+m[4]*n[1]+m[8]*n[2];
    r[4] = m[0]*n[4]+m[4]*n[5]+m[8]*n[6];
    r[8] = m[0]*n[8]+m[4]*n[9]+m[8]*n[10];
    r[12]= m[0]*n[12]+m[4]*n[13]+m[8]*n[14]+m[12];

    r[1] = m[1]*n[0]+m[5]*n[1]+m[9]*n[2];
    r[5] = m[1]*n[4]+m[5]*n[5]+m[9]*n[6];
    r[9] = m[1]*n[8]+m[5]*n[9]+m[9]*n[10];
    r[13]= m[1]*n[12]+m[5]*n[13]+m[9]*n[14]+m[13];

    r[2] = m[2]*n[0]+m[6]*n[1]+m[10]*n[2];
    r[6] = m[2]*n[4]+m[6]*n[5]+m[10]*n[6];
    r[10]= m[2]*n[8]+m[6]*n[9]+m[10]*n[10];
    r[14]= m[2]*n[12]+m[6]*n[13]+m[10]*n[14]+m[14];

    return 0;
}
