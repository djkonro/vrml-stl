#ifndef nd
#define nd

#include <iostream>
#include <vector> // list class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator
#include <cstdlib>
#include <fstream>
#include <cmath>
#include "headers.h"
#include "NodeType.h"

#define PI 3.141592653589793f


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

#define FIELD_rotation 				1
#define FIELD_scaleFactor			2
#define FIELD_translation			3
#define FIELD_set_orientation		4
#define FIELD_set_position			5
#define FIELD_solid					6
#define FIELD_tessellation			7
#define FIELD_scale					8
#define FIELD_radius					9
#define FIELD_point					10
#define FIELD_normal					11
#define FIELD_color					12
#define FIELD_index					13
#define FIELD_position				14
#define FIELD_scaleOrientation	15
#define FIELD_location				16
#define FIELD_colorPerVertex		17
#define FIELD_center					18
#define FIELD_normalPerVertex		19
#define FIELD_segments				20
#define FIELD_texture				21
#define FIELD_colorIndex			22
#define FIELD_geometry				23
#define FIELD_data					24
#define FIELD_string					25
#define FIELD_children				26
#define FIELD_bottomRadius			27
#define FIELD_name					28
#define FIELD_texCoord				29
#define FIELD_texCoordIndex		30
#define FIELD_url						31
#define FIELD_coord					32
#define FIELD_shaders				33
#define FIELD_coordIndex			34
#define FIELD_orientation			35
#define FIELD_appearance			36
#define FIELD_height					37
#define FIELD_size					38	
#define FIELD_bottom					39
#define FIELD_side					40
#define FIELD_top						41

#define FIELDNAMEMAX             42



const double idmat[] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0 }; 






