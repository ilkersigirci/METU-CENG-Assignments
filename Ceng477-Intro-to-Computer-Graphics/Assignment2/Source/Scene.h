#ifndef _SCENE_H_
#define _SCENE_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Matrix4.h"

using namespace std;

class Scene
{
public:
	Color backgroundColor;
	bool cullingEnabled;
	int projectionType;

	vector< vector<Color> > image;
	vector< Camera* > cameras;
	vector< Vec3* > vertices;
	vector< Color* > colorsOfVertices;
	vector< Scaling* > scalings;
	vector< Rotation* > rotations;
	vector< Translation* > translations;
	vector< Model* > models;

	Scene(const char *xmlPath);

	void initializeImage(Camera* camera);
	void forwardRenderingPipeline(Camera* camera);
	int makeBetweenZeroAnd255(double value);
	void writeImageToPPMFile(Camera* camera);
	void convertPPMToPNG(string ppmFileName, int osType);
	Matrix4 modelingTransformation(Model* model);
	Matrix4 cameraTransformation(Camera *camera);
	Matrix4 orthographicTransformation(Camera* camera);
	Matrix4 perspectiveTransformation(Camera* camera);
	Vec4 perspectiveDivide(Vec4 vector);
	Vec3 viewPortTransformation(Camera* camera, Vec4 vertex);
	bool visible(double den, double num, double &t_e, double &t_l);
	std::pair<Vec4, Vec4> liangBarsky(Vec4 p0, Vec4 p1, Camera *camera);
	bool backfaceCulling(Vec4 v0, Vec4 v1, Vec4 v2, Camera* camera);
	void lineRasterization_Low(int x0, int y0, int x1, int y1, Color c0, Color c1);
	void lineRasterization_High(int x0, int y0, int x1, int y1, Color c0, Color c1);
	void lineRasterization(Vec3 v0, Vec3 v1);
	void triangleRasterization(Vec3 v0, Vec3 v1, Vec3 v2, Camera* camera);
	double triangleRasterizationLineEquation(double x, double y, Vec3 d0, Vec3 d1);
};

#endif
