#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <stdio.h>

#include "Scene.h"
#include "Camera.h"
#include "Color.h"
#include "Model.h"
#include "Rotation.h"
#include "Scaling.h"
#include "Translation.h"
#include "Triangle.h"
#include "Vec3.h"
#include "tinyxml2.h"
#include "Helpers.h"
#include "Matrix4.h"

using namespace tinyxml2;
using namespace std;

/*
	Transformations, clipping, culling, rasterization are done here.
	You can define helper functions inside Scene class implementation.
*/
Matrix4 Scene::modelingTransformation(Model* model){
	Matrix4 compositeModelMatrix = getIdentityMatrix();
	for(int k = 0; k < model->numberOfTransformations; k++){
		if(model->transformationTypes[k] == 't'){
			Translation* t = translations[model->transformationIds[k] - 1]; //TODO: indexi control et sonra
			double transform[4][4] = {{1,0,0,t->tx}, {0,1,0,t->ty}, {0,0,1,t->tz}, {0,0,0,1}};
			Matrix4 transformMatrix(transform);
			compositeModelMatrix = multiplyMatrixWithMatrix(transformMatrix, compositeModelMatrix);
			//append transformMatrix;
		}
		else if(model->transformationTypes[k] == 's'){
			Scaling* s = scalings[model->transformationIds[k] - 1];
			double transform[4][4] = {{s->sx,0,0,0}, {0,s->sy,0,0}, {0,0,s->sz,0}, {0,0,0,1}};
			Matrix4 transformMatrix(transform);
			compositeModelMatrix = multiplyMatrixWithMatrix(transformMatrix, compositeModelMatrix);

		}
		
		else{ // rotation around arbitrary axis
			Rotation* r = rotations[model->transformationIds[k] - 1];

			double ux = r->ux;
			double uy = r->uy;
			double uz = r->uz;
			double angle =  (r->angle * M_PI) /180.0;
			double c = cos(angle);
			double s = sin(angle);

			double rotation[4][4] = {{c+ux*ux*(1-c),ux*uy*(1-c)-uz*s,ux*uz*(1-c)+uy*s,0 },\
									{uy*ux*(1-c)+uz*s, c+uy*uy*(1-c), uy*uz*(1-c)-ux*s,0},\
									{uz*ux*(1-c)-uy*s, uz*uy*(1-c)+ux*s, c+uz*uz*(1-c),0},\
									{0,0,0,1}};
			Matrix4 transformMatrix(rotation);
			compositeModelMatrix = multiplyMatrixWithMatrix(transformMatrix, compositeModelMatrix);
			
			/*
			Vec3 u = Vec3(r->ux, r->uy, r->uz, -1);
			u = normalizeVec3(u);

			Vec3 v;

			if((abs(u.x) < abs(u.y)) && (abs(u.x) < abs(u.z)) ){
				v = Vec3(0, u.z, (-1)*u.y, -1);
			}

			else if((abs(u.y) < abs(u.x)) && (abs(u.y) < abs(u.z))){
				v = Vec3((-1)*u.z, 0, u.x, -1);
			}

			else if((abs(u.z) < abs(u.x)) && (abs(u.z) < abs(u.y))){
				v = Vec3((-1)*u.y, u.x, 0, -1);
			}			
			else{
				v = Vec3((-1)*u.y, u.x, 0, -1);
			} 

			v = normalizeVec3(v);
			Vec3 w = crossProductVec3(u, v);
			w = normalizeVec3(w);

			double Minverse[4][4] = { {u.x, v.x, w.x, 0}, {u.y, v.y, w.y, 0}, {u.z, v.z, w.z, 0}, {0,0,0,1} };
			Matrix4 Minversematrix(Minverse); 

			double M[4][4] = { {u.x, u.y, u.z, 0}, {v.x, v.y, v.z, 0}, {w.x, w.y, w.z, 0}, {0,0,0,1} };
			Matrix4 Mmatrix(M);
			double rotationAngle = (r->angle * M_PI) /180.0;
			double rotation[4][4] = { {1,0,0,0}, {0, cos(rotationAngle), (-1)*sin(rotationAngle), 0},\
									 {0, sin(rotationAngle), cos(rotationAngle), 0}, {0,0,0,1} };
			Matrix4 rotationmatrix(rotation); 

			Matrix4 transformMatrix = multiplyMatrixWithMatrix(Minversematrix, multiplyMatrixWithMatrix(rotationmatrix, Mmatrix));
			compositeModelMatrix = multiplyMatrixWithMatrix(transformMatrix, compositeModelMatrix);
			*/
		}	
	}
	return compositeModelMatrix;
}

