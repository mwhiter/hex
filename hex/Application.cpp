#include "PCH.h"

// Global wrappers to singleton Application functions

void key_pressed_wrapper(sf::Event::KeyEvent key) {
	mandr::Application::getInstance()->keyPressed(key);
}

void key_released_wrapper(sf::Event::KeyEvent key) {
	mandr::Application::getInstance()->keyReleased(key);
}

void mouse_moved_wrapper(sf::Event::MouseMoveEvent mouse) {
	mandr::Application::getInstance()->mouseMoved(mouse);
}

void mouse_pressed_wrapper(sf::Event::MouseButtonEvent mouseButton) {
	mandr::Application::getInstance()->mousePressed(mouseButton);
}

void mouse_released_wrapper(sf::Event::MouseButtonEvent mouseButton) {
	mandr::Application::getInstance()->mouseReleased(mouseButton);
}

void mouse_wheel_scroll_wrapper(sf::Event::MouseWheelScrollEvent mouseScroll) {
	mandr::Application::getInstance()->mouseWheelScrolled(mouseScroll);
}

void draw_wrapper(sf::RenderWindow& window) {
	mandr::Application::getInstance()->draw(window);
}

namespace mandr {

	// Static declaration of class to ensure it exists
	Application* Application::m_pInstance = nullptr;

	Application::Application() :
		m_MapLayout(HexMapLayout(HexMap::Orientation_Horizontal, sf::Vector2f(512, 512), sf::Vector2f(0, 0))),
		m_pSelectedTile(nullptr),
		m_Zoom(0),
		m_DraggedEnoughForMovement(false)
	{
	}


	Application::~Application() {
		delete m_pWindow;
		delete m_pInput;
		delete m_pRenderer;
	}

	void Application::init() {
		m_pWindow = new sf::RenderWindow(sf::VideoMode(1600, 900), "Hex Test", sf::Style::Close);
		
		m_pRenderer = new Renderer();
		m_pRenderer->SetRenderCallbackFunc(draw_wrapper);

		m_pInput = new InputHandler();
		m_pInput->setKeyPressedCallbackFunc(key_pressed_wrapper);
		m_pInput->setKeyReleasedCallbackFunc(key_released_wrapper);
		m_pInput->setMouseMovedCallbackFunc(mouse_moved_wrapper);
		m_pInput->setMouseWheelScrollCallbackFunc(mouse_wheel_scroll_wrapper);
		m_pInput->setMouseButtonPressedCallbackFunc(mouse_pressed_wrapper);
		m_pInput->setMouseButtonReleasedCallbackFunc(mouse_released_wrapper);
		
		assert(loadTextures());
		assert(loadFonts());

		m_TerrainInfos[0] = TerrainInfo("TERRAIN_GRASS", 1, 0, TERRIAN_TYPE_GRASS);
		m_TerrainInfos[1] = TerrainInfo("TERRAIN_PLAINS", 1, 1, TERRIAN_TYPE_GRASS);

		loadMap();

		loop();
	}

	// Load textures
	bool Application::loadTextures() {
		bool success = true;
		success = success && m_Textures[0].loadFromFile("textures/grass512.png");
		success = success && m_Textures[1].loadFromFile("textures/plains512.png");
		success = success && m_Textures[2].loadFromFile("textures/ui/ui_hex_highlight_red.png");
		return success;
	}

	bool Application::loadFonts() {
		bool success = true;
		success = success && m_Fonts[0].loadFromFile("fonts/arial.ttf");
		return success;
	}

	void Application::loadMap() {
		m_pMap = new HexMap(m_MapLayout, 16, 16);
		m_pMap->load();
	}

	Application::Application(const Application& other) : m_pInput(other.m_pInput), m_pWindow(other.m_pWindow), m_MapLayout(other.m_MapLayout), m_pMap(other.m_pMap) {
	}

	Application* Application::getInstance()
	{
		// Set up application if it doesn't exist already
		if (m_pInstance == nullptr) {
			m_pInstance = new Application();
		}

		return m_pInstance;
	}

	void Application::loop() {
		while (m_pWindow->isOpen()) {
			m_pInput->processEvents(*m_pWindow);
			m_pRenderer->draw(*m_pWindow);
		}
	}

	void Application::draw(sf::RenderWindow& window) {
		window.clear();
		m_pMap->draw(window);
		window.display();
	}

	sf::Texture Application::getTexture(int i) const {
		return m_Textures[i];
	}

	sf::Font Application::getFont(int i) const {
		return m_Fonts[i];
	}

	void Application::keyPressed(sf::Event::KeyEvent key) {
	}

	void Application::keyReleased(sf::Event::KeyEvent key) {
	}

	void Application::mouseMoved(sf::Event::MouseMoveEvent mouse) {
		// We need to drag a certain amount before we have dragged enough for movement (once we have, keep dragging until mouse is released)
		double mouseDragTotal = m_pInput->getMouseDraggedTotalDistance();
		if (!m_DraggedEnoughForMovement && abs(mouseDragTotal) > 24.0)
			m_DraggedEnoughForMovement = true;
		
		// Control the map move speed
		float dragSpeed = 10.0f;	// this would be a programmer constant
		float dragMod = 2.0f;		// this would be a user setting (from 0.5f - 2.0f)
		
									// Start dragging - get amount we've dragged this frame
		if (m_DraggedEnoughForMovement) {
			sf::Vector2i mouseDragOffset = m_pInput->getMouseDraggedOffset();
			m_pRenderer->getView().move(-mouseDragOffset.x * dragSpeed * dragMod, -mouseDragOffset.y * dragSpeed * dragMod);
		}
	}

	void Application::mouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseScroll) {
		bool changeZoom = mouseScroll.delta > 0 ? (m_Zoom < 5) : (m_Zoom > -10);
		if (changeZoom) {
			m_Zoom += mouseScroll.delta > 0 ? 1 : -1;
			sf::View* view = &m_pRenderer->getView();
			view->zoom(mouseScroll.delta > 0 ? 0.9f : 1.1f);
		}
	}

	void Application::mousePressed(sf::Event::MouseButtonEvent button) {
	}

	void Application::mouseReleased(sf::Event::MouseButtonEvent button) {
		// If mouse was dragged, reset movement
		if (m_DraggedEnoughForMovement && m_pInput->WasMouseDragged()) {
			m_DraggedEnoughForMovement = false;
		}
		// If mouse was not dragged, select a tile
		else {
			// Convert mouse pixel position to world coords
			sf::Vector2f worldPos = m_pWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_pWindow));

			// Use new world coords for selecting a tile we're hovering over
			Hex hover = Hex::pixel_to_hex(m_pMap->getLayout(), worldPos);

			// Select the tile
			setSelectedTile(m_pMap->getTile(hover));
		}
	}

	void Application::setSelectedTile(Tile* pTile) {
		m_pSelectedTile = pTile;
	}
	
	Tile* Application::getSelectedTile() const {
		return m_pSelectedTile;
	}

}