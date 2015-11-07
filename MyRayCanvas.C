/*************************************************************************
 *    NAME: Matthew Fornaciari
 *    USER: mfornaci
 *    FILE: MyRayCanvas.C
 *    DATE: Thu May 10 17:25:24 2007
 *************************************************************************/
#include "MyRayCanvas.H"
#include "IAlgebra.inl"
#include "CS123XmlSceneParser.H"
using namespace std;

#include "MyCamera.H"
#include "MyCube.H"
#include "MyCone.H"
#include "MyCylinder.H"
#include "MySphere.H"

/*************************************************************************
 * Function Name: MyRayCanvas::MyRayCanvas
 * Parameters: 
 * Effects: 
 *************************************************************************/

MyRayCanvas::MyRayCanvas(int width , int height) : RayCanvas(width, height)
{
	m_height = height;
	m_width = width;
	m_root = NULL;
	m_maxDepth = 4;
	m_cube = new MyCube();
	m_cone = new MyCone();
	m_cylinder = new MyCylinder();
	m_sphere = new MySphere();
}

MyRayCanvas::~MyRayCanvas() 
{
	delete m_cube;
	delete m_cone;
	delete m_cylinder;
	delete m_sphere;
}


void MyRayCanvas::render()
{
	MyCube cube;
 	MyCone cone;
	MyCylinder cylinder;
	MySphere sphere;
	MyCamera camera(m_camData);
	m_eye = m_camData.pos;
	IAMatrix ftwMatrix = camera.makeFTWMatrix();
	intersectRtn objData;

	CS123Color lightingColor;

	for (int y= 0; y<m_height; y++) {
		for (int x= 0; x<m_width; x++) {

			IAPoint filmPoint((2.0*x/m_width)-1.0, 1.0-(2.0*y/m_height), -1);
			IAPoint wPoint= ftwMatrix*filmPoint;
	
			IAVector wRay= wPoint-m_eye;
			wRay.normalize();
			lightingColor = recursiveRT(wRay, m_eye, 1);

			setPixel(x, y, lightingColor);
		}
		repaint(0, y, m_width, 1);
		
	}
}

void MyRayCanvas::render(const CS123Rectangle& rect)
{
	MyCamera camera(m_camData);
	m_eye = m_camData.pos;
	IAMatrix ftwMatrix = camera.makeFTWMatrix();
	intersectRtn objData;

	CS123Color lightingColor;

	for (int y= rect.minY; y<rect.maxY; y++) {
		for (int x= rect.minX; x<rect.maxX; x++) {

			IAPoint filmPoint((2.0*x/m_width)-1.0, 1.0-(2.0*y/m_height), -1);
			IAPoint wPoint= ftwMatrix*filmPoint;
	
			IAVector wRay= wPoint-m_eye;
			wRay.normalize();
			lightingColor = recursiveRT(wRay, m_eye, 1);

			setPixel(x, y, lightingColor);
		}
		repaint(0, y, m_width, 1);
	}
}

CS123Color MyRayCanvas::recursiveRT(IAVector ray, IAPoint origin, int depth) 
{
	CS123Color bkgColor;
	bkgColor.r = 0; bkgColor.g = 0; bkgColor.b = 0;
	// initialize closest shape's color to black
	intersectRtn closestObj;
	closestObj.t = INFINITY;

	IAMatrix wtoMat, otwMat;

	// for each of the primitives in the vector make a newT value
	// set to "infinity" and then evaluate t values based on what shape
	for (int i= 0; i<(int)m_primitives.size(); i++) {
		intersectRtn currObj;
		IAMatrix invTransMat	= m_primitives.at(i).invTransMatrix;

		currObj.wRay = ray;
		currObj.oRay = invTransMat*ray;
		currObj.wPoint = origin;
		currObj.oPoint = invTransMat*origin;
		currObj.t = INFINITY;

		switch (m_primitives.at(i).primitive.type) {
			case PRIMITIVE_CUBE:
 				currObj = m_cube->intersect(currObj);
				break;
			case PRIMITIVE_CONE:
				currObj = m_cone->intersect(currObj);
				break;
			case PRIMITIVE_CYLINDER:
				currObj = m_cylinder->intersect(currObj);
				break;
			case PRIMITIVE_SPHERE:
				currObj = m_sphere->intersect(currObj);
				break;
			case PRIMITIVE_TORUS:
				break;
			case PRIMITIVE_MESH:
				break;
		}		
		// if the object is hit and has a smaller t value than 
		// the currect smallT set the closest shape's color and the smallT

		if (currObj.t < closestObj.t) {
			closestObj = currObj;
			otwMat = m_primitives.at(i).invTransMatrix;
			wtoMat = m_primitives.at(i).transMatrix;
			closestObj.primitive = m_primitives.at(i).primitive;
		}
	}
	otwMat = invert(otwMat);
	closestObj.wNorm = otwMat*closestObj.oNorm;
	otwMat.m_d[3] = otwMat.m_d[7] = otwMat.m_d[11] = otwMat.m_d[12] = 0;
	otwMat.m_d[13] = otwMat.m_d[14]; otwMat.m_d[15] = 1;
	otwMat= transpose(otwMat);
	closestObj.wPoint = wtoMat*closestObj.oPoint;
	// the multiply the matrix by the object space norm to get the world space norm
	closestObj.wNorm.normalize();
	
	if (closestObj.t < INFINITY && closestObj.t > -EPSILON)
		return calcShade(closestObj, depth);
	else
		return bkgColor;
}