Matrix4 Scene::cameraTransformation(Camera *camera){
	// Camera Transformations
	double R[4][4] = {{camera->u.x, camera->u.y, camera->u.z, 0},{camera->v.x, camera->v.y, camera->v.z, 0}, {camera->w.x, camera->w.y, camera->w.z, 0}, {0,0,0,1}};
	double translate[4][4] = {{1,0,0, -(camera->pos.x)}, {0,1,0, -(camera->pos.y)}, {0,0,1, -(camera->pos.z)}, {0,0,0,1}};
	
	Matrix4 RMatrix(R);
	Matrix4 translateMatrix(translate);
	Matrix4 Mcam = multiplyMatrixWithMatrix(RMatrix, translateMatrix);

	return Mcam;
	
}

Matrix4 Scene::orthographicTransformation(Camera *camera){
	double r = camera -> right;
	double l = camera -> left;
	double t = camera -> top;
	double b = camera -> bottom;
	double f = camera->far;
	double n = camera->near;
	
	double Morth[4][4] = { {2/(r-l), 0, 0, -(r+l)/(r-l)}, {0, 2/(t-b), 0, -(t+b)/(t-b)}, \
							{0, 0, -2/(f-n), -(f+n)/(f-n)}, {0,0,0,1} };
	return  Matrix4(Morth);
	
}

Matrix4 Scene::perspectiveTransformation(Camera *camera){

	double r = camera -> right;
	double l = camera -> left;
	double t = camera -> top;
	double b = camera -> bottom;
	double f = camera->far;
	double n = camera->near;

	double Mper[4][4] = { {2*n/(r-l), 0, (r+l)/(r-l), 0}, {0, 2*n/(t-b), (t+b)/(t-b) ,0}, \
							{0, 0, -(f+n)/(f-n), -2*f*n/(f-n)}, {0,0,-1,0} };
	return Matrix4(Mper);
}

Vec4 Scene::perspectiveDivide(Vec4 vector){

	double t = vector.t;
	Vec4 result;

    result.x = vector.x / t;
    result.y = vector.y / t;
    result.z = vector.z / t;
    result.t = vector.t / t;
	result.color = vector.color;

    return result;
}

Vec3 Scene::viewPortTransformation(Camera* camera, Vec4 vertex){
	double viewport[4][4] = { {camera->horRes/2.0, 0, 0, (camera->horRes-1)/2.0},\
							 {0, camera->verRes/2.0, 0, (camera->verRes-1)/2.0}, {0, 0, 1/2, 1/2}, {0,0,0,0} };
	Matrix4 viewportMatrix(viewport);
	Vec4 result4x1 = multiplyMatrixWithVec4(viewportMatrix, vertex);
	Vec3 result = Vec3(result4x1.x, result4x1.y, result4x1.z, vertex.color);
	return result;
}

bool Scene::visible(double den, double num, double &t_e, double &t_l){
	//cout << "####################" << endl;
	//cout << "den " << den << endl;
	//cout << "num " << num << endl;
	//cout << "t_e " << t_e << endl;
	//cout << "t_l " << t_l << endl;
	
	if(den > 0){
		double t = num/den;
		//cout << "t when d>0 " << t << endl;
		if(t>t_l){
			return false;
		}
		if(t>t_e){
			t_e = t;
		}
	}
	else if(den < 0){
		double t = num/den;
		//cout << "t when d<0 " << t << endl;
		if(t<t_e){
			return false;
		}
		if(t<t_l){
			t_l = t;
		}
	}
	else if (num>0){
		return false;
	}
	//cout << "####################" << endl;
	return true;
}

