/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCone.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#ifndef MyCone_Header
#define MyCone_Header
#include "Shape.H"

class MyCone : public Shape {

public:
	MyCone();
	virtual ~MyCone();
	virtual intersectRtn intersect(intersectRtn currObj);
	virtual CS123Color map(IAPoint p, double u, double v, CS123Image* textMap);

};

#endif