const char *fields[] = {
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


using namespace std;

char *getNextWord( char *nextword);
char *nextWord(char *inputstring, char * nextwd);
 
class NODE 
{
public:
	int nodetype;
	int fieldnumb;
	int nchild;
	int isprotodef;
	vector<NODE*> children;
	//NODE *parent;
	string nodetypename;
	float scale[3]; // = {1, 1, 1};
	float rotation[4]; // = {0, 0, 0, 0};
	float translation[3]; // = {0, 0, 0};
	float size[3];
	float radius;
	float bottomradius;
	float height;
	double rotmat[16];
	double transmat[16];
	double scalemat[16];
	vector<int> coordindex;
	vector<float> point;
	vector<double> vertics;
	
	

	void setNodeType(int ntype)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
		nodetype = ntype;
	}
	
	int getNodeType()
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		return nodetype;
	}
	
	NODE * createNewNode(int nodetype, NODE *node)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
	
		switch(nodetype){
		
	 			case NODE_APPEARANCE: 		
	 					node = new NODE;
	 					node->nodetypename = "Appearance"; 
	 					initTransform(node);
	 					return node;   
	 					break;
 				case NODE_BOX:
 						node = new NODE;
	 					node->nodetypename = "Box";
	 					node->size[0] = 2.0f;node->size[1] = 2.0f;node->size[2] = 2.0f;
						initTransform(node);
	 					return node;
 						break;
 				case NODE_CONE:
 						node = new NODE;
	 					node->nodetypename = "Cone";
						node->height = 2.0f;
						node->bottomradius = 1.0f;
	 					initTransform(node);
	 					return node;
 						break;
 				case NODE_COORDINATE:
						node = new NODE;
	 					node->nodetypename = "Coordinate";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_CYLINDER:
						node = new NODE;
	 					node->nodetypename = "Cylinder";
	 					node->radius = 1.0f;
	 					node->height = 2.0f;
	 					initTransform(node);
	 					return node;
						break;
				case NODE_GROUP:
						node = new NODE;
	 					node->nodetypename = "Group";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_INDEXEDFACESET:
						node = new NODE;
	 					node->nodetypename = "IndexedFaceSet";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_INDEXEDLINESET:
						node = new NODE;
	 					node->nodetypename = "IndexedLineSet";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_MATERIAL:
						node = new NODE;
	 					node->nodetypename = "Material";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_SHAPE:
						node = new NODE;
	 					node->nodetypename = "Shape";
	 					initTransform(node);
	 					return node;
						break;
				case NODE_SPHERE:
						node = new NODE;
	 					node->nodetypename = "Sphere";
	 					node->radius = 1.0f;
	 					initTransform(node);
	 					return node;
						break;
				case NODE_TRANSFORM:
						node = new NODE;
	 					node->nodetypename = "Transform";
	 					memcpy(node->rotmat,idmat,sizeof(double)*16);
	 					memcpy(node->transmat,idmat,sizeof(double)*16);
	 					memcpy(node->scalemat,idmat,sizeof(double)*16);
	 					initTransform(node);
	 					return node;
						break;
				case NODE_PROTO:
						node = new NODE;
	 					node->nodetypename = "PROTO";
	 					node->isprotodef = 0;
	 					initTransform(node);
	 					return node;
						break;
				default :
						return NULL;
						break;          
		}
	
	}
	
	
	int copyNodeData(NODE *dnode, NODE *snode, int nodetype)
	{
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		
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
						//dnode->point = snode->point;
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
	 					//cout << "this node has " << snode->radius << endl;
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
	
	int findFieldName(char *instring)
	{	
		#ifdef FUNCLINE
		cout << "Called in file " << __FILE__ << " line " << __LINE__ << " \n";
		#endif
		int i;

		for(i = 1; i < FIELDNAMEMAX ; i++){
		//cout << "string = " << instring.c_str() << " nodetypes = " << fields[i] << endl;
			if(strcmp(instring, fields[i]) == 0){
				return i;
			}
		}
	
		return 0; 
	}
	
	int getField(int fieldname, NODE * node)
	{
	
		switch(fieldname)
		{
			case FIELD_rotation:
					getSFVec4f(node->rotation);
					matrotate(rotmat , node->rotation[3],node->rotation[0], node->rotation[1], node->rotation[2]);
					break;
					
			case FIELD_scaleFactor:
					break;
					
			case FIELD_translation:
					getSFVec3f(node->translation);
					break;
					
			case FIELD_scale:
					getSFVec3f(node->scale);
					break;
					
			case FIELD_radius:
					getFloat(node->radius);
					break;
					
			case FIELD_point:
					getPoint(node->point);
					break;
					
			case FIELD_scaleOrientation:
					break;
					
			case FIELD_bottomRadius:
					getFloat(node->bottomradius);
					break;
					
			case FIELD_coord:
					break;
					
			case FIELD_coordIndex:
					getCoordIndex(node->coordindex);
					break;
					
			case FIELD_height:
					getFloat(node->height);
					break;
					
			case FIELD_size:
					getSFVec3f(node->size);
					break;
					
			case FIELD_bottom:
					break;
					
			case FIELD_side:
					break;
					
			case FIELD_top:
					break;

		
		}
	
	
	}
	
	void getSFVec3f(float *p)
	{
		int i;
		char val[10];
		char *ch;
		
		for(i = 0; i < 3; i++){
			ch = getNextWord( val );
			p[i] = atof(val);
			nextWord(ch , val);
			
			
			if(*val == '}'){
			//cout << "This box node has char ";printf("%c \n", *val);
				break;
			}
		}
	
	}
	
	void getSFVec4f(float *p)
	{
		int i;
		char val[10];
		
		for(i = 0; i < 4; i++){
			getNextWord( val );
			p[i] = atof(val);
		}
	}
	
	void getInt(int &n)
	{
		char val[10];
		
		getNextWord( val );
		n = atoi(val);
	}
	
	int getFloat(float &n)
	{
		char val[10];
		
		getNextWord( val );
		//cout << "Val has "<<val << endl;
		n = atof(val);
		//cout << "N has "<<n << endl;
	}
	
	void getCoordIndex(vector<int> &coordindex)
	{	
		int n;
		char val[20];
		
		getNextWord( val );
		
		//cout << "The next val after the coordindex is " << val << endl;
		
		while(getNextWord( val )){
			if(*val == ']'){
				break;
			}
			
			if(*val == ',' || (strcmp("-1" ,val) == 0)){
				continue;
			}
			
			n = atoi(val);
			coordindex.push_back(n);
		
		}
		
		//cout << "End of coordindex with " << val << endl;
		
	}
	
	void getPoint(vector<float> &point)
	{
		float n;
		char val[20];
		
		getNextWord( val );
		
		//cout << "The next val after the point is " << val << endl;
		
		while(getNextWord( val )){
		
			//cout << "point has " << val << endl;
			if(*val == ']'){
				break;
			}
			
			if(*val == ','){
				continue;
			}
			
			n = atof(val);
			
			point.push_back(n);
			//cout << "point has val of " << point[point.size()-1] << endl;
		
		}
		
		//cout << "End of point with " << val << endl;
		
	}
	
	void initTransform(NODE * node)
	{
		int i; 
		node->scale[0] = 1; node->scale[1] = 1; node->scale[2] = 1;
		node->rotation[0] = 0; node->rotation[1] = 0; node->rotation[2] = 0; node->rotation[3] = 0;
		node->translation[0] = 0; node->translation[1] = 0; node->translation[2] = 0;
		for(i = 0; i < 16; i++){
			node->rotmat[i];
		}
	
	}


	
void sliceCone(NODE * node)
{
	//cout << "Calling slice cone " << endl;
	#define  CONEDIV 20

	float h = (node->height)/2;
	float r = node->bottomradius;
	float angle;
	int i;
	float point[3];
	//ofstream output("../cadtest/output.stl");

	
		/* we create two triangle fans - the cone, and the bottom. */
		/* first, the flat bit on the bottom */
		int indx=0;

		
			for (i=0; i<CONEDIV; i++) {
				double angle = PI*2*i/(double)CONEDIV;
				double next_angle = PI*2*(i+1)/(double)CONEDIV;
				/* vertex #1 */
				point[0] = r* (float) sin(angle);
				node->vertics.push_back(point[0]);
				point[1] = (float) -h;
				node->vertics.push_back(point[1]);
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[2]);
		
				indx++;
	
				/* vertex #2 - in the centre */
				point[0] = 0.0f;
				node->vertics.push_back(point[0]);
				point[1] = (float) -h;
				node->vertics.push_back(point[1]);
				point[2] = 0.0f;
				node->vertics.push_back(point[2]);
			
				indx++;
	
				/* vertex #3 */
				point[0] = r* (float) sin(next_angle);
				node->vertics.push_back(point[0]);
				point[1] = (float) -h;
				node->vertics.push_back(point[1]);
				point[2] = r* (float) cos(next_angle);
				node->vertics.push_back(point[2]);
				
				indx++;
			}
	


		

			for (i=0; i<CONEDIV; i++) {
				double angle;

				/* vertex #1 */
				angle = (double) (PI * 2 * (i+1.0f)) / (double) (CONEDIV);
				point[0] = r* (float) sin(angle);
				node->vertics.push_back(point[0]);
				point[1] = (float) -h;
				node->vertics.push_back(point[1]);
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[2]);
			
				indx++;
	
				/* vertex #2 - in the centre */
				angle = (float) (PI * 2 * (i+0.5f)) / (double)(CONEDIV);
				point[0] = 0.0f;
				node->vertics.push_back(point[0]);
				point[1] = (float) h;
				node->vertics.push_back(point[1]);
				point[2] = 0.0f;
				node->vertics.push_back(point[2]);
				
				indx++;
	
				/* vertex #3 */
				angle = (float) (PI * 2 * (i+0.0f)) / (double) (CONEDIV);
				point[0] = r* (float) sin(angle);
				node->vertics.push_back(point[0]);
				point[1] = (float) -h;
				node->vertics.push_back(point[1]);
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[2]);
				
				indx++;
				
			}
			
		/*	cout << "Has " << node->vertics.size() << " points" << endl;
			
			output << "solid s0" << endl;
			output << "  facet normal 0 0 0" << endl;
			output << "    outer loop";
			//output << "      vertex ";
			
			
			for(int x = 0; x < node->vertics.size() ; x++){
				 	if(((x)%3) == 0){
				 		output << endl;
				 		output << "      vertex ";
				 	}
				 	
				 	output << node->vertics[x] << " ";
				 	
				 	if(x == (node->vertics.size()-1)){
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
		*/
			

}

