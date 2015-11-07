/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCone.C
 *    DATE: Sept 19, 2007
 *************************************************************************/

#include "MyCone.H"
#include "math.h"

MyCone::MyCone() : Shape()
{
}

MyCone::~MyCone()
{
}

intersectRtn MyCone::intersect(intersectRtn currObj)
{
	IAPoint p_tilde = currObj.oPoint;
	IAVector d_tilde = currObj.oRay;

	double t1=INFINITY, t2= INFINITY;
	IAPoint ppv1, ppv2;
	// checking the body of the cone
	double a= (d_tilde[0]*d_tilde[0]+d_tilde[2]*d_tilde[2]-0.25*d_tilde[1]*d_tilde[1]);
	double b= (2*p_tilde[0]*d_tilde[0]+2*p_tilde[2]*d_tilde[2]-0.5*p_tilde[1]*d_tilde[1]+0.25*d_tilde[1]);
	double c= (p_tilde[0]*p_tilde[0]+p_tilde[2]*p_tilde[2]-0.25*p_tilde[1]*p_tilde[1]+0.25*p_tilde[1]-0.0625);
	// if the discriminant is greater than or equal to 0 
	// we get real values and must evaluate
	double discrim= b*b-4.0*a*c;
	if (discrim >= 0) {	
		// there is either one root or two roots
		t1= (-b+sqrt(b*b-4.0*a*c))/(2.0*a);
		t2= (-b-sqrt(b*b-4.0*a*c))/(2.0*a);
		ppv1= p_tilde+t1*d_tilde;
		ppv2= p_tilde+t2*d_tilde;
		// if the yValues are less than -0.5 or greater than 0.5
		// throw them out, they are not valid
		if (ppv1[1]<-0.5 || ppv1[1]>0.5)
			t1= INFINITY;
		if (ppv2[1]<-0.5 || ppv2[1]>0.5)
			t2= INFINITY;

		// if t2 <= t1 & >= 0 then set t1 equal to t2
		if (t2 <= t1 && t2 >= 0)
			t1= t2;
	}
	// checking the bottom
	t2= (-0.5-p_tilde[1])/d_tilde[1];
	ppv2= p_tilde+t2*d_tilde;
	if (ppv2[0]*ppv2[0]+ppv2[2]*ppv2[2] > 0.25)
		t2= INFINITY;

	if (t2 <= t1 && t2 > 0)
		currObj.t= t2;
	else if (t1 > 0)
		currObj.t= t1;
	else
		currObj.t = INFINITY;

	// calculating the normal
	if (currObj.t < INFINITY) {
		currObj.oPoint= p_tilde+currObj.t*d_tilde;

		if (currObj.oPoint[1] <= 0.5+EPSILON &&  currObj.oPoint[1] >= 0.5-EPSILON) {
			IAVector topNorm(0, 1, 0);
			currObj.oNorm = topNorm;
		}
		else if (currObj.oPoint[1] <= -0.5+EPSILON &&  currObj.oPoint[1] >= -0.5-EPSILON) {
			IAVector botNorm(0, -1, 0);
			currObj.oNorm = botNorm;
		}
		else {
			IAVector norm(2.0*currObj.oPoint[0], (-(currObj.oPoint[1]/2.0) + 0.25), 2.0*currObj.oPoint[2]);
		currObj.oNorm = norm;
		}
	}

	return currObj;
}

CS123Color MyCone::map(IAPoint p, double u, double v, CS123Image* textMap)
{
	CS123Color rtnColor;
	rtnColor.r = 0; rtnColor.b = 0; rtnColor.g = 0;
	CS123Color* data = textMap->getData();

	double x = p[0], y = p[1], z = p[2];
	double a, b, theta;
	int s, t, w, h;

	w = textMap->getWidth();
	h = textMap->getHeight();
	
	if (y > -0.5-EPSILON && y < -0.5+EPSILON)
	{
		a = x + 0.5;
		b = 1.0 - (z + 0.5);
	}
	
	else {
		// first find the y coordinate of the unit square (b)
		b = 1.0 - (y + 0.5);

		// now find the x coordinate of the unit square (a)
		theta = atan2(z, x);

		a = 1.0 + ((-theta)/(2.0*M_PI));
	}

	s = ((int)(a * u * w)) % w;
	t = ((int)(b * v * h)) % h;

	rtnColor.r = (data+t*w+s)->r;
	rtnColor.b = (data+t*w+s)->b;
	rtnColor.g = (data+t*w+s)->g;

	return rtnColor;
}
