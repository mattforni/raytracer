#ifndef IALGEBRA_INL
#define IALGEBRA_INL

// *** DO NOT CHANGE THIS INCLUDE ***
#include <IAlgebra.H>
#include <math.h>

////////////////////////////////////////////////////////////////////
//              SECTION ONE: IAPoint
//
//              (definitions for IAPoint methods)
////////////////////////////////////////////////////////////////////

inline bool IAPoint::operator==(const IAPoint& p) const
{
    for(int i=0; i<4; i++) {
	if(fabs(m_d[i]-p.m_d[i])>EPSILON)
		return false;
	}
	return true;
}

inline bool IAPoint::operator!=(const IAPoint& p) const
{
    return !(*this==p);
}

inline void IAPoint::homogenize()
{
    if(m_d[3]==0.0)
	printf("Unfortunately the w component is equal to 0.\nCannot homogenize!\n\n");
    else {
    	for(int i=0; i<4; i++)
		m_d[i]/=m_d[3];
    }
}

////////////////////////////////////////////////////////////////////
//              SECTION TWO: IAVector
//
//              (definitions for IAVector methods)
////////////////////////////////////////////////////////////////////

inline bool IAVector::operator==(const IAVector& v) const
{
    for(int i=0; i<4; i++) {
	if(fabs(m_d[i]-v.m_d[i])>EPSILON)
		return false;
	}
	return true;
}

inline bool IAVector::operator!=(const IAVector& v) const
{
    return !(*this==v);
}

inline void IAVector::normalize()
{
    double denom=sqrt(m_d[0]*m_d[0]+m_d[1]*m_d[1]+m_d[2]*m_d[2]+m_d[3]*m_d[3]);
    // if(denom==0.0)
	// printf("Unfortunately the length is equal to 0.\nCannot normalize!\n\n");
    // else {
    	m_d[0]/=denom;
    	m_d[1]/=denom;
    	m_d[2]/=denom;
    	m_d[3]/=denom;
   // }
}

////////////////////////////////////////////////////////////////////
//              SECTION THREE: IAMatrix
//
//              (definitions for IAMatrix methods)
////////////////////////////////////////////////////////////////////

inline bool IAMatrix::operator==(const IAMatrix& m) const
{
    for(int i=0; i<16; i++) {
	if(fabs(m_d[i]-m.m_d[i])>EPSILON)
		return false;
	}
	return true;
}

inline bool IAMatrix::operator!=(const IAMatrix& m) const
{
    return !(*this==m);
}

////////////////////////////////////////////////////////////////////
//              SECTION FOUR: Global Operators
//
//              (definitions for global operator overloads)
////////////////////////////////////////////////////////////////////

// This adds a vector to a point, and returns the resultant point

inline IAPoint operator+(const IAVector& v, const IAPoint& p) {
    return IAPoint(p.m_d[0]+v.m_d[0], p.m_d[1]+v.m_d[1], p.m_d[2]+v.m_d[2], p.m_d[3]+v.m_d[3]);
};

// This does the same.

inline IAPoint operator+(const IAPoint& p, const IAVector& v) {
    return IAPoint(p.m_d[0]+v.m_d[0], p.m_d[1]+v.m_d[1], p.m_d[2]+v.m_d[2], p.m_d[3]+v.m_d[3]);
};

// This adds two vectors, and returns the resultant one

inline IAVector operator+(const IAVector& v1, const IAVector& v2) {
    return IAVector(v1.m_d[0]+v2.m_d[0], v1.m_d[1]+v2.m_d[1], v1.m_d[2]+v2.m_d[2]); 
};

// Note: no (point + point) operator



// This subtracts a vector from a point, and returns the resultant point.

inline IAPoint operator-(const IAPoint& p, const IAVector& v) {
    return IAPoint(p.m_d[0]-v.m_d[0], p.m_d[1]-v.m_d[1], p.m_d[2]-v.m_d[2], p.m_d[3]-v.m_d[3]);
};

// This returns the negated vector

inline IAVector operator-(const IAVector& v) {
    return IAVector(-v.m_d[0], -v.m_d[1], -v.m_d[2]);
};

