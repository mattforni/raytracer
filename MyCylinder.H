/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCylinder.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#ifndef MyCylinder_Header
#define MyCylinder_Header
#include "Shape.H"

class MyCylinder : public Shape {

public:
	MyCylinder();
	virtual ~MyCylinder();
	virtual intersectRtn intersect(intersectRtn currObj);
	virtual CS123Color map(IAPoint p, double u, double v, CS123Image* textMap);
};

#endif
