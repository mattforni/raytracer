/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCube.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#ifndef MyCube_Header
#define MyCube_Header
#include "Shape.H"

class MyCube : public Shape {

public:
	MyCube();
	virtual ~MyCube();
	virtual intersectRtn intersect(intersectRtn currObj);
	virtual CS123Color map(IAPoint p, double u, double v, CS123Image* textMap);
};

#endif
