#include "Camera.h"

Camera::Camera(int id,                      // Id of the camera
               const char* imageName,       // Name of the output PPM file 
               const Vector3f& pos,         // Camera position
               const Vector3f& gaze,        // Camera gaze direction
               const Vector3f& up,          // Camera up direction
               const ImagePlane& imgPlane)  // Image plane parameters
		: pos(pos), gaze(gaze), up(up)
{	
	const char* tempName = imageName;
	int i = 0;
	for(i; *tempName != '\0'; i++){
		this->imageName[i] = *tempName;
		tempName++;
	}
	this->imageName[i] = '\0';
	this->id = id;
	this->imgPlane = imgPlane;
}

/* Takes coordinate of an image pixel as row and col, and
 * returns the ray going through that pixel. 
 */
Ray Camera::getPrimaryRay(int col, int row) const
{
	Vector3f my_U = gaze.cross(up);	

	float s_u = (col + 0.5) * ((imgPlane.right - imgPlane.left) / imgPlane.nx);
	float s_v = (row + 0.5) * ((imgPlane.top - imgPlane.bottom) / imgPlane.ny);

	Vector3f m = pos + gaze*imgPlane.distance;
	Vector3f q = m   + imgPlane.left*my_U + imgPlane.top*up;
	Vector3f s = q   + s_u*my_U - s_v*up;
	Vector3f d = (s - pos).normalized();

	Ray primaryRay(pos, d);

	return primaryRay;
}
