#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "shaderprogram.h"
#include "constants.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "reflector.h"
#include "pipe.h"

class Scene {
private:
	std::vector<Reflector> reflectors;
	std::vector<Pipe> pipes;
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> textcords;
	glm::mat4 M_Scene;
	std::vector<glm::vec4> lights;
public:
	Scene();
	void createScene();
	void drawScene(float timestamp, std::vector<GLuint> texture);
	~Scene();
};
#endif