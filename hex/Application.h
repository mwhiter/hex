#pragma once

#include <iostream>
#include "Map.h"
#include "InputHandler.h"
#include <SFML/Graphics.hpp>

namespace mandr {

	// A instance of the application
	// Singleton class, because one should only ever exist

	class Application
	{
	private:
		HexMapLayout m_MapLayout;
		HexMap* m_pMap;
		InputHandler* m_pInput;
		sf::RenderWindow* m_pWindow;

		Application();
		Application(const Application& other);
		Application& operator=(const Application& other) {};

		void draw();

		static Application* m_pInstance;
	public:
		~Application();
		static Application* getInstance();

		void loop();

		void keyPressed(sf::Event::KeyEvent key);
		void keyReleased(sf::Event::KeyEvent key);
		void mouseMoved(sf::Event::MouseMoveEvent key);
		void mousePressed(sf::Event::MouseButtonEvent key);
		void mouseReleased(sf::Event::MouseButtonEvent key);
	};

}