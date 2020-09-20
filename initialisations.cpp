#include "initialisations.h"

 initialisations::initialisations() {
	GLFWwindow* window;
	 


	
	
	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);
	
	
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glewInit();
	glfwInit();
	glEnable(GL_DEPTH_TEST);
}
void initialisations::errors() {
	std::cout << "hello world";

}