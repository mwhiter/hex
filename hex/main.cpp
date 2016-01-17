#include "PCH.h"
#include <SFML/Graphics.hpp>

#include "Application.h"

using namespace mandr;

int main() {
	Application* app = Application::getInstance();
	app->init();
	app->loop();
	
	return 0;
}