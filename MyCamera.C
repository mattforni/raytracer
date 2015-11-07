/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCamera.C
 *    DATE: October 1, 2007
 *************************************************************************/
#include "MyCamera.H"
#include "IAlgebra.inl"
#include <Qt/QtOpenGL>

struct CS123SceneCameraData;

MyCamera::MyCamera (CS123SceneCameraData camData)
{
	m_eye 		= camData.pos;
	m_look 		= camData.look;
	m_up 		= camData.up;
	m_heightAngle 	= camData.heightAngle;
	m_aspectRatio 	= camData.aspectRatio;
	m_near		= 1.0;
	m_far		= 30.0;
	setWidthAngle();
	makeUVN();
}

MyCamera::~MyCamera()
{
}

void MyCamera::makeUVN()
{
	m_n= -m_look/length(m_look);
	m_u= cross(m_up, m_n)/length(cross(m_up, m_n));
	m_u.normalize();
	m_v= cross(m_n, m_u);
}

void MyCamera::setWidthAngle()
{
  double height	= (double)4.0*tan((double)(m_heightAngle/2.0)*(M_PI/180.0));
  double width	= (double)height*m_aspectRatio;
  m_widthAngle	= ((double)360.0/M_PI)*atan(width/4.0);
}

IAMatrix MyCamera::makeWTFMatrix()
{
	double k = (m_near/m_far);
	IAMatrix A(	1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1/(k-1), k/(k-1),
			0.0, 0.0, -1.0, 0.0); 

	IAMatrix B = 	scale_mat(IAVector(m_far, m_far, m_far));

	IAMatrix C(	1.0/tan((m_widthAngle/2.0)*(M_PI/180.0)), 0.0, 0.0, 0.0,
		    	0.0, 1.0/tan((m_heightAngle/2.0)*(M_PI/180.0)), 0.0, 0.0,
		    	0.0, 0.0, 1.0, 0.0,
		    	0.0, 0.0, 0.0, 1.0);

	IAMatrix D(	m_u.m_d[0], m_u.m_d[1], m_u.m_d[2], 0.0,
			m_v.m_d[0], m_v.m_d[1], m_v.m_d[2], 0.0,
			m_n.m_d[0], m_n.m_d[1], m_n.m_d[2], 0.0,
			0.0, 0.0, 0.0, 1.0	);

	IAMatrix E(	1.0, 0.0, 0.0, -m_eye.m_d[0],
		   	0.0, 1.0, 0.0, -m_eye.m_d[1],
		   	0.0, 0.0, 1.0, -m_eye.m_d[2],
		   	0.0, 0.0, 0.0, 1.0);

	IAMatrix wtf = A*B*C*D*E;
	return wtf;
}

IAMatrix MyCamera::makeFTWMatrix()
{	
	IAMatrix Sxyz = inv_scale_mat(IAVector(m_far, m_far, m_far));
	IAMatrix invSxyz = invert(Sxyz);
;
	IAMatrix Sxy(	1.0/tan((m_widthAngle/2.0)*(M_PI/180.0)), 0.0, 0.0, 0.0,
		    	0.0, 1.0/tan((m_heightAngle/2.0)*(M_PI/180.0)), 0.0, 0.0,
		    	0.0, 0.0, 1.0, 0.0,
		    	0.0, 0.0, 0.0, 1.0);
	IAMatrix invSxy= invert(Sxy);

	IAMatrix R(	m_u[0], m_u[1], m_u[2], 0.0,
			m_v[0], m_v[1], m_v[2], 0.0,
			m_n[0], m_n[1], m_n[2], 0.0,
			0.0, 0.0, 0.0, 1.0	);
	IAMatrix invR= invert(R);

	IAMatrix T(	1.0, 0.0, 0.0, -m_eye[0],
		   	0.0, 1.0, 0.0, -m_eye[1],
		   	0.0, 0.0, 1.0, -m_eye[2],
		   	0.0, 0.0, 0.0, 1.0);
	IAMatrix invT= invert(T);

	IAMatrix ftw= invT*invR*invSxy*invSxyz;
	return ftw;
}
