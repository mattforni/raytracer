/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MySphere.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#ifndef MySphere_Header
#define MySphere_Header
#include "Shape.H"

class MySphere : public Shape {

public:
	MySphere();
	virtual ~MySphere();
	virtual intersectRtn intersect(intersectRtn currObj);
	virtual CS123Color map(IAPoint p, double u, double v, CS123Image* textMap);
};

#endif
