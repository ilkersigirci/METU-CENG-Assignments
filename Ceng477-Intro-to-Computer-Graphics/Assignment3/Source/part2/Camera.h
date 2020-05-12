#ifndef __CAMERA__H__
#define __CAMERA__H__

#include "helper.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <cmath>

using namespace std;

class Camera {
	public:
		glm::vec3 position;
		glm::vec3 gaze;
		glm::vec3 v;
		
		GLfloat angle;
		GLfloat aspectRatio;
		GLfloat nearPlane;
		GLfloat farPlane;
		GLfloat offset;
		GLfloat speed;
		GLuint idProgramShader;	

		Camera();
		void initialize(int widthTexture, int heightTexture, GLuint &idProgramShader);
		void updateCameraPosition();
		void sendCameraData();
		void resetSpeed();
		void increaseSpeed();
		void decreaseSpeed();
		void pitchDown();
		void pitchUp();
		void yawLeft();
		void yawRight();
		
};


#endif