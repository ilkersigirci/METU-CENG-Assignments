#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "Shape.h"
#include "tinyxml2.h"
#include "Image.h"
#include <cfloat>
#include <time.h>
using namespace tinyxml2;

// MIrror formula
// 𝐿𝑜(𝒙,𝒘𝒐)=𝐿e(𝒙,𝒘𝒐) + integral(𝑓(𝒙,𝒘𝒐,𝒘𝒊)*𝐿𝑖(𝒙,𝒘𝒊)*𝑐𝑜𝑠𝜃𝑑𝑤)


/* 
 * Must render the scene from each camera's viewpoint and create an image.
 * You can use the methods of the Image class to save the image as a PPM file. 
 */

void Scene::renderScene(void)
{
	/* time_t t = time(NULL);
	cout << ctime(&t); */

	for(auto camera : pScene->cameras){
		int col = camera->imgPlane.nx;  // width = col
		int row = camera->imgPlane.ny; // heigth = row
		Image img(col, row);		
		Vector3f finalColor;
		Color color;		
		for(int x = 0 ; x < row; x++){
			for(int y = 0 ; y < col; y++){
				Ray r = camera->getPrimaryRay(y,x);
				finalColor = renderMaster(r, maxRecursionDepth);

				for(int i = 0; i < 3; i++){
					int temp = finalColor[i];
					temp = (temp > 255) ? 255 : temp;
					temp = (temp < 0  ) ? 0   : temp;
					finalColor[i] = temp;
				}				
				color.red = finalColor[0];
				color.grn = finalColor[1];
				color.blu = finalColor[2];
				img.setPixelValue(y,x,color);
			}
		}
		img.saveImage(camera->imageName);
	}
	/* t = time(NULL);
	cout << ctime(&t); */
}

Vector3f Scene::renderMaster(Ray r, int recursionDepth){

	Vector3f color(0,0,0);
	if(recursionDepth == 0) return color;

	float t_min = FLT_MAX;
	Shape* obj = NULL;
	ReturnVal result, finalResult;
	float my_eps = 1000*pScene->intTestEps;  //FIXME: degisecek burasi
	for(auto o : pScene->objects){
		result = o->intersect(r);					
		if(result.isintersecting == true){
			if (result.t > my_eps){
				if(result.t < t_min){
					t_min = result.t;
					finalResult = result;
					obj = o;							
				}
			}
		}
	}				
	if(obj != NULL){ // viewing ray intersected with an object 
		Material* objMaterial = pScene->materials[obj->matIndex-1];
		Vector3f ambient = (pScene->ambientLight).cwiseProduct(objMaterial->ambientRef);
		color = ambient;
		Vector3f surfaceNorm = finalResult.surfaceNormal;
		Vector3f intersectionPoint = finalResult.intersectPoint;
		Vector3f w_0 = (r.getPoint(0) - intersectionPoint).normalized();
		for(auto l : pScene->lights){
			// Compute Shadow			
			Vector3f w_i = (l->position - intersectionPoint).normalized();
			bool shadowBool = false;
			Ray shadowRay(intersectionPoint+(w_i*shadowRayEps),w_i);							
			float light_t = shadowRay.gett(l->position);
			for(auto p : pScene->objects){ // Compute Shadow
				ReturnVal shadowIntersect = p->intersect(shadowRay);
				if(shadowIntersect.isintersecting){
					if(shadowIntersect.t < light_t){
						shadowBool = true;
						break; 
					}
					else continue;
				}
			}
			if(shadowBool== true) continue;
			// Compute Diffuse		
			double w_in = w_i.dot(surfaceNorm);
			float diffuseCos = max(0.0, w_in);
			Vector3f irradiance = (l->computeLightContribution(intersectionPoint));
			Vector3f diffuse = diffuseCos*(irradiance.cwiseProduct(objMaterial->diffuseRef));
			// Compute Specular			
			Vector3f h = (w_i + w_0).normalized();\
			double nh = surfaceNorm.dot(h);
			float specularCos = max(0.0, nh);						
			Vector3f specular = pow(specularCos,objMaterial->phongExp)*((objMaterial->specularRef).cwiseProduct(irradiance));
			// Compute Final Color
			color += diffuse + specular;
		}
		Vector3f mirrRef = objMaterial->mirrorRef;
		if(mirrRef != Vector3f(0,0,0)){
			Vector3f w_r = ( -w_0 + 2 * surfaceNorm*(surfaceNorm.dot(w_0)) ).normalized();
			Ray w_r_ray(intersectionPoint, w_r);
			Vector3f mirrShading = mirrRef.cwiseProduct(renderMaster(w_r_ray, recursionDepth-1));
			color += mirrShading;
		}
		
	}				
	else{
		Vector3f bg = pScene->backgroundColor;
		color = bg;
	}
	return color;	
}

