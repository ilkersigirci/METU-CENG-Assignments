#include "helper.h"
#include "Camera.h"
#include <vector>

static GLFWwindow * window = NULL;
//#define PI 3.14159265
#define PI glm::pi<float>()
// Shaders
GLuint idProgramShader;
GLuint idFragmentShader;
GLuint idVertexShader;
GLuint idJpegTexture[2];
GLuint idMVPMatrix;

int widthTexture, heightTexture;
Camera cam;
bool fullScreen = false;
int width = 1000, height = 1000;
int displayWidth, displayHeight;

glm::vec3 lightPosition;
int verticesNumber;
glm::vec3* vertices;
GLfloat heightFactor = 10.0f;

static void errorCallback(int error,
	const char * description) {
	fprintf(stderr, "Error: %s\n", description);
}

void clearMatrices() {
	glClearDepth(1.0f);
	glClearColor(0, 0, 0, 1);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void createTriangles() {

	verticesNumber = 6 * widthTexture * heightTexture;
	vertices = new glm::vec3[verticesNumber];

    glm::vec3 vertex0, vertex1, vertex2, vertex3;
    int index = 0;

    for(int i = 0; i < widthTexture; i++){
        for(int j = 0; j < heightTexture; j++){

            vertex0 = glm::vec3(i, 0, j);
			vertex1 = glm::vec3(i+1, 0, j+1);
            vertex2 = glm::vec3(i+1, 0, j);
			vertex3 = glm::vec3(i, 0, j+1);
			
			// Two triangles with same winding order is formed
			vertices[index++] = vertex0;
			vertices[index++] = vertex2;
            vertices[index++] = vertex1;

            vertices[index++] = vertex0,
            vertices[index++] = vertex1;
            vertices[index++] = vertex3;
		}
	}
}

void sendTextureData()  {
	glUniform1i(glGetUniformLocation(idProgramShader, "widthTexture"  ), widthTexture);
	glUniform1i(glGetUniformLocation(idProgramShader, "heightTexture" ), heightTexture);
	glUniform1i(glGetUniformLocation(idProgramShader, "firstTexture"    ), 0);
	glUniform1i(glGetUniformLocation(idProgramShader, "secondTexture"), 1);

	glUniform1f(glGetUniformLocation(idProgramShader, "heightFactor"  ), heightFactor);
	glUniform1f(glGetUniformLocation(idProgramShader, "offset"  ), cam.offset);
	glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
}

void configureScreen(){

	if(fullScreen) {

		fullScreen = false;
		glfwSetWindowMonitor( window, nullptr, 0, 0, displayWidth, displayHeight, 0 );

	}
	else {
		displayWidth = width;
		displayHeight = height;

		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		fullScreen = true;

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		glfwSetWindowMonitor( window, monitor, 0, 0, mode->width, mode->height, 0 );
	}
}

static void keyCallback(GLFWwindow *win, int key, int scancode, int action, int mods) { // GLFWwindow *window default
  
	switch(key) {

		case GLFW_KEY_Q:{ // offset left
			cam.offset += 1;
			glUniform1f(glGetUniformLocation(idProgramShader, "offset"  ), cam.offset);
			break;
		}
		case GLFW_KEY_E:{ // offset right
			cam.offset -= 1;
			glUniform1f(glGetUniformLocation(idProgramShader, "offset"  ), cam.offset);
			break;
		}	
		/**************************** LIGHT MOVEMENT ***********************************/
		case GLFW_KEY_UP:{
			lightPosition.z += 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}
		case GLFW_KEY_DOWN:{
			lightPosition.z -= 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}
		case GLFW_KEY_LEFT:{
			lightPosition.x += 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}
		case GLFW_KEY_RIGHT:{
			lightPosition.x -= 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}
		case GLFW_KEY_T:{
			lightPosition.y += 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}
		case GLFW_KEY_G:{
			lightPosition.y -= 5;
			glUniform3fv(glGetUniformLocation(idProgramShader, "lightPosition"), 1, &lightPosition[0]);
			break;
		}		
		/**************************** LIGHT MOVEMENT ***********************************/
		case GLFW_KEY_I:{ // Reset Camera
			cam.initialize(widthTexture, heightTexture, idProgramShader);
			break;
		}
		case GLFW_KEY_R:{ //Increase height factor
			heightFactor += 0.5;
			GLuint hfLocation = glGetUniformLocation(idProgramShader, "heightFactor");
			glUniform1f(hfLocation, heightFactor);
			break;
		}
		case GLFW_KEY_F:{ //Decrease height factor
			heightFactor -= 0.5;
			GLuint hfLocation = glGetUniformLocation(idProgramShader, "heightFactor");
			glUniform1f(hfLocation, heightFactor);
			break;
		}
		case GLFW_KEY_W:{ //Pitch up	
			cam.pitchUp();
			break;   
		}
		case GLFW_KEY_S:{ //Pitch down
			cam.pitchDown();
			break;
		}
		case GLFW_KEY_A:{ //Yaw left
			cam.yawLeft();
			break;
		}
		case GLFW_KEY_D:{ //Yaw right
			cam.yawRight();
			break;
		}		
		case GLFW_KEY_X:{ //Reset speed
			cam.resetSpeed();
			break;
		}
		case GLFW_KEY_Y:{ //Increase speed
			cam.increaseSpeed();
			break;
		}
		case GLFW_KEY_H:{ //Decrease speed
			cam.decreaseSpeed();
			break;
		}
		case GLFW_KEY_P:{ //Switch to full screen
			if(action == GLFW_PRESS) configureScreen();
			break;
		}
	}
}

int main(int argc, char * argv[]) {

	if (argc != 3) {
		printf("Only two texture image expected!\n");
		exit(-1);
	}
	glfwSetErrorCallback(errorCallback);

	if (!glfwInit()) exit(-1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
	/* For MacOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); */

	window = glfwCreateWindow(width, height, "CENG477-HW3", NULL, NULL); // 1000, 1000

	if (!window) {
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		glfwTerminate();
		exit(-1);
	}

	initShaders();
	glUseProgram(idProgramShader);
	initTexture(argv[1], & widthTexture, & heightTexture, 0);
	initTexture(argv[2], & widthTexture, & heightTexture, 1);
	lightPosition = glm::vec3(widthTexture / 2.0, 100, heightTexture / 2.0);

	cam.initialize(widthTexture, heightTexture, idProgramShader);
	cam.sendCameraData();

	glfwSetKeyCallback(window, keyCallback);
	glViewport (0, 0, width, height);

	createTriangles();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);

	sendTextureData();
	
	while (!glfwWindowShouldClose(window)) {

		clearMatrices();
		glfwGetWindowSize(window, &width, &height);
		glViewport (0, 0, width, height);

		cam.updateCameraPosition();
		cam.sendCameraData();

		// draw triangles
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, verticesNumber);
		glDisableClientState(GL_VERTEX_ARRAY);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}