std::pair<Vec4, Vec4> Scene::liangBarsky(Vec4 p0, Vec4 p1, Camera *camera){

	
	double t_E = 0;
	double t_L = 1;
	double d_x = p1.x - p0.x;
	double d_y = p1.y - p0.y;
	double d_z = p1.z - p0.z;

	double x_min = -1; double x_max =  1;	
	double y_min = -1; double y_max =  1;	
	double z_min = -1; double z_max =  1;
	
	
	double x0 = p0.x;
	double y0 = p0.y;
	double z0 = p0.z;
	double x1 = p1.x;
	double y1 = p1.y;
	double z1 = p1.z;

	bool isVisible = false;
	if(visible(d_x, x_min-x0, t_E, t_L)){ //left
		//cout << "t_E left: " << t_E << endl;
		//cout << "t_L left: " << t_L << endl;
		if(visible(-d_x, x0 - x_max, t_E, t_L)){ //right
			//cout << "t_E right: " << t_E << endl;
			//cout << "t_L right: " << t_L << endl;
			if(visible(d_y, y_min - y0, t_E, t_L)){ //bottom
				if(visible(-d_y, y0-y_max, t_E, t_L)){ //top
					if(visible(d_z, z_min - z0, t_E, t_L)){ //front
						if(visible(-d_z, z0-z_max, t_E, t_L)){ //back
							isVisible = true;
							//cout << "visible True" << endl;
							if(t_L < 1){
								x1 = x0 + d_x * t_L;
								y1 = y0 + d_y * t_L;
								z1 = z0 + d_z * t_L;
							}
							if(t_E > 0){
								x0 = x0 + d_x * t_E;
								y0 = y0 + d_y * t_E;
								z0 = z0 + d_z * t_E; // burada slayt d_y yapmis
							}
						}
					}
				}
			}
		}
	}

	if(isVisible){
		// t_E ve t_L ye bakarak interpolation yap burda
		Color color0;
		color0.r = (1-t_E) * p0.color.r + t_E * p1.color.r;
		color0.g = (1-t_E) * p0.color.g + t_E * p1.color.g;
		color0.b = (1-t_E) * p0.color.b + t_E * p1.color.b;
		//cout << "old p0 color " << oldp0.color << endl;
		//cout << "p0 color " << p0.color << endl;
		
		Color color1;
		color1.r = t_L * p1.color.r + (1 - t_L) * p0.color.r;
		color1.g = t_L * p1.color.g + (1 - t_L) * p0.color.g;
		color1.b = t_L * p1.color.b + (1 - t_L) * p0.color.b;

		//cout << "old p1 color " << oldp1.color << endl;
		//cout << "p1 color " << p1.color << endl;

		return make_pair(Vec4(x0,y0,z0,1,color0), Vec4(x1,y1,z1,1,color1));
	}
	else{
		//return make_pair(p0, p1);
		return make_pair(Vec4(0,0,0,1,-2), Vec4(0,0,0,1,-2)); // color id is set to -2 for invisible lines
	}
	//return std::make_pair(p0,p1);
}

bool Scene::backfaceCulling(Vec4 v0, Vec4 v1, Vec4 v2, Camera* camera){

	Vec3 cameraPos;
	Vec3 v3_0(v0.x, v0.y, v0.z, 1);
	Vec3 v3_1(v1.x, v1.y, v1.z, 1);
	Vec3 v3_2(v2.x, v2.y, v2.z, 1);

	Vec3 v01 = subtractVec3(v3_1,v3_0);
	Vec3 v02 = subtractVec3(v3_2,v3_0);
	Vec3 n 	 = crossProductVec3(v01, v02);
	n = inverseVec3(n);
	Vec3 v 	 = subtractVec3(v3_0,cameraPos);

	if (dotProductVec3(n,v) < 0) return true; //FIXME: -
	else return false;	
}

void Scene::lineRasterization_Low(int x0, int y0, int x1, int y1, Color c0, Color c1){
	int dx = x1 - x0;
	int dy = y1 - y0;
	int y_i = 1;

	if(dy < 0){
		y_i = -1;
		dy = -dy;
	}
	int D = 2*dy - dx;
	int x = x0;
	int y = y0;
	Color c = c0;
	Color dc;
	dc.r = (c1.r - c0.r)/dx;
	dc.g = (c1.g - c0.g)/dx;
	dc.b = (c1.b - c0.b)/dx;
	
	while(x < x1){
		image[x][y] = c;
		if(D > 0){
			y += y_i;
			D -= 2*dx;
		}
		D += 2*dy;
		x++;
		c.r += dc.r;
		c.g += dc.g;
		c.b += dc.b;
	}
}