// This subtracts the second vector from the first, and returns the resultant.

inline IAVector operator-(const IAVector& v1, const IAVector& v2) {
    return IAVector(v1.m_d[0]-v2.m_d[0], v1.m_d[1]-v2.m_d[1], v1.m_d[2]-v2.m_d[2]);
};

//The vector spanning p1 and p2--make sure you know what direction it goes
inline IAVector operator-(const IAPoint& p1, const IAPoint& p2) {
    return IAVector(p1.m_d[0]-p2.m_d[0], p1.m_d[1]-p2.m_d[1], p1.m_d[2]-p2.m_d[2]);
};

// Note: no (vector - point) or (- point) operators




// --- Scalars

// This divides a vector by a scalar

inline IAVector operator/(const IAVector& v, const double s) {
   if(s==0.0) {
	printf("Unfortunately the scaling factor is equal to 0.\nCannot divide!\nReturning the original vector.\n\n");
	return v;
   }
   else
   	return IAVector((double)v.m_d[0]/s, (double)v.m_d[1]/s, (double)v.m_d[2]/s);
};

// This should multiply the vector by the scalar, returning a vector

inline IAVector operator*(const double s, const IAVector &v) {
   return IAVector((double)v.m_d[0]*s, (double)v.m_d[1]*s, (double)v.m_d[2]*s);
};

// This does the same.

inline IAVector operator*(const IAVector& v, const double s) {
   return IAVector((double)v.m_d[0]*s, (double)v.m_d[1]*s, (double)v.m_d[2]*s);
};



// --- Matrix Operator

// Applies the matrix to a point, returns the new point

inline IAPoint operator*(const IAMatrix& m, const IAPoint& p) {
   IAPoint point = IAPoint((double)m.m_d[0]*p.m_d[0] +(double)m.m_d[4]*p.m_d[1] +(double)m.m_d[8]*p.m_d[2] +(double)m.m_d[12]*p.m_d[3],
		  (double)m.m_d[1]*p.m_d[0] +(double)m.m_d[5]*p.m_d[1] +(double)m.m_d[9]*p.m_d[2] +(double)m.m_d[13]*p.m_d[3],
		  (double)m.m_d[2]*p.m_d[0] +(double)m.m_d[6]*p.m_d[1] +(double)m.m_d[10]*p.m_d[2]+(double)m.m_d[14]*p.m_d[3],
		  (double)m.m_d[3]*p.m_d[0] +(double)m.m_d[7]*p.m_d[1] +(double)m.m_d[11]*p.m_d[2]+(double)m.m_d[15]*p.m_d[3]);
	point.homogenize();
	return point;
};

// Applies the matrix to the vector, returns the new vector.

inline IAVector operator*(const IAMatrix& m, const IAVector& v) {
  return IAVector((double)m.m_d[0]*v.m_d[0]+(double)m.m_d[4]*v.m_d[1]+(double)m.m_d[8]*v.m_d[2]+(double)m.m_d[12]*v.m_d[3],
		  (double)m.m_d[1]*v.m_d[0]+(double)m.m_d[5]*v.m_d[1]+(double)m.m_d[9]*v.m_d[2]+(double)m.m_d[13]*v.m_d[3],
		  (double)m.m_d[2]*v.m_d[0]+(double)m.m_d[6]*v.m_d[1]+(double)m.m_d[10]*v.m_d[2]+(double)m.m_d[14]*v.m_d[3]);
};