// Parses XML file. 
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLError eResult;
	XMLElement *pElement;

	maxRecursionDepth = 1;
	shadowRayEps = 0.001;

	eResult = xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	pElement = pRoot->FirstChildElement("MaxRecursionDepth");
	if(pElement != nullptr)
		pElement->QueryIntText(&maxRecursionDepth);

	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%f %f %f", &backgroundColor[0], &backgroundColor[1], &backgroundColor[2]);

	pElement = pRoot->FirstChildElement("ShadowRayEpsilon");
	if(pElement != nullptr)
		pElement->QueryFloatText(&shadowRayEps);

	pElement = pRoot->FirstChildElement("IntersectionTestEpsilon");
	if(pElement != nullptr)
		eResult = pElement->QueryFloatText(&intTestEps);

	// Parse cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while(pCamera != nullptr)
	{
        int id;
        char imageName[64];
        Vector3f pos, gaze, up;
        ImagePlane imgPlane;

		eResult = pCamera->QueryIntAttribute("id", &id);
		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &pos[0], &pos[1], &pos[2]);
		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &gaze[0], &gaze[1], &gaze[2]);
		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%f %f %f", &up[0], &up[1], &up[2]);
		camElement = pCamera->FirstChildElement("NearPlane");
		str = camElement->GetText();
		sscanf(str, "%f %f %f %f", &imgPlane.left, &imgPlane.right, &imgPlane.bottom, &imgPlane.top);
		camElement = pCamera->FirstChildElement("NearDistance");
		eResult = camElement->QueryFloatText(&imgPlane.distance);
		camElement = pCamera->FirstChildElement("ImageResolution");	
		str = camElement->GetText();
		sscanf(str, "%d %d", &imgPlane.nx, &imgPlane.ny);
		camElement = pCamera->FirstChildElement("ImageName");
		str = camElement->GetText();
		strcpy(imageName, str);

		cameras.push_back(new Camera(id, imageName, pos, gaze, up, imgPlane));

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// Parse materals
	pElement = pRoot->FirstChildElement("Materials");
	XMLElement *pMaterial = pElement->FirstChildElement("Material");
	XMLElement *materialElement;
	while(pMaterial != nullptr)
	{
		materials.push_back(new Material());

		int curr = materials.size() - 1;
	
		eResult = pMaterial->QueryIntAttribute("id", &materials[curr]->id);
		materialElement = pMaterial->FirstChildElement("AmbientReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->ambientRef[0], &materials[curr]->ambientRef[1], &materials[curr]->ambientRef[2]);
		materialElement = pMaterial->FirstChildElement("DiffuseReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->diffuseRef[0], &materials[curr]->diffuseRef[1], &materials[curr]->diffuseRef[2]);
		materialElement = pMaterial->FirstChildElement("SpecularReflectance");
		str = materialElement->GetText();
		sscanf(str, "%f %f %f", &materials[curr]->specularRef[0], &materials[curr]->specularRef[1], &materials[curr]->specularRef[2]);
		materialElement = pMaterial->FirstChildElement("MirrorReflectance");
		if(materialElement != nullptr)
		{
			str = materialElement->GetText();
			sscanf(str, "%f %f %f", &materials[curr]->mirrorRef[0], &materials[curr]->mirrorRef[1], &materials[curr]->mirrorRef[2]);
		}
				else
		{
			materials[curr]->mirrorRef[0] = 0.0;
			materials[curr]->mirrorRef[1] = 0.0;
			materials[curr]->mirrorRef[2] = 0.0;
		}
		materialElement = pMaterial->FirstChildElement("PhongExponent");
		if(materialElement != nullptr)
			materialElement->QueryIntText(&materials[curr]->phongExp);

		pMaterial = pMaterial->NextSiblingElement("Material");
	}

	// Parse vertex data
	pElement = pRoot->FirstChildElement("VertexData");
	int cursor = 0;
	Vector3f tmpPoint;
	str = pElement->GetText();
	while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
		cursor++;
	while(str[cursor] != '\0')
	{
		for(int cnt = 0 ; cnt < 3 ; cnt++)
		{
			if(cnt == 0)
				tmpPoint[0] = atof(str + cursor);
			else if(cnt == 1)
				tmpPoint[1] = atof(str + cursor);
			else
				tmpPoint[2] = atof(str + cursor);
			while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
				cursor++; 
			while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
				cursor++;
		}
		vertices.push_back(tmpPoint);
	}

	// Parse objects
	pElement = pRoot->FirstChildElement("Objects");
	
	// Parse spheres
	XMLElement *pObject = pElement->FirstChildElement("Sphere");
	XMLElement *objElement;
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int cIndex;
		float R;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Center");
		eResult = objElement->QueryIntText(&cIndex);
		objElement = pObject->FirstChildElement("Radius");
		eResult = objElement->QueryFloatText(&R);

		objects.push_back(new Sphere(id, matIndex, cIndex, R, &vertices));

		pObject = pObject->NextSiblingElement("Sphere");
	}

	// Parse triangles
	pObject = pElement->FirstChildElement("Triangle");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Indices");
		str = objElement->GetText();
		sscanf(str, "%d %d %d", &p1Index, &p2Index, &p3Index);

		objects.push_back(new Triangle(id, matIndex, p1Index, p2Index, p3Index, &vertices));

		pObject = pObject->NextSiblingElement("Triangle");
	}

	// Parse meshes
	pObject = pElement->FirstChildElement("Mesh");
	while(pObject != nullptr)
	{
		int id;
		int matIndex;
		int p1Index;
		int p2Index;
		int p3Index;
		int cursor = 0;
		int vertexOffset = 0;
		vector<Triangle> faces;
		vector<int> *meshIndices = new vector<int>;

		eResult = pObject->QueryIntAttribute("id", &id);
		objElement = pObject->FirstChildElement("Material");
		eResult = objElement->QueryIntText(&matIndex);
		objElement = pObject->FirstChildElement("Faces");
		objElement->QueryIntAttribute("vertexOffset", &vertexOffset);
		str = objElement->GetText();
		while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
			cursor++;
		while(str[cursor] != '\0')
		{
			for(int cnt = 0 ; cnt < 3 ; cnt++)
			{
				if(cnt == 0)
					p1Index = atoi(str + cursor) + vertexOffset;
				else if(cnt == 1)
					p2Index = atoi(str + cursor) + vertexOffset;
				else
					p3Index = atoi(str + cursor) + vertexOffset;
				while(str[cursor] != ' ' && str[cursor] != '\t' && str[cursor] != '\n')
					cursor++; 
				while(str[cursor] == ' ' || str[cursor] == '\t' || str[cursor] == '\n')
					cursor++;
			}
			faces.push_back(*(new Triangle(-1, matIndex, p1Index, p2Index, p3Index, &vertices)));
			meshIndices->push_back(p1Index);
			meshIndices->push_back(p2Index);
			meshIndices->push_back(p3Index);
		}

		objects.push_back(new Mesh(id, matIndex, faces, meshIndices, &vertices));

		pObject = pObject->NextSiblingElement("Mesh");
	}

	// Parse lights
	int id;
	Vector3f position;
	Vector3f intensity;
	pElement = pRoot->FirstChildElement("Lights");

	XMLElement *pLight = pElement->FirstChildElement("AmbientLight");
	XMLElement *lightElement;
	str = pLight->GetText();
	sscanf(str, "%f %f %f", &ambientLight[0], &ambientLight[1], &ambientLight[2]);

	pLight = pElement->FirstChildElement("PointLight");
	while(pLight != nullptr)
	{
		eResult = pLight->QueryIntAttribute("id", &id);
		lightElement = pLight->FirstChildElement("Position");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &position[0], &position[1], &position[2]);
		lightElement = pLight->FirstChildElement("Intensity");
		str = lightElement->GetText();
		sscanf(str, "%f %f %f", &intensity[0], &intensity[1], &intensity[2]);

		lights.push_back(new PointLight(position, intensity));

		pLight = pLight->NextSiblingElement("PointLight");
	}
}
