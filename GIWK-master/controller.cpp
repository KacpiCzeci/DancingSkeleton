#include "controller.h"
void Controller::initAll(){
	glfwInit();
	this->window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	glewInit();
	glEnable(GL_DEPTH_TEST);
	std::cout << "hello world";
}

void Controller::endAll() {
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}