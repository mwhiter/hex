#include "PCH.h"
#include <SFML/Graphics.hpp>

#include "Application.h"

#include <GLFW/glfw3.h>

using namespace mandr;

int main() {
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}

	Application* app = Application::getInstance();
	app->init();
	app->loop();
	
	return 0;
}