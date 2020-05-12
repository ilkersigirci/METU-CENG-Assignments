#include "Shape.h"
#include "Scene.h"
#include <cstdio>
Shape::Shape(void)
{
}

Shape::Shape(int id, int matIndex)
    : id(id), matIndex(matIndex)
{
}

Sphere::Sphere(void)
{}

/* Constructor for sphere. You will implement this. */
Sphere::Sphere(int id, int matIndex, int cIndex, float R, vector<Vector3f> *pVertices)
    : Shape(id, matIndex), R(R)
{
	c = (*pVertices)[cIndex-1];
}

/* Sphere-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Sphere::intersect(const Ray & ray) const
{
	Vector3f d = ray.direction;
	Vector3f o = ray.origin;
	ReturnVal result;
	result.isintersecting = false;
	float my_eps = 1000*pScene->intTestEps;  //FIXME: degisecek burasi

	float doc = d.dot(o-c);
	float dd  = d.dot(d);
	float determinant = pow(2*doc,2) - 4*dd*(((o-c).dot(o-c))-R*R);
	float t = 0;

	if(determinant < 0) return result;
	else if(determinant == 0){
		result.isintersecting = true;
		t = (-2*doc + sqrt(determinant)) / (2*dd);		
	}
	else{		
		float root1 = (-2*doc + sqrt(determinant)) / (2*dd);
		float root2 = (-2*doc - sqrt(determinant)) / (2*dd);
		if  (root1 < 0 && root2 < 0) return result;
		else{
			result.isintersecting = true;
			if (root1 > my_eps && root2 > my_eps) t = (root1<root2) ? root1 : root2;
			else if (root1 > my_eps && root2 < 0) t = root1;
			else    						 t = root2;
		}		
	}
	Vector3f intersection = ray.getPoint(t);
	Vector3f normalVector = (intersection - c).normalized(); // normalized form
	result.intersectPoint = intersection;
	result.surfaceNormal  = normalVector;
	result.t = t;
	return result;
}

Triangle::Triangle(void)
{}

/* Constructor for triangle. You will implement this. */
Triangle::Triangle(int id, int matIndex, int p1Index, int p2Index, int p3Index, vector<Vector3f> *pVertices)
    : Shape(id, matIndex)
{
	p1 = (*pVertices)[p1Index-1];
    p2 = (*pVertices)[p2Index-1];
    p3 = (*pVertices)[p3Index-1];
}

/* Triangle-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Triangle::intersect(const Ray & ray) const
{
	ReturnVal result;
	result.isintersecting = false;

	Vector3f d = ray.direction;
	Vector3f o = ray.origin;

	//Cramers Rule
	Matrix3f A;
	float Adeterminant;
	A << p1-p2, p1-p3, d;
	Adeterminant = A.determinant();

	Matrix3f betamatrix;
	float betamatrixdeterminant;
	betamatrix << p1-o, p1-p3, d;
	betamatrixdeterminant = betamatrix.determinant();

	Matrix3f gamamatrix;
	float gamamatrixdeterminant;
	gamamatrix << p1-p2, p1-o, d;
	gamamatrixdeterminant = gamamatrix.determinant();

	Matrix3f tmatrix;
	float tmatrixdeterminant;
	tmatrix << p1-p2, p1-p3, p1-o;
	tmatrixdeterminant = tmatrix.determinant();
	
	float beta = betamatrixdeterminant / Adeterminant;

	float gama = gamamatrixdeterminant / Adeterminant;

	float t = tmatrixdeterminant / Adeterminant;

	float eps = pScene->intTestEps;
	float my_eps = 1000*eps;  //FIXME: degisecek burasi

	if(t > my_eps && beta >= -eps && gama >= -eps && (beta+gama) <= 1){ 
		
		result.isintersecting = true;
		Vector3f crossproduct = (p2-p1).cross(p3-p1);
		Vector3f normal = crossproduct.normalized();
		result.surfaceNormal = normal;
		Vector3f intersectionpoint = ray.getPoint(t);
		result.intersectPoint = intersectionpoint;
	}
	result.t = t;
	return result;
}

Mesh::Mesh()
{}

/* Constructor for mesh. You will implement this. */
Mesh::Mesh(int id, int matIndex, const vector<Triangle>& faces, vector<int> *pIndices, vector<Vector3f> *pVertices)
    : Shape(id, matIndex)
{
	this->faces = faces;
}

/* Mesh-ray intersection routine. You will implement this. 
Note that ReturnVal structure should hold the information related to the intersection point, e.g., coordinate of that point, normal at that point etc. 
You should to declare the variables in ReturnVal structure you think you will need. It is in defs.h file. */
ReturnVal Mesh::intersect(const Ray & ray) const
{
	// butun ucgenlerle intersect et, pindicesi kullanma, kesisen iki ucgenden yakin olani al
	ReturnVal result,temp;
	float mint;
	result.isintersecting = false;

	for(auto face : faces){
		temp = face.intersect(ray);
		if(temp.isintersecting){
			if(result.isintersecting == false){
				mint = temp.t;
				result = temp;
			}
			if(temp.t < mint){
				result = temp;
				mint = temp.t;
			}
		}
	}	
	return result;	
}
