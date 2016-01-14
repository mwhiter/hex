#include "Renderer.h"

namespace mandr {

	Renderer::Renderer() {
	}


	Renderer::~Renderer() {
	}

	void Renderer::draw(sf::RenderWindow& window) {
		draw_func(window);
	}

	void Renderer::SetRenderCallbackFunc(void(*callback)(sf::RenderWindow&)) {
		draw_func = callback;
	}
}