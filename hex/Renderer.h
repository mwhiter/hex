#pragma once

#include <SFML/Graphics.hpp>

namespace mandr {

	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void draw(sf::RenderWindow& window);
		void SetRenderCallbackFunc(void(*callback)(sf::RenderWindow&));
	private:
		void(*draw_func)(sf::RenderWindow&);
	};

}