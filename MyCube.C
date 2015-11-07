/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCube.C
 *    DATE: Sept 19, 2007
 *************************************************************************/

#include "MyCube.H"

MyCube::MyCube() : Shape()
{
}

MyCube::~MyCube()
{
}

intersectRtn MyCube::intersect(intersectRtn currObj)
{
	IAPoint p_tilde = currObj.oPoint;
	IAVector d_tilde = currObj.oRay;
	currObj.t = INFINITY;

	double t1=INFINITY, t2= INFINITY;
	IAPoint ppv1, ppv2;

	// checking the right side
	t1= (0.5-p_tilde[0])/d_tilde[0];
	ppv1= p_tilde+t1*d_tilde;
	// if y or z are less than -0.5 or greater than 0.5 through out t1
	if (ppv1[1] < -0.5 || ppv1[1] > 0.5 || ppv1[2] < -0.5 || ppv1[2] > 0.5)
		t1 = INFINITY;

	// checking the left side
	t2= (-0.5-p_tilde[0])/d_tilde[0];
	ppv2= p_tilde+t2*d_tilde;
	// if y or z are less than -0.5 or greater than 0.5 through out t1
	if (ppv2[1] < -0.5 || ppv2[1] > 0.5 || ppv2[2] < -0.5 || ppv2[2] > 0.5)
		t2 = INFINITY;

	if (t2 <= t1 && t2 > 0) {
		t1 = t2;
		IAVector leftNorm(-1, 0, 0);
		currObj.oNorm = leftNorm; 
	}
	else if (t1 > 0) {
		IAVector rightNorm(1, 0, 0);
		currObj.oNorm = rightNorm;
	}
		
	// checking the top
	t2= (0.5-p_tilde[1])/d_tilde[1];
	ppv2= p_tilde+t2*d_tilde;
	// if x or z are less than -0.5 or greater than 0.5 through out t1
	if (ppv2[0] < -0.5 || ppv2[0] > 0.5 || ppv2[2] < -0.5 || ppv2[2] > 0.5)
		t2 = INFINITY;	

	if (t2 <= t1 && t2 > 0) {
		t1 = t2;
		IAVector topNorm(0, 1, 0);
		currObj.oNorm = topNorm; 
	}

	// checking the bottom
	t2= (-0.5-p_tilde[1])/d_tilde[1];
	ppv2= p_tilde+t2*d_tilde;
	// if x or z are less than -0.5 or greater than 0.5 through out t1
	if (ppv2[0] < -0.5 || ppv2[0] > 0.5 || ppv2[2] < -0.5 || ppv2[2] > 0.5)
		t2 = INFINITY;	

	if (t2 <= t1 && t2 > 0) {
		t1 = t2;
		IAVector botNorm(0, -1, 0);
		currObj.oNorm = botNorm; 
	}

	// checking the front
	t2= (0.5-p_tilde[2])/d_tilde[2];
	ppv2= p_tilde+t2*d_tilde;
	// if x or y are less than -0.5 or greater than 0.5 through out t1
	if (ppv2[0] < -0.5 || ppv2[0] > 0.5 || ppv2[1] < -0.5 || ppv2[1] > 0.5)
		t2 = INFINITY;	

	if (t2 <= t1 && t2 > 0) {
		t1 = t2;
		IAVector frontNorm(0, 0, 1);
		currObj.oNorm = frontNorm; 
	}

	// checking the back
	t2= (-0.5-p_tilde[2])/d_tilde[2];
	ppv2= p_tilde+t2*d_tilde;
	// if x or y are less than -0.5 or greater than 0.5 through out t1
	if (ppv2[0] < -0.5 || ppv2[0] > 0.5 || ppv2[1] < -0.5 || ppv2[1] > 0.5)
		t2 = INFINITY;	

	if (t2 <= t1 && t2 > 0) {
		currObj.t = t2;
		IAVector backNorm(0, 0, -1);
		currObj.oNorm = backNorm; 
	}
	else 
		currObj.t = t1;

	currObj.oPoint= p_tilde+currObj.t*d_tilde;

	return currObj;
}

CS123Color MyCube::map(IAPoint p, double u, double v, CS123Image* textMap)
{
	CS123Color rtnColor;
	CS123Color* data = textMap->getData();

	double x = p[0], y = p[1], z = p[2];
	double a, b;
	int s, t, w, h;

	w = textMap->getWidth();
	h = textMap->getHeight();	

	// left side
	if (x > -0.5-EPSILON && x < -0.5+EPSILON) 
	{
		a = z + 0.5;
		b = y + 0.5;
	}

	// the right side -- weird math cause z is backwards
	if (x > 0.5-EPSILON && x < 0.5+EPSILON) 
	{
		a = 1.0 - (z + 0.5);
		b = y + 0.5;
	}

	// the front side
	if (z > 0.5-EPSILON && z < 0.5+EPSILON)
	{
		a = x + 0.5;
		b = y + 0.5;
	}

	// the back side
	if (z > -0.5-EPSILON && z < -0.5+EPSILON)
	{
		a = 1.0 - (x + 0.5);
		b = y + 0.5;
	}

	// the top
	if (y > 0.5-EPSILON && y < 0.5+EPSILON)
	{
		a = x + 0.5;
		b = 1.0 - (z + 0.5);
	}

	// the bottom
	if (y > -0.5-EPSILON && y < -0.5+EPSILON)
	{
		a = x + 0.5;
		b = z + 0.5;
	}
	
	b = 1.0 - b;

	s = ((int)(a * u * w)) % w;
	t = ((int)(b * v * h)) % h;

	rtnColor.r = (data+t*w+s)->r;
	rtnColor.b = (data+t*w+s)->b;
	rtnColor.g = (data+t*w+s)->g;

	return rtnColor;
}