void Scene::lineRasterization_High(int x0, int y0, int x1, int y1, Color c0, Color c1){
	int dx = x1 - x0;
	int dy = y1 - y0;
	int xi = 1;
	if(dx < 0){
		xi = -1;
		dx = (-1)*dx;
	}
	Color c = c0;
	Color dc;
	dc.r = (c1.r - c0.r)/dy;
	dc.g = (c1.g - c0.g)/dy;
	dc.b = (c1.b - c0.b)/dy;

	double d = 2*dx - dy;
	int x = x0;
	int y = y0;
	while(y < y1){
		image[x][y] = c;
		if(d > 0){
			x += + xi;
			d -= 2*dy;
		}
		d += 2*dx;
		
		y++;
		c.r += dc.r;
		c.g += dc.g;
		c.b += dc.b;
	}
}

void Scene::lineRasterization(Vec3 v0, Vec3 v1){

	/*
 	int dx = x1 - x0;
	int dy = y1 - y0;
	double m = dy / dx;
	int x = x0;
	int y = y0;

	if( m == 0){

	}
	else if( m == 1){

	}
	
	else if(m > 0 && m < 1){
		
		double d = dy - dx/2;
		//image[x][y] = c
		while(x < x1){
			x = x + 1;
			if(d < 0) d += dy;
			else{
				d += dy - dx;
				y = y + 1;
			}
			//image[x][y] = c
		}
	}
	else if(m < -1 && m > 1){

		double d = dx - dy/2;
		//image[x][y] = c
		while(y < y1){
			y = y + 1;
			if(d < 0) d += dx;
			else{
				d += dx - dy;
				x = x + 1;
			}
			//image[x][y] = c
		}
	} 
	*/
	int   x0 = int(v0.x);
	int   y0 = int(v0.y);
	Color c0 = v0.color;
	int   x1 = int(v1.x);
	int   y1 = int(v1.y);
	Color c1 = v1.color;


	if (abs(y1 - y0) < abs(x1 - x0)){
		if(x0 > x1)  lineRasterization_Low(x1,y1,x0,y0,c1,c0);
		else         lineRasterization_Low(x0,y0,x1,y1,c0,c1);
	}
	else{
		if(y0 > y1)  lineRasterization_High(x1,y1,x0,y0,c1,c0);
		else         lineRasterization_High(x0,y0,x1,y1,c0,c1);
	}

	
	
}

void Scene::triangleRasterization(Vec3 v0, Vec3 v1, Vec3 v2, Camera* camera){

	int x_min = round(min(v0.x, min(v1.x, v2.x)));
	int x_max = round(max(v0.x, max(v1.x, v2.x)));
	int y_min = round(min(v0.y, min(v1.y, v2.y)));
	int y_max = round(max(v0.y, max(v1.y, v2.y)));

	if( x_min < 0) x_min = 0; if (x_max < 0) x_max = 0;
	if( x_max > camera->horRes-1) x_max = camera->horRes-1;
	if( y_min < 0) y_min = 0; if (y_max < 0) y_max = 0;
	if( y_max > camera->verRes-1) y_max = camera->verRes-1;


	//cout << "v0.color" << v0.color << "v1.color" << v1.color << "v2.color" << v2.color << endl;
	//cout << "x_min " << x_min << "x_max" << x_max << "y_min " << y_min << "y_max" << y_max << endl;
	for(int y = y_min; y < y_max; y++){
		for(int x = x_min; x < x_max; x++){
			//FIXME: 0 gelme durumunda alfa,beta,gama durumu degisecek mi?
			double alfa = triangleRasterizationLineEquation(x,y,v1,v2) / (triangleRasterizationLineEquation(round(v0.x), round(v0.y), v1, v2)+EPSILON);
			double beta = triangleRasterizationLineEquation(x,y,v2,v0) / (triangleRasterizationLineEquation(round(v1.x), round(v1.y), v2, v0)+EPSILON);
			double gama = triangleRasterizationLineEquation(x,y,v0,v1) / (triangleRasterizationLineEquation(round(v2.x), round(v2.y), v0, v1)+EPSILON);
			//cout << "alfa " << alfa << "beta" <<  beta << "gama" << gama << endl;
			if( alfa >= 0 && beta >= 0 &&  gama >= 0){
				//double c = alfa * c_0 + beta * c_1 + gama * c_2;
				//draw(x,y, round(c));
				Color c;
				c.r = round(alfa * v0.color.r + beta * v1.color.r + gama * v2.color.r);
				c.g = round(alfa * v0.color.g + beta * v1.color.g + gama * v2.color.g);
				c.b = round(alfa * v0.color.b + beta * v1.color.b + gama * v2.color.b);
				//cout << "color: r g b " << c.r << c.g << c.b << endl;

				if(x < 0 || y < 0) cout << x << y << endl;
				image[x][y] = c;
			}
		}
	}
}