// Multiplies two matrices together, returns the resultant matrix
inline IAMatrix operator*(const IAMatrix& m1, const IAMatrix& m2) {
    return IAMatrix((double)m2.m_d[0]*m1.m_d[0]+(double)m2.m_d[1]*m1.m_d[4]+(double)m2.m_d[2]*m1.m_d[8]+(double)m2.m_d[3]*m1.m_d[12],
		    (double)m2.m_d[4]*m1.m_d[0]+(double)m2.m_d[5]*m1.m_d[4]+(double)m2.m_d[6]*m1.m_d[8]+(double)m2.m_d[7]*m1.m_d[12],
		    (double)m2.m_d[8]*m1.m_d[0]+(double)m2.m_d[9]*m1.m_d[4]+(double)m2.m_d[10]*m1.m_d[8]+(double)m2.m_d[11]*m1.m_d[12],
		    (double)m2.m_d[12]*m1.m_d[0]+(double)m2.m_d[13]*m1.m_d[4]+(double)m2.m_d[14]*m1.m_d[8]+(double)m2.m_d[15]*m1.m_d[12],
		    (double)m2.m_d[0]*m1.m_d[1]+(double)m2.m_d[1]*m1.m_d[5]+(double)m2.m_d[2]*m1.m_d[9]+(double)m2.m_d[3]*m1.m_d[13],
		    (double)m2.m_d[4]*m1.m_d[1]+(double)m2.m_d[5]*m1.m_d[5]+(double)m2.m_d[6]*m1.m_d[9]+(double)m2.m_d[7]*m1.m_d[13],
		    (double)m2.m_d[8]*m1.m_d[1]+(double)m2.m_d[9]*m1.m_d[5]+(double)m2.m_d[10]*m1.m_d[9]+(double)m2.m_d[11]*m1.m_d[13],
		    (double)m2.m_d[12]*m1.m_d[1]+(double)m2.m_d[13]*m1.m_d[5]+(double)m2.m_d[14]*m1.m_d[9]+(double)m2.m_d[15]*m1.m_d[13],
		    (double)m2.m_d[0]*m1.m_d[2]+(double)m2.m_d[1]*m1.m_d[6]+(double)m2.m_d[2]*m1.m_d[10]+(double)m2.m_d[3]*m1.m_d[14],
		    (double)m2.m_d[4]*m1.m_d[2]+(double)m2.m_d[5]*m1.m_d[6]+(double)m2.m_d[6]*m1.m_d[10]+(double)m2.m_d[7]*m1.m_d[14],
		    (double)m2.m_d[8]*m1.m_d[2]+(double)m2.m_d[9]*m1.m_d[6]+(double)m2.m_d[10]*m1.m_d[10]+(double)m2.m_d[11]*m1.m_d[14],
		    (double)m2.m_d[12]*m1.m_d[2]+(double)m2.m_d[13]*m1.m_d[6]+(double)m2.m_d[14]*m1.m_d[10]+(double)m2.m_d[15]*m1.m_d[14],
		    (double)m2.m_d[0]*m1.m_d[3]+(double)m2.m_d[1]*m1.m_d[7]+(double)m2.m_d[2]*m1.m_d[11]+(double)m2.m_d[3]*m1.m_d[15],
		    (double)m2.m_d[4]*m1.m_d[3]+(double)m2.m_d[5]*m1.m_d[7]+(double)m2.m_d[6]*m1.m_d[11]+(double)m2.m_d[7]*m1.m_d[15],
		    (double)m2.m_d[8]*m1.m_d[3]+(double)m2.m_d[9]*m1.m_d[7]+(double)m2.m_d[10]*m1.m_d[11]+(double)m2.m_d[11]*m1.m_d[15],
		    (double)m2.m_d[12]*m1.m_d[3]+(double)m2.m_d[13]*m1.m_d[7]+(double)m2.m_d[14]*m1.m_d[11]+(double)m2.m_d[15]*m1.m_d[15]);
};



////////////////////////////////////////////////////////////////////
//              SECTION FIVE: Global Functions
//
//              (definitions for global functions on IA objects)
////////////////////////////////////////////////////////////////////

// --- Vector dot and cross products

// Returns the dot product of the two vectors.

inline double dot(const IAVector& u, const IAVector& v) {
    return (double)u.m_d[0]*v.m_d[0]+(double)u.m_d[1]*v.m_d[1]+(double)u.m_d[2]*v.m_d[2];
};

// Returns the cross product of the two vectors.

inline IAVector cross(const IAVector& u, const IAVector& v) {
    return IAVector((double)u.m_d[1]*v.m_d[2]-(double)u.m_d[2]*v.m_d[1], (double)u.m_d[2]*v.m_d[0]-(double)u.m_d[0]*v.m_d[2], (double)u.m_d[0]*v.m_d[1]-(double)u.m_d[1]*v.m_d[0]);
};


