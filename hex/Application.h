#pragma once

#include "Map.h"
#include "Infos.h"
#include "InputHandler.h"
#include "Renderer.h"
#include <SFML/Graphics.hpp>

namespace mandr {
	// A instance of the application
	// Singleton class, because one should only ever exist

#define MAX_TEXTURES 100
#define MAX_FONTS 40

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

		int m_Zoom;

		bool m_DraggedEnoughForMovement;

		sf::Texture m_Textures[MAX_TEXTURES];
		sf::Font m_Fonts[MAX_FONTS];
		
		static Application* m_pInstance;
	public:
		~Application();
		static Application* getInstance();

		sf::Texture getTexture(int i) const;
		sf::Font getFont(int i) const;

		TerrainInfo m_TerrainInfos[6];

		void init();
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

		inline Renderer* getRenderer() const {
			return m_pRenderer;
		}
	private:
		bool loadFonts();
		bool loadTextures();
		void loadMap();
	};

#define GAME (*Application::getInstance())
}