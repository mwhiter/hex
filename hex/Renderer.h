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

		sf::View& getView();
	private:
		sf::View m_View;
		void(*draw_func)(sf::RenderWindow&);
	};

}