double Scene::triangleRasterizationLineEquation(double x, double y, Vec3 d0, Vec3 d1){

	int x0 = round(d0.x);
	int y0 = round(d0.y);
	int x1 = round(d1.x);
	int y1 = round(d1.y);

	double result = x*(y0 - y1) + y*(x1 - x0) + (x0*y1) - (y0*x1);
	//cout << "triangleRasterization result" << result << endl;
	//if(result == 0) result = EPSILON;      //FIXME: precision check gerekebilir
	return result;
}

void Scene::forwardRenderingPipeline(Camera *camera)
{
	//vector<vector<vector<Vec3>>> transformedVertices;

	for(int i = 0; i < models.size(); i++){

		//vector<vector<Vec3>> modelsTriangles;
		for(int j = 0; j < models[i]->numberOfTriangles; j++){

			vector<Vec4> transformedTriangleVertices;
			int id;

			for(int k = 0; k < 3; k++){
				if(k == 0) id = models[i]->triangles[j].getFirstVertexId() - 1;
				if(k == 1) id = models[i]->triangles[j].getSecondVertexId() - 1;
				if(k == 2) id = models[i]->triangles[j].getThirdVertexId() - 1;

				Vec4 vertex = Vec4(vertices[id]->x, vertices[id]->y, vertices[id]->z, 1, *(colorsOfVertices[vertices[id]->colorId - 1]));
				Matrix4 modelMatrix = modelingTransformation(models[i]);
				Matrix4 cameraMatrix = cameraTransformation(camera);
				Matrix4 projectionMatrix;
				if (projectionType == 0) projectionMatrix = orthographicTransformation(camera); // orthographic projection
				else 					 projectionMatrix = perspectiveTransformation(camera); // perspective projection
				Matrix4 compositematrix = multiplyMatrixWithMatrix(projectionMatrix, multiplyMatrixWithMatrix(cameraMatrix, modelMatrix));
				Vec4 transformedVertex = multiplyMatrixWithVec4(compositematrix, vertex);
				transformedVertex.color = vertex.color;
				if (projectionType == 1) transformedVertex = perspectiveDivide(transformedVertex);  // perspective divide
				//Vec3 viewportedVertex = viewPortTransformation(camera, transformedVertex);          // viewport transformation
				transformedTriangleVertices.push_back(transformedVertex);
			}
			//modelsTriangles.push_back(transformedTriangleVertices);

			//culling
			if(cullingEnabled){
				bool isFrontFaced = backfaceCulling(transformedTriangleVertices[0], transformedTriangleVertices[1], transformedTriangleVertices[2], camera);
				if(isFrontFaced == false) continue;
			}

			if(models[i]->type == 0){ // wireframe mode

				//clipping
				pair<Vec4, Vec4> firstCutLine  = liangBarsky(transformedTriangleVertices[0], transformedTriangleVertices[1], camera);
				pair<Vec4, Vec4> secondCutLine = liangBarsky(transformedTriangleVertices[1], transformedTriangleVertices[2], camera);
				pair<Vec4, Vec4> thirdCutLine  = liangBarsky(transformedTriangleVertices[2], transformedTriangleVertices[0], camera);
							
				// culling buradaydi				

				//viewport transformation
				//FIXME: id = -2 ''yi yapmak lazim 

				if(firstCutLine.first.colorId != -2){

					Vec3 viewportedVertex0 = viewPortTransformation(camera, firstCutLine.first);
					Vec3 viewportedVertex1 = viewPortTransformation(camera, firstCutLine.second);

					lineRasterization(viewportedVertex0, viewportedVertex1);

				}

				if(secondCutLine.first.colorId != -2){

					Vec3 viewportedVertex2 = viewPortTransformation(camera, secondCutLine.first);
					Vec3 viewportedVertex3 = viewPortTransformation(camera, secondCutLine.second);

					lineRasterization(viewportedVertex2, viewportedVertex3);

				} 

				if(thirdCutLine.first.colorId != -2){

					Vec3 viewportedVertex4 = viewPortTransformation(camera, thirdCutLine.first);
					Vec3 viewportedVertex5 = viewPortTransformation(camera, thirdCutLine.second);

					lineRasterization(viewportedVertex4, viewportedVertex5);

				} 

				/*
				Vec3 viewportedVertex0 = viewPortTransformation(camera, firstCutLine.first);
				Vec3 viewportedVertex1 = viewPortTransformation(camera, firstCutLine.second);
				Vec3 viewportedVertex2 = viewPortTransformation(camera, secondCutLine.first);
				Vec3 viewportedVertex3 = viewPortTransformation(camera, secondCutLine.second);
				Vec3 viewportedVertex4 = viewPortTransformation(camera, thirdCutLine.first);
				Vec3 viewportedVertex5 = viewPortTransformation(camera, thirdCutLine.second);
				
				pair<Vec3, Vec3> firstCutLineview = make_pair(viewportedVertex0, viewportedVertex1);
				pair<Vec3, Vec3> secondCutLineview = make_pair(viewportedVertex2, viewportedVertex3);
				pair<Vec3, Vec3> thirdCutLineview = make_pair(viewportedVertex4, viewportedVertex5);				

				//line restarization
				if(firstCutLineview.first.colorId != -2)  lineRasterization(viewportedVertex0, viewportedVertex1);
				if(secondCutLineview.first.colorId != -2) lineRasterization(viewportedVertex2, viewportedVertex3);
				if(thirdCutLineview.first.colorId != -2)  lineRasterization(viewportedVertex4, viewportedVertex5);
				*/

				
			}
			else{
				//culling buradaydi

				//viewport transformation
				Vec3 viewportedVertex0 = viewPortTransformation(camera, transformedTriangleVertices[0]);
				Vec3 viewportedVertex1 = viewPortTransformation(camera, transformedTriangleVertices[1]);
				Vec3 viewportedVertex2 = viewPortTransformation(camera, transformedTriangleVertices[2]);

				//triangle restarization
				triangleRasterization(viewportedVertex0, viewportedVertex1, viewportedVertex2, camera);
			}

		}
		//transformedVertices.push_back(modelsTriangles);

		/*********************************************************************************************
		*************************************** END OF TRANSFORMATION ***********************************
		*********************************************************************************************/
		/* if(models[i]->type == 0){ // wireframe mode
			
			//clip			
			for(int j = 0; j < transformedVertices[i].size(); j++){
				vector<Vec3> trianglevertices = transformedVertices[i][j];
				pair<Vec3, Vec3> firstCutLine  = liangBarsky(trianglevertices[0], trianglevertices[1], camera);
				pair<Vec3, Vec3> secondCutLine = liangBarsky(trianglevertices[1], trianglevertices[2], camera);
				pair<Vec3, Vec3> thirdCutLine  = liangBarsky(trianglevertices[2], trianglevertices[0], camera);

				Vec3 v01 = trianglevertices[1] - trianglevertices[0];
				Vec3 v02 = trianglevertices[2] - trianglevertices[0];
				if(cullingEnabled) backfaceCulling();


				//line restarization
				if(firstCutLine.first.colorId != -2)  lineRasterization(firstCutLine.first,firstCutLine.second);
				if(secondCutLine.first.colorId != -2) lineRasterization(secondCutLine.first,secondCutLine.second);
				if(thirdCutLine.first.colorId != -2)  lineRasterization(thirdCutLine.first,thirdCutLine.second);
			}	
		}
		else{
			
			//if(cullingEnabled) //backfaceCulling()
			// triangle restarization
			for(int j = 0; j < transformedVertices[i].size(); j++){
				vector<Vec3> trianglevertices = transformedVertices[i][j];
				//cout << "before rasterization " << trianglevertices[0].color << trianglevertices[1].color << trianglevertices[2].color << endl;
				triangleRasterization(trianglevertices[0], trianglevertices[1], trianglevertices[2], camera);
			}
		} */
	}
}

