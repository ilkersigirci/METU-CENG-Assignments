#include "Camera.h"
#include "helper.h"
#include <vector>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
using namespace std;

Camera::Camera() {}

void Camera::initialize(int widthTexture, int heightTexture, GLuint &idProgramShader){
	this->v = glm::vec3 (0,0,1.0);
	this->gaze = glm::vec3 (0,-1.0,0);
	//this->w = glm::vec3 (-(this->gaze.x), -(this->gaze.y), -(this->gaze.z));
	//this->u = glm::cross(this->v, this->gaze);
	this->position = glm::vec3 (0, 600, 0);
	this->nearPlane = 0.1f;
	this->farPlane = 1000.0f;
	this->aspectRatio = 1.0f;
	this->angle = 45.0f;
	this->speed = 0;
	this->offset = 0;
	this->idProgramShader = idProgramShader;
}

void Camera::updateCameraPosition() {
	this->position += this->speed * this->gaze;			
}

void Camera::sendCameraData() {
	glm::vec3 center = this->position + this->gaze * this->nearPlane;
	glm::mat4 projectionMatrix = glm::perspective(this->angle, this->aspectRatio, this->nearPlane, this->farPlane);
	glm::mat4 viewMatrix = glm::lookAt(this->position, center, this->v);
	glm::mat4 projectionViewMatrix = projectionMatrix * viewMatrix;
	glUniformMatrix4fv(glGetUniformLocation(this->idProgramShader, "MVP"), 1, GL_FALSE, &projectionViewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(this->idProgramShader, "MV"), 1, GL_FALSE, &viewMatrix[0][0]);
	//glUniformMatrix3fv(glGetUniformLocation(this->idProgramShader, "cameraPosition"), 1, GL_FALSE, &this->position[0]);
	glUniform3fv(glGetUniformLocation(this->idProgramShader, "cameraPosition"), 1, &this->position[0]);

}

void Camera::resetSpeed() {
	this->speed = 0;
}

void Camera::increaseSpeed() {
	this->speed += 0.01;
}

void Camera::decreaseSpeed() {
	this->speed -= 0.01;
}

void Camera::pitchUp() {
	/* this->gaze = glm::rotate(this->gaze, -0.05f, this->u);
	this->v = glm::rotate(this->v, -0.05f, this->u); */
	glm::vec3 minus_U = glm::cross(this->gaze, this->v);
	this->gaze = glm::rotate(this->gaze, 0.05f, minus_U);
	this->v = glm::rotate(this->v, 0.05f, minus_U);
}

void Camera::pitchDown() {
	/* this->gaze = glm::rotate(this->gaze, 0.05f, this->u);
	this->v = glm::rotate(this->v, 0.05f, this->u); */
	glm::vec3 minus_U = glm::cross(this->gaze, this->v);
	this->gaze = glm::rotate(this->gaze, -0.05f, minus_U);
	this->v = glm::rotate(this->v, -0.05f, minus_U);
}

void Camera::yawLeft() {
	/* this->gaze = glm::rotate(this->gaze, 0.05f, this->v);
	this->u = glm::rotate(this->u, 0.05f, this->v); */
	this->gaze = glm::rotate(this->gaze, 0.05f, this->v);
}

void Camera::yawRight() {
	/* this->gaze = glm::rotate(this->gaze, -0.05f, this->v);
	this->u = glm::rotate(this->u, -0.05f, this->v); */
	this->gaze = glm::rotate(this->gaze, -0.05f, this->v);
}