CS123Color MyRayCanvas::calcShade(intersectRtn objData, int depth) 
{
	double globAmb	= m_globalData.ka;
	double globDiff = m_globalData.kd;
	double globSpec = m_globalData.ks;
	CS123SceneColor objAmb = objData.primitive.material.cAmbient;
	CS123SceneColor objDiff = objData.primitive.material.cDiffuse;
	CS123SceneColor objSpec = objData.primitive.material.cSpecular;
	CS123SceneColor objRef = objData.primitive.material.cReflective;

	CS123Color lColor, rColor;
	IAPoint lPos;
	IAVector lRay, rRay, lAtten;
	double dotProdNL, dotProdRV, dotRVExp, lightCheck, lDist, fAtten;

	double 	rTotal = 0.0, bTotal = 0.0, gTotal = 0.0;
	lColor.r = 0;
	lColor.b = 0;
	lColor.g = 0;

	if (objData.t == INFINITY)
		return lColor;

/***	AMBIENT COLORING	***/
	rTotal = globAmb*objAmb.r*255.0;
	bTotal = globAmb*objAmb.b*255.0;
	gTotal = globAmb*objAmb.g*255.0;

/*** 	TEXTURE MAPPING		***/
	CS123SceneFileMap* textMapFile = objData.primitive.material.textureMap;
	CS123Image* textMap = m_map[textMapFile->filename];
	CS123Color textMapCol;
	textMapCol.r=0; textMapCol.g=0; textMapCol.b=0;
	double repU, repV, blend;
	int width, height;
	if (textMapFile->isUsed) 
	{
		repU = textMapFile->repeatU;
		repV = textMapFile->repeatV;
		// creates a CS123Image using the stored texture map file

		switch (objData.primitive.type) 
		{
			case PRIMITIVE_CUBE:
 				textMapCol = m_cube->map(objData.oPoint, repU, repV, textMap);				break;
			case PRIMITIVE_CONE:
				textMapCol = m_cone->map(objData.oPoint, repU, repV, textMap);
				break;
			case PRIMITIVE_CYLINDER:
				textMapCol = m_cylinder->map(objData.oPoint, repU, repV, textMap);
				break;
			case PRIMITIVE_SPHERE:
				textMapCol = m_sphere->map(objData.oPoint, repU, repV, textMap);
				break;
			case PRIMITIVE_TORUS:

				break;
			case PRIMITIVE_MESH:

				break;
		}
	
		blend = objData.primitive.material.blend;
	} 

/***	DIFFUSE COLORING	***/
/***	SPECULAR COLORING	***/
	for (int i=0; i<(int)m_lightData.size(); i++) 
	{
		fAtten = 0.0;
		switch (m_lightData.at(i).type) 
		{
			case LIGHT_POINT:
				lPos = m_lightData.at(i).pos;
				lRay = lPos-objData.wPoint;
				break;
			case LIGHT_DIRECTIONAL:
				lRay = -m_lightData.at(i).dir;
				break;
			case LIGHT_SPOT:
				break;
			case LIGHT_AREA:
				break;
		}

		lAtten = m_lightData.at(i).function;
		lDist = length(lRay);
		fAtten = 1.0/(lAtten[0] + lAtten[1]*lDist + lAtten[2]*lDist*lDist);
		
		lightCheck = checkShadow(lRay, objData.wPoint);
		// if the light is not blocked by any objects at this pixel
		if (lightCheck == INFINITY) {
			lRay.normalize();
			// dot product of the world space norm and the lighting vector
			dotProdNL = dot(lRay, objData.wNorm);
			if (dotProdNL < 0.0)
			dotProdNL = 0.0;

			rRay = 2.0 * objData.wNorm * dot(objData.wNorm, -lRay) + lRay;
			rRay.normalize();

			dotProdRV = dot(rRay, objData.wRay);

			if (dotProdRV < 0.0)
				dotProdRV = 0.0;

			dotRVExp = pow(dotProdRV, objData.primitive.material.shininess);

			IAVector attenuation = m_lightData.at(i).function;
			CS123SceneColor lightCol = m_lightData.at(i).color;

			rTotal += 	fAtten*lightCol.r*( 
					((double)blend*(globDiff*textMapCol.r*dotProdNL)) + 
					(double)(1.0-blend)*(globDiff*objDiff.r*dotProdNL*255.0) + 
					globSpec*objSpec.r*dotRVExp*255.0 );

			gTotal += 	fAtten*lightCol.g*( 
					((double)blend*(globDiff*textMapCol.g*dotProdNL)) + 
					(double)(1.0-blend)*(globDiff*objDiff.g*dotProdNL*255.0) +
					globSpec*objSpec.g*dotRVExp*255.0 );

			bTotal +=	fAtten*lightCol.b*( 
					((double)blend*(globDiff*textMapCol.b*dotProdNL)) + 
					(double)(1.0-blend)*(globDiff*objDiff.b*dotProdNL*255.0) + 
					globSpec*objSpec.b*dotRVExp*255.0 );
		}
	}

	/*** reflection ***
	if (depth < m_maxDepth) {
		rColor = recursiveRT(rRay, objData.wPoint, depth+1);

		rTotal += globSpec*objRef.r*rColor.r;
		bTotal += globSpec*objRef.b*rColor.b;
		gTotal += globSpec*objRef.g*rColor.g;
	}  **/

	lColor.r = (unsigned char)MIN(255.0, rTotal);
	lColor.b = (unsigned char)MIN(255.0, bTotal);
	lColor.g = (unsigned char)MIN(255.0, gTotal);

	return lColor;
}