// --- Length of a vector

// returns the length of the vector

inline double length(const IAVector& v) {
    return sqrt((double)v.m_d[0]*v.m_d[0]+(double)v.m_d[1]*v.m_d[1]+(double)v.m_d[2]*v.m_d[2]);
};


inline IAMatrix transpose(const IAMatrix& m) {
    return IAMatrix(	m.m_d[0], m.m_d[1], m.m_d[2], m.m_d[3], 
			m.m_d[4], m.m_d[5], m.m_d[6], m.m_d[7], 
			m.m_d[8], m.m_d[9], m.m_d[10], m.m_d[11], 
			m.m_d[12], m.m_d[13], m.m_d[14], m.m_d[15]);
};

// returns a scaling transformation matrix, which will scale by the vector v

inline IAMatrix scale_mat(const IAVector& v) {
    return IAMatrix(	v.m_d[0], 0.0, 0.0, 0.0, 
			0.0, v.m_d[1], 0.0, 0.0,
			0.0, 0.0, v.m_d[2], 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns a translaion matrix, which will translate by the vector v 

inline IAMatrix trans_mat(const IAVector& v) {
    return IAMatrix(	1.0, 0.0, 0.0, v.m_d[0], 
			0.0, 1.0, 0.0, v.m_d[1],
			0.0, 0.0, 1.0, v.m_d[2],
			0.0, 0.0, 0.0, 1.0);
};

// returns a rotation matrix effecting a rotation around the X axis by 
// specified radians

inline IAMatrix rotX_mat(const double radians) {
    return IAMatrix(	1.0, 0.0, 0.0, 0.0,
			0.0, cos(radians), -sin(radians), 0.0,
			0.0, sin(radians), cos(radians), 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns a rotation matrix effecting rotation around the Y axis by
// specified radians

inline IAMatrix rotY_mat(const double radians) {
    return IAMatrix(	cos(radians), 0.0, sin(radians), 0.0,
			0.0, 1.0, 0.0, 0.0,
			-sin(radians), 0.0, cos(radians), 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns a rotation matrix effecting rotation around the Z axis by
// specified radians
inline IAMatrix rotZ_mat(const double radians) {
    return IAMatrix(	cos(radians), -sin(radians), 0.0, 0.0,
			sin(radians), cos(radians), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns a rotation matrix effecting a rotation around the given vector and
// point, by the specified number of radians.
inline IAMatrix rot_mat(const IAPoint  &p, const IAVector &v, const double radians){
    
   double yAngle=atan2(v.m_d[2], v.m_d[0]);
   double zAngle=-atan2(v.m_d[1], sqrt(v.m_d[0]*v.m_d[0]+v.m_d[2]*v.m_d[2]));

   IAMatrix rot_mat =	trans_mat(IAVector(p.m_d[0], p.m_d[1], p.m_d[2]))*
			inv_rotY_mat(yAngle)*
			inv_rotZ_mat(zAngle)*
			rotX_mat(radians)*
			rotZ_mat(zAngle)*
			rotY_mat(yAngle)*
			inv_trans_mat(IAVector(p.m_d[0], p.m_d[1], p.m_d[2]));

   return rot_mat;
};  

// Returns the inverse matrix of scale_mat()

inline IAMatrix inv_scale_mat(const IAVector &v) {
    return IAMatrix(	1.0/v.m_d[0], 0.0, 0.0, 0.0,
			0.0, 1.0/v.m_d[1], 0.0, 0.0,
			0.0, 0.0, 1.0/v.m_d[2], 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns the inverse matrix of trans_mat()
inline IAMatrix inv_trans_mat(const IAVector &v) {
    return IAMatrix(	1.0, 0.0, 0.0, -v.m_d[0], 
			0.0, 1.0, 0.0, -v.m_d[1],
			0.0, 0.0, 1.0, -v.m_d[2],
			0.0, 0.0, 0.0, 1.0);
};

// Returns the inverse matrix of rotX_mat()

inline IAMatrix inv_rotX_mat(const double radians) {
    return IAMatrix(	1.0, 0.0, 0.0, 0.0,
			0.0, cos(radians), sin(radians), 0.0,
			0.0, -sin(radians), cos(radians), 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns the inverse matrix of rotY_mat()

inline IAMatrix inv_rotY_mat(const double radians) {
    return IAMatrix(	cos(radians), 0.0, -sin(radians), 0.0,
			0.0, 1.0, 0.0, 0.0,
			sin(radians), 0.0, cos(radians), 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns the inverse matrix of rotZ_mat()
inline IAMatrix inv_rotZ_mat(const double radians) {
    return IAMatrix(	cos(radians), sin(radians), 0.0, 0.0,
			-sin(radians), cos(radians), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
};

// Returns the inverse matrix of rot_mat()
inline IAMatrix inv_rot_mat(const IAPoint &p, const IAVector &v, const double radians) {

    double yAngle=atan2(v.m_d[2], v.m_d[0]);
    double zAngle=-atan2(v.m_d[1], sqrt(v.m_d[0]*v.m_d[0]+v.m_d[2]*v.m_d[2]));

    IAMatrix inv_rot_mat =	trans_mat(IAVector(p.m_d[0], p.m_d[1], p.m_d[2]))*
				inv_rotY_mat(yAngle)*
				inv_rotZ_mat(zAngle)*
				inv_rotX_mat(radians)*
				rotZ_mat(zAngle)*
				rotY_mat(yAngle)*
				inv_trans_mat(IAVector(p.m_d[0], p.m_d[1], p.m_d[2]));
				
				

    return inv_rot_mat;
};

inline IAMatrix invert(const IAMatrix& m) {
    
    double det= (      -m.m_d[0]*m.m_d[5]*m.m_d[10]*m.m_d[15]  + m.m_d[0]*m.m_d[5]*m.m_d[14]*m.m_d[11] +
			m.m_d[0]*m.m_d[6]*m.m_d[9]*m.m_d[15]   - m.m_d[0]*m.m_d[6]*m.m_d[13]*m.m_d[11] - 
			m.m_d[0]*m.m_d[7]*m.m_d[9]*m.m_d[14]   + m.m_d[0]*m.m_d[7]*m.m_d[13]*m.m_d[10] + 
			m.m_d[1]*m.m_d[4]*m.m_d[10]*m.m_d[15]  - m.m_d[1]*m.m_d[4]*m.m_d[14]*m.m_d[11] - 
			m.m_d[1]*m.m_d[6]*m.m_d[8]*m.m_d[15]   + m.m_d[1]*m.m_d[6]*m.m_d[12]*m.m_d[11] + 
			m.m_d[1]*m.m_d[7]*m.m_d[8]*m.m_d[14]   - m.m_d[1]*m.m_d[7]*m.m_d[12]*m.m_d[10] - 
			m.m_d[2]*m.m_d[4]*m.m_d[9]*m.m_d[15]   + m.m_d[2]*m.m_d[4]*m.m_d[13]*m.m_d[11] + 
			m.m_d[2]*m.m_d[5]*m.m_d[8]*m.m_d[15]   - m.m_d[2]*m.m_d[5]*m.m_d[12]*m.m_d[11] - 
			m.m_d[2]*m.m_d[7]*m.m_d[8]*m.m_d[13]   + m.m_d[2]*m.m_d[7]*m.m_d[12]*m.m_d[9]  + 
			m.m_d[3]*m.m_d[4]*m.m_d[9]*m.m_d[14]   - m.m_d[3]*m.m_d[4]*m.m_d[13]*m.m_d[10] - 
			m.m_d[3]*m.m_d[5]*m.m_d[8]*m.m_d[14]   + m.m_d[3]*m.m_d[5]*m.m_d[12]*m.m_d[10] + 
			m.m_d[3]*m.m_d[6]*m.m_d[8]*m.m_d[13]   - m.m_d[3]*m.m_d[6]*m.m_d[12]*m.m_d[9]  );  

	/** used for MAPLE **
	A := array( 	[[m.m_d0,m.m_d4,m.m_d8,m.m_d12],
			 [m.m_d1,m.m_d5,m.m_d9,m.m_d13],
			 [m.m_d2,m.m_d6,m.m_d10,m.m_d14],
			 [m.m_d3,m.m_d7,m.m_d11,m.m_d15]] );
	**/

    if(det==0.0) {
	printf("Matrix is univertable.\nReturning the Identity Matrix\n\n");
	return IAMatrix(1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
    }   
	double m00 =   -(m.m_d[5]*m.m_d[10]*m.m_d[15] - m.m_d[5]*m.m_d[14]*m.m_d[11]  - 
			m.m_d[6]*m.m_d[9]*m.m_d[15]  + m.m_d[6]*m.m_d[13]*m.m_d[11]  + 
			m.m_d[7]*m.m_d[9]*m.m_d[14]  - m.m_d[7]*m.m_d[13]*m.m_d[10] );

	double m01 =    (m.m_d[4]*m.m_d[10]*m.m_d[15]  - m.m_d[4]*m.m_d[14]*m.m_d[11] - 
			m.m_d[6]*m.m_d[8]*m.m_d[15]  + m.m_d[6]*m.m_d[12]*m.m_d[11]  + 
			m.m_d[7]*m.m_d[8]*m.m_d[14]  - m.m_d[7]*m.m_d[12]*m.m_d[10] );

	double m02 =   -(m.m_d[4]*m.m_d[9]*m.m_d[15]  - m.m_d[4]*m.m_d[13]*m.m_d[11]  - 
			m.m_d[5]*m.m_d[8]*m.m_d[15]  + m.m_d[5]*m.m_d[12]*m.m_d[11]  + 
			m.m_d[7]*m.m_d[8]*m.m_d[13]  - m.m_d[7]*m.m_d[12]*m.m_d[9]  );

	double m03 =    (m.m_d[4]*m.m_d[9]*m.m_d[14]  - m.m_d[4]*m.m_d[13]*m.m_d[10]  - 
			m.m_d[5]*m.m_d[8]*m.m_d[14]  + m.m_d[5]*m.m_d[12]*m.m_d[10]  + 
			m.m_d[6]*m.m_d[8]*m.m_d[13]  - m.m_d[6]*m.m_d[12]*m.m_d[9]  );

	double m10 =    (m.m_d[1]*m.m_d[10]*m.m_d[15] - m.m_d[1]*m.m_d[14]*m.m_d[11]  - 
			m.m_d[2]*m.m_d[9]*m.m_d[15]  + m.m_d[2]*m.m_d[13]*m.m_d[11]  + 
			m.m_d[3]*m.m_d[9]*m.m_d[14]  - m.m_d[3]*m.m_d[13]*m.m_d[10]  );

	double m11 =   -(m.m_d[0]*m.m_d[10]*m.m_d[15] - m.m_d[0]*m.m_d[14]*m.m_d[11]  - 
			m.m_d[2]*m.m_d[8]*m.m_d[15]  + m.m_d[2]*m.m_d[12]*m.m_d[11]  + 
			m.m_d[3]*m.m_d[8]*m.m_d[14]  - m.m_d[3]*m.m_d[12]*m.m_d[10]  );

	double m12 =    (m.m_d[0]*m.m_d[9]*m.m_d[15]  - m.m_d[0]*m.m_d[13]*m.m_d[11]  - 
			m.m_d[1]*m.m_d[8]*m.m_d[15]  + m.m_d[1]*m.m_d[12]*m.m_d[11]  + 
			m.m_d[3]*m.m_d[8]*m.m_d[13]  - m.m_d[3]*m.m_d[12]*m.m_d[9]   );

	double m13 =   -(m.m_d[0]*m.m_d[9]*m.m_d[14]  - m.m_d[0]*m.m_d[13]*m.m_d[10]  - 
			m.m_d[1]*m.m_d[8]*m.m_d[14]  + m.m_d[1]*m.m_d[12]*m.m_d[10]  + 
			m.m_d[2]*m.m_d[8]*m.m_d[13]  - m.m_d[2]*m.m_d[12]*m.m_d[9]   );

	double m20 =   -(m.m_d[1]*m.m_d[6]*m.m_d[15]  - m.m_d[1]*m.m_d[14]*m.m_d[7]   - 
			m.m_d[2]*m.m_d[5]*m.m_d[15]  + m.m_d[2]*m.m_d[13]*m.m_d[7]   + 
			m.m_d[3]*m.m_d[5]*m.m_d[14]  - m.m_d[3]*m.m_d[13]*m.m_d[6]   );

	double m21 =    (m.m_d[0]*m.m_d[6]*m.m_d[15]  - m.m_d[0]*m.m_d[14]*m.m_d[7]   - 
			m.m_d[2]*m.m_d[4]*m.m_d[15]  + m.m_d[2]*m.m_d[12]*m.m_d[7]   + 
			m.m_d[3]*m.m_d[4]*m.m_d[14]  - m.m_d[3]*m.m_d[12]*m.m_d[6]   );

	double m22 =   -(m.m_d[0]*m.m_d[5]*m.m_d[15]  - m.m_d[0]*m.m_d[13]*m.m_d[7]   - 
			m.m_d[1]*m.m_d[4]*m.m_d[15]  + m.m_d[1]*m.m_d[12]*m.m_d[7]   + 
			m.m_d[3]*m.m_d[4]*m.m_d[13]  - m.m_d[3]*m.m_d[12]*m.m_d[5]   );	

	double m23 =    (m.m_d[0]*m.m_d[5]*m.m_d[14]  - m.m_d[0]*m.m_d[13]*m.m_d[6]   - 
			m.m_d[1]*m.m_d[4]*m.m_d[14]  + m.m_d[1]*m.m_d[12]*m.m_d[6]   + 
			m.m_d[2]*m.m_d[4]*m.m_d[13]  - m.m_d[2]*m.m_d[12]*m.m_d[5]   );	

	double m30 =    (m.m_d[1]*m.m_d[6]*m.m_d[11]  - m.m_d[1]*m.m_d[10]*m.m_d[7]   - 
			m.m_d[2]*m.m_d[5]*m.m_d[11]  + m.m_d[2]*m.m_d[9]*m.m_d[7]    + 
			m.m_d[3]*m.m_d[5]*m.m_d[10]  - m.m_d[3]*m.m_d[9]*m.m_d[6]    );	

	double m31 =   -(m.m_d[0]*m.m_d[6]*m.m_d[11]  - m.m_d[0]*m.m_d[10]*m.m_d[7]   - 
			m.m_d[2]*m.m_d[4]*m.m_d[11]  + m.m_d[2]*m.m_d[8]*m.m_d[7]    + 
			m.m_d[3]*m.m_d[4]*m.m_d[10]  - m.m_d[3]*m.m_d[8]*m.m_d[6]    );

	double m32 =    (m.m_d[0]*m.m_d[5]*m.m_d[11]  - m.m_d[0]*m.m_d[9]*m.m_d[7]    - 
			m.m_d[1]*m.m_d[4]*m.m_d[11]  + m.m_d[1]*m.m_d[8]*m.m_d[7]    + 
			m.m_d[3]*m.m_d[4]*m.m_d[9]   - m.m_d[3]*m.m_d[8]*m.m_d[5]    );

	double m33 =   -(m.m_d[0]*m.m_d[5]*m.m_d[10]  - m.m_d[0]*m.m_d[9]*m.m_d[6]    - 
			m.m_d[1]*m.m_d[4]*m.m_d[10]  + m.m_d[1]*m.m_d[8]*m.m_d[6]    + 
			m.m_d[2]*m.m_d[4]*m.m_d[9]   - m.m_d[2]*m.m_d[8]*m.m_d[5]    );



    return IAMatrix(	m00/det, m01/det, m02/det, m03/det,
			m10/det, m11/det, m12/det, m13/det,
			m20/det, m21/det, m22/det, m23/det,
			m30/det, m31/det, m32/det, m33/det);
		      

			
	

}
#endif
