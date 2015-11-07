/**
 *
 * Author: Djimeli Konrad
 *
 */

#include <cmath>

#include "node.h"
#include "parser.h"
#include "transform_node.h"

using namespace std;

//Peforms transforms on transform node children
void
TRANSFORM::transformChild(NODE * pnode)
{
	vector<NODE*> mychildlist;
	int count;
	double temprotmat[16] ;//= {1,2,3,4};
	PARSER par;
	vector<double> tempvec;
	
	par.getChildNodeList(pnode, mychildlist);
	
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

