/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MySphere.H
 *    DATE: Sept 19, 2007
 *************************************************************************/

#include "MySphere.H"

MySphere::MySphere() : Shape()
{
}

MySphere::~MySphere()
{
}

intersectRtn MySphere::intersect(intersectRtn currObj)
{
	IAPoint p_tilde = currObj.oPoint;
	IAVector d_tilde = currObj.oRay;

	double t1=INFINITY, t2= INFINITY;
	// checking the body of the sphere
	double a= (d_tilde[0]*d_tilde[0]+d_tilde[1]*d_tilde[1]+d_tilde[2]*d_tilde[2]);
	double b= (2.0*p_tilde[0]*d_tilde[0]+2.0*p_tilde[1]*d_tilde[1]+2.0*p_tilde[2]*d_tilde[2]);
	double c= (p_tilde[0]*p_tilde[0]+p_tilde[1]*p_tilde[1]+p_tilde[2]*p_tilde[2]-0.25);
	double discrim= b*b-4.0*a*c;
	// if the discriminant is greater than or equal to 0 
	// we get real values and must evaluate

	// my discrim is never equal to 0 .. epsilon ?
	if (discrim >= -EPSILON) {
		t1= (-b+sqrt(b*b-4.0*a*c))/(2*a);
		t2= (-b-sqrt(b*b-4.0*a*c))/(2*a);
	}
	// if t1 is less than t1 return t2
	if (t2 <= t1 && t2 > -EPSILON)
		currObj.t = t2;
	else if (t1 > -EPSILON)
		currObj.t = t1;
	else
		currObj.t = INFINITY;


	currObj.oPoint= p_tilde+currObj.t*d_tilde;
	IAVector norm(currObj.oPoint[0], currObj.oPoint[1], currObj.oPoint[2]);
	currObj.oNorm= norm;
	
	return currObj;
}	

CS123Color MySphere::map(IAPoint p, double u, double v, CS123Image* textMap)
{
	CS123Color rtnColor;
	rtnColor.r = 0; rtnColor.b = 0; rtnColor.g = 0;
	CS123Color* data = textMap->getData();
	

	double x = p[0], y = p[1], z = p[2];
	double a, b, theta, psi;
	int s, t, w, h;

	w = textMap->getWidth();
	h = textMap->getHeight();

	// now find the x coordinate of the unit square (a)
	theta = atan2(z, x);

	a = 1.0 + ((-theta)/(2.0*M_PI));

	psi = (double)asin(y/0.5);
	b = (double)(psi/M_PI) + 0.5;

	b = 1.0 - b;

	s = ((int)(a * u * w)) % w;
	t = ((int)(b * v * h)) % h;

	rtnColor.r = (data+t*w+s)->r;
	rtnColor.b = (data+t*w+s)->b;
	rtnColor.g = (data+t*w+s)->g;

	return rtnColor;
}
