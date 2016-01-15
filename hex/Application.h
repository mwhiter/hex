#pragma once

#include <iostream>
#include "Map.h"
#include "InputHandler.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>

namespace mandr {

	// A instance of the application
	// Singleton class, because one should only ever exist

	class Application
	{
	private:
		HexMapLayout m_MapLayout;
		HexMap* m_pMap;
		sf::RenderWindow* m_pWindow;
		
		InputHandler* m_pInput;
		Renderer* m_pRenderer;
		
		Tile* m_pSelectedTile;

		Application();
		Application(const Application& other);
		Application& operator=(const Application& other) {};

		static Application* m_pInstance;
	public:
		~Application();
		static Application* getInstance();

		void loop();

		void draw(sf::RenderWindow& window);

		void setSelectedTile(Tile* pTile);
		Tile* getSelectedTile() const;

		void keyPressed(sf::Event::KeyEvent key);
		void keyReleased(sf::Event::KeyEvent key);
		void mouseMoved(sf::Event::MouseMoveEvent mouse);
		void mouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseScroll);
		void mousePressed(sf::Event::MouseButtonEvent mouseButton);
		void mouseReleased(sf::Event::MouseButtonEvent mouseButton);
	};

}