/*
	Parses XML file
*/
Scene::Scene(const char *xmlPath)
{
	const char *str;
	XMLDocument xmlDoc;
	XMLElement *pElement;

	xmlDoc.LoadFile(xmlPath);

	XMLNode *pRoot = xmlDoc.FirstChild();

	// read background color
	pElement = pRoot->FirstChildElement("BackgroundColor");
	str = pElement->GetText();
	sscanf(str, "%lf %lf %lf", &backgroundColor.r, &backgroundColor.g, &backgroundColor.b);

	// read culling
	pElement = pRoot->FirstChildElement("Culling");
	if (pElement != NULL)
		pElement->QueryBoolText(&cullingEnabled);

	// read projection type
	pElement = pRoot->FirstChildElement("ProjectionType");
	if (pElement != NULL)
		pElement->QueryIntText(&projectionType);

	// read cameras
	pElement = pRoot->FirstChildElement("Cameras");
	XMLElement *pCamera = pElement->FirstChildElement("Camera");
	XMLElement *camElement;
	while (pCamera != NULL)
	{
		Camera *cam = new Camera();

		pCamera->QueryIntAttribute("id", &cam->cameraId);

		camElement = pCamera->FirstChildElement("Position");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->pos.x, &cam->pos.y, &cam->pos.z);

		camElement = pCamera->FirstChildElement("Gaze");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->gaze.x, &cam->gaze.y, &cam->gaze.z);

		camElement = pCamera->FirstChildElement("Up");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf", &cam->v.x, &cam->v.y, &cam->v.z);

		cam->gaze = normalizeVec3(cam->gaze);
		cam->u = crossProductVec3(cam->gaze, cam->v);
		cam->u = normalizeVec3(cam->u);

		cam->w = inverseVec3(cam->gaze);
		cam->v = crossProductVec3(cam->u, cam->gaze);
		cam->v = normalizeVec3(cam->v);

		camElement = pCamera->FirstChildElement("ImagePlane");
		str = camElement->GetText();
		sscanf(str, "%lf %lf %lf %lf %lf %lf %d %d",
			   &cam->left, &cam->right, &cam->bottom, &cam->top,
			   &cam->near, &cam->far, &cam->horRes, &cam->verRes);

		camElement = pCamera->FirstChildElement("OutputName");
		str = camElement->GetText();
		cam->outputFileName = string(str);

		cameras.push_back(cam);

		pCamera = pCamera->NextSiblingElement("Camera");
	}

	// read vertices
	pElement = pRoot->FirstChildElement("Vertices");
	XMLElement *pVertex = pElement->FirstChildElement("Vertex");
	int vertexId = 1;

	while (pVertex != NULL)
	{
		Vec3 *vertex = new Vec3();
		Color *color = new Color();

		vertex->colorId = vertexId;

		str = pVertex->Attribute("position");
		sscanf(str, "%lf %lf %lf", &vertex->x, &vertex->y, &vertex->z);

		str = pVertex->Attribute("color");
		sscanf(str, "%lf %lf %lf", &color->r, &color->g, &color->b);

		vertices.push_back(vertex);
		colorsOfVertices.push_back(color);

		pVertex = pVertex->NextSiblingElement("Vertex");

		vertexId++;
	}

	// read translations
	pElement = pRoot->FirstChildElement("Translations");
	XMLElement *pTranslation = pElement->FirstChildElement("Translation");
	while (pTranslation != NULL)
	{
		Translation *translation = new Translation();

		pTranslation->QueryIntAttribute("id", &translation->translationId);

		str = pTranslation->Attribute("value");
		sscanf(str, "%lf %lf %lf", &translation->tx, &translation->ty, &translation->tz);

		translations.push_back(translation);

		pTranslation = pTranslation->NextSiblingElement("Translation");
	}

	// read scalings
	pElement = pRoot->FirstChildElement("Scalings");
	XMLElement *pScaling = pElement->FirstChildElement("Scaling");
	while (pScaling != NULL)
	{
		Scaling *scaling = new Scaling();

		pScaling->QueryIntAttribute("id", &scaling->scalingId);
		str = pScaling->Attribute("value");
		sscanf(str, "%lf %lf %lf", &scaling->sx, &scaling->sy, &scaling->sz);

		scalings.push_back(scaling);

		pScaling = pScaling->NextSiblingElement("Scaling");
	}

	// read rotations
	pElement = pRoot->FirstChildElement("Rotations");
	XMLElement *pRotation = pElement->FirstChildElement("Rotation");
	while (pRotation != NULL)
	{
		Rotation *rotation = new Rotation();

		pRotation->QueryIntAttribute("id", &rotation->rotationId);
		str = pRotation->Attribute("value");
		sscanf(str, "%lf %lf %lf %lf", &rotation->angle, &rotation->ux, &rotation->uy, &rotation->uz);

		rotations.push_back(rotation);

		pRotation = pRotation->NextSiblingElement("Rotation");
	}

	// read models
	pElement = pRoot->FirstChildElement("Models");

	XMLElement *pModel = pElement->FirstChildElement("Model");
	XMLElement *modelElement;
	while (pModel != NULL)
	{
		Model *model = new Model();

		pModel->QueryIntAttribute("id", &model->modelId);
		pModel->QueryIntAttribute("type", &model->type);

		// read model transformations
		XMLElement *pTransformations = pModel->FirstChildElement("Transformations");
		XMLElement *pTransformation = pTransformations->FirstChildElement("Transformation");

		pTransformations->QueryIntAttribute("count", &model->numberOfTransformations);

		while (pTransformation != NULL)
		{
			char transformationType;
			int transformationId;

			str = pTransformation->GetText();
			sscanf(str, "%c %d", &transformationType, &transformationId);

			model->transformationTypes.push_back(transformationType);
			model->transformationIds.push_back(transformationId);

			pTransformation = pTransformation->NextSiblingElement("Transformation");
		}

		// read model triangles
		XMLElement *pTriangles = pModel->FirstChildElement("Triangles");
		XMLElement *pTriangle = pTriangles->FirstChildElement("Triangle");

		pTriangles->QueryIntAttribute("count", &model->numberOfTriangles);

		while (pTriangle != NULL)
		{
			int v1, v2, v3;

			str = pTriangle->GetText();
			sscanf(str, "%d %d %d", &v1, &v2, &v3);

			model->triangles.push_back(Triangle(v1, v2, v3));

			pTriangle = pTriangle->NextSiblingElement("Triangle");
		}

		models.push_back(model);

		pModel = pModel->NextSiblingElement("Model");
	}
}