double MyRayCanvas::checkShadow(IAVector worldD, IAPoint worldP) 
{
	intersectRtn closestObj;
	closestObj.t = INFINITY;

	IAMatrix wtoMat, otwMat;

	// for each of the primitives in the vector make a newT value
	// set to "infinity" and then evaluate t values based on what shape
	for (int i= 0; i<(int)m_primitives.size(); i++) {
		intersectRtn currObj;
		IAMatrix invTransMat	= m_primitives.at(i).invTransMatrix;
		IAMatrix transMat	= m_primitives.at(i).transMatrix;

		currObj.wRay = worldD;
		currObj.oRay = invTransMat*currObj.wRay;
		currObj.wPoint = worldP;
		currObj.oPoint = invTransMat*currObj.wPoint;
		currObj.t = INFINITY;

		switch (m_primitives.at(i).primitive.type) {
			case PRIMITIVE_CUBE:
 				currObj = m_cube->intersect(currObj);
				break;
			case PRIMITIVE_CONE:
				currObj = m_cone->intersect(currObj);
				break;
			case PRIMITIVE_CYLINDER:
				currObj = m_cylinder->intersect(currObj);
				break;
			case PRIMITIVE_SPHERE:
				currObj = m_sphere->intersect(currObj);
				break;
			case PRIMITIVE_TORUS:
				break;
			case PRIMITIVE_MESH:
				break;
		}		
		// if the object is hit and has a smaller t value than 
		// the currect smallT set the closest shape's color and the smallT

		if (currObj.t < closestObj.t && currObj.t > EPSILON)
			closestObj = currObj;
	}
	
	return closestObj.t;
}

void MyRayCanvas::setRenderSetting(RayOptions option, int value)
{
	switch (option) {
		case RAY_OPTION_RECURSION_DEPTH:
			m_maxDepth = value;
			break;

		case RAY_OPTION_SUPERSAMPLING:
			printf("No Supersampling Available at this Time, Sorry!\n");
			break;
	}
}

void MyRayCanvas::loadScene(const char* sceneFile)
{
	m_map.clear();
	m_lightData.clear();
	m_primitives.clear();

	m_parser= new CS123XmlSceneParser(sceneFile);

	// if the file cannot be parsed print error message
	if (!m_parser->parse())
		printf("Invalid Parse File\n\n");
	// if the camera data is not valid print error message
	if(!m_parser->getCameraData(m_camData))
		printf("Invalid Camera Data\n\n");

	m_numLights= m_parser->getNumLights();
	for (int i=0; i<m_numLights; i++) {
		CS123SceneLightData data;
		// if the light data for light i is invalid print error message
		if(!m_parser->getLightData(i, data)) {
			printf("Invalid Light Data at index %d\n\n", i);
		}
		// add the CS123SceneLightData to the vector
		m_lightData.push_back(data);
	}
	// if the global data is not valid print error message
	if(!m_parser->getGlobalData(m_globalData))
		printf("Invalid Global Scene Data\n\n");
	// gets the root node and create list of primitives 
	m_root= m_parser->getRootNode();
	createList(m_root, IAMatrix(1.0, 0.0, 0.0, 0.0,
				    0.0, 1.0, 0.0, 0.0,
				    0.0, 0.0, 1.0, 0.0,
				    0.0, 0.0, 0.0, 1.0), IAMatrix(	1.0, 0.0, 0.0, 0.0,
				    					0.0, 1.0, 0.0, 0.0,
				    					0.0, 0.0, 1.0, 0.0,
				    					0.0, 0.0, 0.0, 1.0));
}

