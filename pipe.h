#pragma once
#ifndef PIPE_H
#define PIPE_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "shaderprogram.h"
#include "constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

class Pipe {
protected:
	std::vector<float> verts;
	std::vector<float> normals;
	std::vector<float> begin;
	std::vector<float> textcoords;
	glm::mat4 M_pipe;
	float length;
public:
	Pipe(float l, std::vector<float> b);
	void createPipe(int steps, float radius1, float radius2);
	std::vector<float> returnPipeVertices();
	std::vector<float> returnPipeNormals();
	std::vector<float> returnPipeTextcoords();
	void setMatrice(glm::mat4 matrice);
	glm::mat4 returnMatrice();
	~Pipe();
};
#endif