#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/cimport.h>
#include "shaderprogram.h"
#include "ModelCtrl.h"

class Drower
{	
protected:
	GLFWwindow* window;
	glm::mat4 cameraPosition;
	glm::mat4 Perspective;
public:
	Drower(GLFWwindow*);
	//czyœci ekran
	void clear();
	void setCamera(float=0, float=0, float=-5, float=0, float=0);
	
	
};