void MyRayCanvas::createList(CS123SceneNode* currNode, IAMatrix parTransMat, IAMatrix invParTransMat) {
	int transSize = (currNode->transformations).size();
	int primsSize = (currNode->primitives).size();
	int childSize = (currNode->children).size();
	IAMatrix totTransMat, totInvTransMat;

	IAMatrix transMat = IAMatrix(	1.0, 0.0, 0.0, 0.0,
					0.0, 1.0, 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0);

	IAMatrix invTransMat= IAMatrix(	1.0, 0.0, 0.0, 0.0,
					0.0, 1.0, 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0,
					0.0, 0.0, 0.0, 1.0);

	// for all transformations at this node
	for (int i=0; i<transSize; i++) {
		CS123SceneTransformation* currTransform= currNode->transformations.at(i);
		IAMatrix tempMat, tempInvMat;
		switch (currTransform->type) {
			// the tempMat is equal to the transformation 
			// matrix created using currTransform's translate vector
			// the tempInvMat is equal to the inverse transformation
			// matrix created using currTransform's translate vector
			case TRANSFORMATION_TRANSLATE:
				tempMat= trans_mat(currTransform->translate);
				tempInvMat= inv_trans_mat(currTransform->translate);
				break;
			// the tempMat is equal to the scaling 
			// matrix created using currTransform's scale vector
			// the tempInvMat is equal to the inverse scaling
			// matrix created using currTransform's scale vector
			case TRANSFORMATION_SCALE:
				tempMat= scale_mat(currTransform->scale);
				tempInvMat= inv_scale_mat(currTransform->scale);
				break;
			// the tempMat is equal to the rotational 
			// matrix created using currTransform's rotation vector
			// the tempInvMat is equal to the inverse rotational
			// matrix created using currTransform's rotation vector
			case TRANSFORMATION_ROTATE:
				tempMat= rot_mat(IAPoint(), currTransform->rotate, currTransform->angle);
				tempInvMat= inv_rot_mat(IAPoint(), currTransform->rotate, currTransform->angle);
				break;
			// the tempMat is equal to currTransform's matrix
			// the tempInvMat is equal to the inverse of currTransform's matrix
			case TRANSFORMATION_MATRIX:
				tempMat= currTransform->matrix;
				tempInvMat= invert(currTransform->matrix);
				break;
		}	
		// the transformation matrix = currTransMat*nextTransform
		transMat= transMat*tempMat;
		// the inverse transformation matrix = nextInverseTransform*currInvTransMat		
		invTransMat= tempInvMat*invTransMat;
	}
	totTransMat= parTransMat*transMat;
	totInvTransMat= invTransMat*invParTransMat;
	IAMatrix identity= totTransMat*totInvTransMat;
	// if the node has a primitive in it create a list entry and put it into the vector
	if (primsSize!= 0) {
		listEntry tempEntry;
		tempEntry.transMatrix= totTransMat;
		tempEntry.invTransMatrix= totInvTransMat;
		tempEntry.primitive.material = currNode->primitives.at(0)->material;
		
		if (tempEntry.primitive.material.textureMap->filename.size() > 0) 
		{
			CS123Image* textMap = new CS123Image(tempEntry.primitive.material.textureMap->filename.c_str());
			m_map[tempEntry.primitive.material.textureMap->filename] = textMap;
		}


		switch (currNode->primitives.at(0)->type) {
			case PRIMITIVE_CUBE:
				tempEntry.primitive.type= PRIMITIVE_CUBE;
				break;
			case PRIMITIVE_CONE:
				tempEntry.primitive.type= PRIMITIVE_CONE;
				break;
			case PRIMITIVE_CYLINDER:
				tempEntry.primitive.type= PRIMITIVE_CYLINDER;
				break;
			case PRIMITIVE_SPHERE:
				tempEntry.primitive.type= PRIMITIVE_SPHERE;
				break;
			case PRIMITIVE_TORUS:
	    			break;
	  		case PRIMITIVE_MESH:
	    			break;
	  	}    
	m_primitives.push_back(tempEntry);
	}	
	// if not a leaf node, then recurse
	if (childSize!= 0) {
		// iterate through all of the children passing in this nodes rotation matrix
		for (int j=0; j<childSize; j++) {
			createList(currNode->children.at(j), totTransMat, totInvTransMat);
		}
	}
	// if the node is a leaf then return without doing anything
	else {
		return;
	} 
}
