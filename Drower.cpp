#include "Drower.h"


Drower::Drower(GLFWwindow* window) {
	this->window = window;
	this->cameraPosition = glm::lookAt(
		glm::vec3(0.0f, 5.0f, -50.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	this->Perspective = glm::perspective(50.0f * 3.14f / 180.0f, 1.0f, 1.0f, 150.0f);
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(this->Perspective));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(this->cameraPosition));
	
}

void Drower::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.27, 0.27, 0.27, 1);
}

void Drower::setCamera(float x, float y, float z, float rota, float y_side) {
	this->cameraPosition = glm::lookAt(
			glm::vec3(x, y, z),
			glm::vec3(x+sin(rota), y_side, z+cos(rota)),
			glm::vec3(0.0f, 1.0f, 0.0f));



	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(this->cameraPosition));
}



