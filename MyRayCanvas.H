#ifndef __MY_RAY_CANVAS_H__
#define __MY_RAY_CANVAS_H__

#include <CS123Image.H>
#include <RayCanvas.H>
#include <iostream>
#include <CS123SceneData.H>

class Shape;
class IAMatrix;
class CS123SceneCameraData;
class CS123SceneGlobalData;
class CS123ScenePrimitive;
class CS123XmlSceneParser;
class CS123SceneLightData;
struct CS123SceneColor;
struct CS123SceneNode;
class MyCamera;


struct listEntry {
	IAMatrix transMatrix;
	IAMatrix invTransMatrix;
	CS123ScenePrimitive primitive;
};

struct intersectRtn {
	double t;
	IAVector oNorm, wNorm, oRay, wRay;
	IAPoint oPoint, wPoint;
	CS123ScenePrimitive primitive;
	CS123Color color;
};

class MyRayCanvas : public RayCanvas {

	public:
		/* No need to worry about this - this is to get concurrent rendering */
		friend class MainSyscallProxy;

		//! Create a canvas with the given dimensions
		MyRayCanvas(int width, int height);
		virtual ~MyRayCanvas();

		//! Render the entire canvas
		virtual void render();
		//! Render the portion of the canvas specified by the rectangle
		virtual void render(const CS123Rectangle&);
		//! This method can be used to control render settings 
		virtual void setRenderSetting(RayOptions option, int value);
		virtual void createList(CS123SceneNode* currNode, IAMatrix parTransMat, IAMatrix invParTransMat);

		//! Override this method to load scenes.  
		/* When you override it, do NOT make it a slot.  Simply declare it
		 * as being a public method */
		virtual void loadScene(const char* sceneFile);
		CS123Color calcShade(intersectRtn objData, int depth);
		CS123Color recursiveRT(IAVector ray, IAPoint p_origin, int depth);
		double checkShadow(IAVector worldD, IAPoint worldP);

	private:
		int m_height, m_widht, m_numLights, m_maxDepth;
		IAPoint m_eye;
		CS123SceneGlobalData m_globalData;
		std::vector<listEntry> m_primitives;
		std::vector<CS123SceneLightData> m_lightData;
		CS123SceneNode* m_root;
		CS123XmlSceneParser* m_parser;
		CS123SceneCameraData m_camData;
		Shape *m_cube, *m_cone, *m_cylinder, *m_sphere;
		std::map<std::string, CS123Image*> m_map;
};
#endif
