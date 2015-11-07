/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: Shape.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#ifndef __SHAPE_H_
#define __SHAPE_H_

#include <IAlgebra.inl>
#include <MyRayCanvas.H>

class Shape {

  public: 
	Shape();
	virtual ~Shape();
	virtual intersectRtn intersect(intersectRtn currObj)=0;
	virtual CS123Color map(IAPoint p, double u, double v, CS123Image* textMap)=0;
};

#endif