void printConeSlice(NODE * node, char *fname, int scale)
{
	
	int i;
	float point[3];
	ofstream output(fname);

	
		/* we create two triangle fans - the cone, and the bottom. */
		/* first, the flat bit on the bottom */
		int indx=0;

		
		
			output << "solid s0" << endl;
			output << "  facet normal 0 0 0" << endl;
			output << "    outer loop";
			//output << "      vertex ";
			
			
			for(int x = 0; x < node->vertics.size() ; x++){
				 	if(((x)%3) == 0){
				 		output << endl;
				 		output << "      vertex ";
				 	}
				 	
				 	if(((x)%3) == 0){
				 		output << (node->vertics[x]) << " ";
				 	}else{
				 		output << (node->vertics[x]) << " ";
				 	}
				 	
				 	
				 	if(x == (node->vertics.size()-1)){
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


void matrotate(double * Result, double Theta, double x, double y, double z)
{
    double CosTheta = cos(Theta);
    double SinTheta = sin(Theta);

    Result[0] = x*x + (y*y+z*z)*CosTheta;
    Result[1] = x*y - x*y*CosTheta + z*SinTheta;
    Result[2] = x*z - x*z*CosTheta - y*SinTheta;
    Result[4] = x*y - x*y*CosTheta - z*SinTheta;
    Result[5] = y*y + (x*x+z*z)*CosTheta;
    Result[6] = z*y - z*y*CosTheta + x*SinTheta;
    Result[8] = z*x - z*x*CosTheta + y*SinTheta;
    Result[9] = z*y - z*y*CosTheta - x*SinTheta;
    Result[10]= z*z + (x*x+y*y)*CosTheta;
    Result[3] = 0;
    Result[7] = 0;
    Result[11] = 0;
    Result[12] = 0;
    Result[13] = 0;
    Result[14] = 0;
    Result[15] = 1;

}

int matmultiply(double * r, double * mm , double* nn)
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

void sliceBox(NODE *node) {
//cout << "Slicing the box " << endl;
	float x = node->size[0]/2;
	float y = node->size[1]/2;
	float z = node->size[2]/2;

	
#define PTF0 node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(z);
#define PTF1 node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(z); 
#define PTF2 node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(z); 
#define PTF3 node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(z) ;
#define PTR0 node->vertics.push_back(x); node->vertics.push_back(y); node->vertics.push_back(-z);
#define PTR1 node->vertics.push_back(-x); node->vertics.push_back(y); node->vertics.push_back(-z);
#define PTR2 node->vertics.push_back(-x); node->vertics.push_back(-y); node->vertics.push_back(-z);
#define PTR3 node->vertics.push_back(x); node->vertics.push_back(-y); node->vertics.push_back(-z);


	PTF0 PTF1 PTF2  PTF0 PTF2 PTF3 /* front */
	PTR2 PTR1 PTR0  PTR3 PTR2 PTR0 /* back  */
	PTF0 PTR0 PTR1  PTF0 PTR1 PTF1 /* top   */
	PTF3 PTF2 PTR2  PTF3 PTR2 PTR3 /* bottom */
	PTF0 PTF3 PTR3 	PTF0 PTR3 PTR0 /* right */
	PTF1 PTR1 PTR2  PTF1 PTR2 PTF2 /* left */


}
#undef PTF0
#undef PTF1
#undef PTF2
#undef PTR0
#undef PTR1
#undef PTR2

void sliceCylinder (NODE *node) {
	#define CYLDIV 20
	float h = (node->height)/2;
	float r = node->radius;
	int i = 0;
	float point[3];

		int indx = 0;

			for (i=0; i<CYLDIV; i++) {
				double angle = PI*2*i/(double)CYLDIV;
				double next_angle = PI*2*(i+1)/(double)CYLDIV;
				/* vertex #1 */
				point[0] = r* (float) sin(angle);
				point[1] = (float) -h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #2 - in the centre */
				point[0] = 0.0f;
				point[1] = (float) -h;
				point[2] = 0.0f;
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #3 */
				point[0] = r* (float) sin(next_angle);
				point[1] = (float) -h;
				point[2] = r* (float) cos(next_angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
			}
		
			/* same as bottom, but wind'em the other way */
			for (i=0; i<CYLDIV; i++) {
				double angle = PI*2*i/(double)CYLDIV;
				double next_angle = PI*2*(i+1)/(double)CYLDIV;
				/* vertex #1 */
				point[0] = r* (float) sin(next_angle);
				point[1] = (float) h;
				point[2] = r* (float) cos(next_angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #2 - in the centre */
				point[0] = 0.0f;
				point[1] = (float) h;
				point[2] = 0.0f;
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #3 */
				point[0] = r* (float) sin(angle);
				point[1] = (float) h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
			}
		
	


	
			for (i=0; i<CYLDIV; i++) {
				double angle;

				/* Triangle #1 for this segment of the side */
				/* vertex #1 - bottom right */
				angle = (double) (PI * 2 * (i+1.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) -h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #2 - top left */
				angle = (double) (PI * 2 * (i+0.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #3 - bottom left */
				angle = (double) (PI * 2 * (i+0.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) -h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;

				/* Triangle #2 for this segment of the side */
				/* vertex #1 - bottom right */
				angle = (double) (PI * 2 * (i+1.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) -h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				indx++;
	
				/* vertex #2 - top right */
				angle = (double) (PI * 2 * (i+1.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
			
				indx++;
	
				/* vertex #3 - top left */
				angle = (float) (PI * 2 * (i+0.0f)) / (double) (CYLDIV);
				point[0] = r* (float) sin(angle);
				point[1] = (float) h;
				point[2] = r* (float) cos(angle);
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
			
				indx++;
			}
   
}

void sliceSphere (NODE *node) {
	#define SPHDIV 20
	
	#define INIT_TRIG1(div) t_aa = (float) sin(PI/(div)); t_aa *= 2*t_aa; t_ab =(float) -sin(2*PI/(div));
	#define START_TRIG1 t_sa = 0; t_ca = -1;
	#define UP_TRIG1 t_sa1 = t_sa; t_sa -= t_sa*t_aa - t_ca * t_ab; t_ca -= t_ca * t_aa + t_sa1 * t_ab;
	#define SIN1 t_sa
	#define COS1 t_ca
	#define INIT_TRIG2(div) t2_aa = (float) sin(PI/(div)); t2_aa *= 2*t2_aa; t2_ab = (float) -sin(2*PI/(div));
	#define START_TRIG2 t2_sa = -1; t2_ca = 0;
	#define UP_TRIG2 t2_sa1 = t2_sa; t2_sa -= t2_sa*t2_aa - t2_ca * t2_ab; t2_ca -= t2_ca * t2_aa + t2_sa1 * t2_ab;
	#define SIN2 t2_sa
	#define COS2 t2_ca
	
	int count;
	float rad = node->radius;

	int v; int h;
	float point[3];
	
	count = 0;
	
	
	INIT_TRIG1(SPHDIV)
	INIT_TRIG2(SPHDIV)

	START_TRIG1

		for(v=0; v<SPHDIV; v++) {
			float vsin1 = SIN1;
			float vcos1 = COS1, vsin2,vcos2;
			UP_TRIG1
			vsin2 = SIN1;
			vcos2 = COS1;
			START_TRIG2
			for(h=0; h<=SPHDIV; h++) {
				float hsin1 = SIN2;
				float hcos1 = COS2;
				UP_TRIG2
				point[0] = rad * vsin2 * hcos1;
				point[1] = rad * vcos2;
				point[2] = rad * vsin2 * hsin1;
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				count++;
				
				point[0] = rad * vsin1 * hcos1;
				point[1] = rad * vcos1;
				point[2] = rad * vsin1 * hsin1;
				node->vertics.push_back(point[0]);
				node->vertics.push_back(point[1]);
				node->vertics.push_back(point[2]);
				count++;
			}
		}	
}


void getPolyRep(NODE *node) {
	
	int i;

	for(i = 0; i < node->coordindex.size(); i++){
	
		node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3]);
		node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3+1]);
		node->vertics.push_back(node->children[0]->point[node->coordindex[i]*3+2]);
		
		//cout << "Faceset is pushing " << node->children[0]->point[node->coordindex[i]*3]<<" " << node->children[0]->point[node->coordindex[i]*3+1]<<" " <<node->children[0]->point[node->coordindex[i]*3+2] << endl;
		//cout << "Points are " << node->coordindex[i]*3<<" " <<node->coordindex[i]*3+1<<" " <<node->coordindex[i]*3+2<< endl;
		//cout << "i = " << i << " indexsize " << node->coordindex.size()<< endl;
	}
}


	
};

#endif
