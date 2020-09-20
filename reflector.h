#pragma once

#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "shaderprogram.h"
#include "constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

struct Light
{
	glm::mat4 position;
	glm::vec4 direction;
	float anglein;
	float angleout;
};

class Reflector {
private:
	std::vector<float> vertices_base;
	std::vector<float> normals_base;
	std::vector<float> textcords_base;
	std::vector<float> vertices_handle;
	std::vector<float> normals_handle;
	std::vector<float> textcords_handle;
	Light light;
	glm::mat4 M_handle;
	glm::mat4 M_base;
	float speed_handle;
	float speed_base;
	float angle_handle;
	float angle_base;
protected:
	void createBase();
	void createHandle();
public:
	Reflector(glm::mat4 M);
	void drawHandle(std::vector<GLuint> texture);
	void drawBase(std::vector<GLuint> texture);
	void Move(float timestamp);
	void changeMatricehandle();
	void changeMatricebase();
	void setMatrice(glm::mat4 M);
	glm::vec4 returnLightdir();
	glm::vec4 returnLight();
	glm::mat4 returnMatrice();
	float returnAnglein();
	float returnAngleout();
	~Reflector(); 

};

#endif