/*
	Initializes image with background color
*/
void Scene::initializeImage(Camera *camera)
{
	if (this->image.empty())
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			vector<Color> rowOfColors;

			for (int j = 0; j < camera->verRes; j++)
			{
				rowOfColors.push_back(this->backgroundColor);
			}

			this->image.push_back(rowOfColors);
		}
	}
	// if image is filled before, just change color rgb values with the background color
	else
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			for (int j = 0; j < camera->verRes; j++)
			{
				this->image[i][j].r = this->backgroundColor.r;
				this->image[i][j].g = this->backgroundColor.g;
				this->image[i][j].b = this->backgroundColor.b;
			}
		}
	}
}

/*
	If given value is less than 0, converts value to 0.
	If given value is more than 255, converts value to 255.
	Otherwise returns value itself.
*/
int Scene::makeBetweenZeroAnd255(double value)
{
	if (value >= 255.0)
		return 255;
	if (value <= 0.0)
		return 0;
	return (int)(value);
}

/*
	Writes contents of image (Color**) into a PPM file.
*/
void Scene::writeImageToPPMFile(Camera *camera)
{
	ofstream fout;

	fout.open(camera->outputFileName.c_str());

	fout << "P3" << endl;
	fout << "# " << camera->outputFileName << endl;
	fout << camera->horRes << " " << camera->verRes << endl;
	fout << "255" << endl;

	for (int j = camera->verRes - 1; j >= 0; j--)
	{
		for (int i = 0; i < camera->horRes; i++)
		{
			fout << makeBetweenZeroAnd255(this->image[i][j].r) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].g) << " "
				 << makeBetweenZeroAnd255(this->image[i][j].b) << " ";
		}
		fout << endl;
	}
	fout.close();
}

/*
	Converts PPM image in given path to PNG file, by calling ImageMagick's 'convert' command.
	os_type == 1 		-> Ubuntu
	os_type == 2 		-> Windows
	os_type == other	-> No conversion
*/
void Scene::convertPPMToPNG(string ppmFileName, int osType)
{
	string command;

	// call command on Ubuntu
	if (osType == 1)
	{
		command = "convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// call command on Windows
	else if (osType == 2)
	{
		command = "magick convert " + ppmFileName + " " + ppmFileName + ".png";
		system(command.c_str());
	}

	// default action - don't do conversion
	else
	{
	}
}