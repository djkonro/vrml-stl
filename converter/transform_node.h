/**
 *
 * Author: Djimeli Konrad
 *
 */

#ifndef TRANSFORM_NODE_H
#define TRANSFORM_NODE_H


class TRANSFORM
{
	public:
	void transformChild(NODE * pnode);
	void matrotate(double * Result, double Theta, double x, double y, double z);
	void transformSceneVert(vector<NODE*> &scenenoderef);
};

#endif

