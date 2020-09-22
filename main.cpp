#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "lodepng.h"
#include "shaderprogram.h"
#include "controller.h"
#include "Drower.h"
#include "ModelCtrl.h"
#include "ModelGroup.h"
#include "scene.h"
#include <iostream>


float key_X  = 0.0f;
float key_Y = 5.0f;
float key_Z = -50.0f;
float key_Side = 0.0f;
float speed = 0.3;
float key_Y_Side = 5.0f;
bool nextKF = 0;
std::vector<GLuint> texture;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mod) {



	if (action == GLFW_REPEAT) {
		if (key == GLFW_KEY_W) {
			key_X += sin(key_Side);
			key_Z += cos(key_Side);
		}
		else if (key == GLFW_KEY_S) {
			key_X -= sin(key_Side) ;
			key_Z -= cos(key_Side) ;
		}
		else if (key == GLFW_KEY_A) {
			key_Y += speed;
			key_Y_Side += speed;
		}
		else if (key == GLFW_KEY_D) {
			key_Y -= speed;
			key_Y_Side -= speed;
		}
	}
	else if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_X) {
			nextKF = 1;
		}
		else if (key == GLFW_KEY_LEFT) {
			key_Side += speed/2;
		}
		else if (key == GLFW_KEY_RIGHT) {
			key_Side -= speed/2;
		}
		else if (key == GLFW_KEY_UP) {
			key_Y_Side += speed/2;
		}
		else if (key == GLFW_KEY_DOWN) {
			key_Y_Side -= speed/2;
		}
	}
}

std::vector<GLuint> readTexture(std::vector<const char*> file) {
	std::vector<unsigned char> image;
	unsigned int width = 0, height = 0;
	unsigned int error;
	std::vector<GLuint> tex(file.size());

	for (int i = 0; i < file.size(); i++) {
		error = lodepng::decode(image, width, height, file[i]);

		glActiveTexture(GL_TEXTURE0 + i);
		glGenTextures(1, &tex[i]);
		glActiveTexture(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex[i]);

		glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

		
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		//std::cout << width << "," << height << "\n";
		//std::cout << error << "\n";

		image.clear();
	}
	return tex;
}


int main(){
	float timestamp = 0.0f;

	Controller libcontroll;
	libcontroll.initAll();
	texture = readTexture({ "wood_plank.png", "grass.png", "oak_log.png", "obsidian.png", "iron.png" });

	glfwSetKeyCallback(libcontroll.getWindow(), key_callback);


	Drower drowIT(libcontroll.getWindow());

	std::string dane1 = "keyFrames";
	std::string dane2 = "kf";

	Scene S;
	ModelGroup SceletonA(9,dane1, dane2, 0.0f, 4.0f, 0.0f);
	float Time = 0.0f;
	glfwSetTime(0);
	
	while (!glfwWindowShouldClose(libcontroll.getWindow())) {
		timestamp = glfwGetTime();
		glfwSetTime(0);
		drowIT.clear();
		S.drawScene(timestamp, texture);


		SceletonA.interpolation(Time, &texture[4]);
		Time += 0.05f;


		glfwSwapBuffers(libcontroll.getWindow());
		glfwPollEvents();
		if (Time >= 1.0f)
		{
			Time = 0.0f;
			SceletonA.goToNextKF();
			std::cout << "next frame" << std::endl;
		}
		drowIT.setCamera(key_X, key_Y, key_Z, key_Side, key_Y_Side);
	}

	libcontroll.endAll();
	return 0;
}