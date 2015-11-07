/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyCamera.H
 *    DATE: October 1, 2007
 *************************************************************************/
#ifndef __MY_CAMERA_H__
#define __MY_CAMERA_H__

#include <IAlgebra.H>
#include <CS123SceneData.H>

class MyCamera
{
public:
  	MyCamera(CS123SceneCameraData camData);
  	virtual ~MyCamera();
  
	virtual void setWidthAngle();
	virtual void makeUVN();
	virtual IAMatrix makeWTFMatrix();
	virtual IAMatrix makeFTWMatrix();

protected:
	double m_near, m_far, m_heightAngle, m_widthAngle, m_aspectRatio;
	IAPoint m_eye;
	IAVector m_look, m_up, m_u, m_v, m_n;
};

#endif
