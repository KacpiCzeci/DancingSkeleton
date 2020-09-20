#include "controller.h"
void Controller::initAll(){
	glfwInit();
	this->window = glfwCreateWindow(900, 900, "OpenGL", NULL, NULL);
	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
		exit(EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);
	initShaders();
	sp->use();
	std::cout << "hello world" << std::endl;
}

void Controller::endAll() {
	freeShaders();
	glfwDestroyWindow(this->window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
GLFWwindow* Controller::getWindow() {
	return this->window;
}