/**
 *
 * Author: Djimeli Konrad
 *
 */

#include "node.h"
#include "parser.h"
#include "transform_node.h"

using namespace std;

//Peforms transforms on transform node children
void
TRANSFORM::transformChild(NODE * pnode)
{
	PARSER parse;
	vector<NODE*> mychildlist;
	unsigned int count;
	double tempvec[3];
	double temprotvec[3];
		
	parse.getChildNodeList(pnode, mychildlist);
		
	for(count = 0; count < mychildlist.size(); count++){
		
		if(mychildlist[count]->vertics.size()){
				
			for(unsigned int i = 0; i < (mychildlist[count]->vertics.size()); i+=3 ){
				tempvec[0] = mychildlist[count]->vertics[i];
				tempvec[1] = mychildlist[count]->vertics[i+1];
				tempvec[2] = mychildlist[count]->vertics[i+2];
				
				VEC3X4MAT(temprotvec , tempvec ,pnode->rotmat);  //Mutiply vector by rotation matrix
				//Do scaling and translation
				mychildlist[count]->vertics[i] = (temprotvec[0]*pnode->scale[0])+pnode->translation[0] ;
				mychildlist[count]->vertics[i+1] = (temprotvec[1]*pnode->scale[1])+pnode->translation[1];
				mychildlist[count]->vertics[i+2] = (temprotvec[2]*pnode->scale[2])+pnode->translation[2];
			}
		}
	}
}

//Vrml rotation matrix routine
void
TRANSFORM::matrotate(double * output, double angle, double x, double y, double z)
{
	double cosxy = cos(angle);
	double sinxy = sin(angle);

	output[0] = x*x + (y*y+z*z)*cosxy;
	output[1] = x*y - x*y*cosxy + z*sinxy;
	output[2] = x*z - x*z*cosxy - y*sinxy;
	output[4] = x*y - x*y*cosxy - z*sinxy;
	output[5] = y*y + (x*x+z*z)*cosxy;
	output[6] = z*y - z*y*cosxy + x*sinxy;
	output[8] = z*x - z*x*cosxy + y*sinxy;
	output[9] = z*y - z*y*cosxy - x*sinxy;
	output[10]= z*z + (x*x+y*y)*cosxy;
	output[3] = 0;
	output[7] = 0;
	output[11] = 0;
	output[12] = 0;
	output[13] = 0;
	output[14] = 0;
	output[15] = 1;

}

void
TRANSFORM::transformSceneVert(vector<NODE*> &scenenoderef)
{
	int size = static_cast<int>(scenenoderef.size());
	int i;
	
	for(i = size - 1; i >= 0; i--){
		if(scenenoderef[i]->nnodetype == NODE_TRANSFORM){
			transformChild(scenenoderef[i]);
		}
	}
}

