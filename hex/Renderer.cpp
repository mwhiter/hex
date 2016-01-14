#include "Renderer.h"

namespace mandr {

	Renderer::Renderer() : m_View(sf::View(sf::Vector2f(0,0), sf::Vector2f(1600, 900))) {
	}


	Renderer::~Renderer() {
	}

	void Renderer::draw(sf::RenderWindow& window) {
		window.setView(m_View);
		draw_func(window);
	}

	void Renderer::SetRenderCallbackFunc(void(*callback)(sf::RenderWindow&)) {
		draw_func = callback;
	}

	sf::View& Renderer::getView() {
		return m_View;
	}
}