#include "Application.h"

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
		m_pWindow(new sf::RenderWindow(sf::VideoMode(1600, 900), "Hex Test", sf::Style::Close)),
		m_MapLayout(HexMapLayout(HexMap::Orientation_Horizontal, sf::Vector2f(512, 512), sf::Vector2f(0, 0))),
		m_pSelectedTile(nullptr)
	{
		m_pMap = new HexMap(m_MapLayout, 120, 80);

		m_pRenderer = new Renderer();
		m_pRenderer->SetRenderCallbackFunc(draw_wrapper);

		m_pInput = new InputHandler();
		m_pInput->setKeyPressedCallbackFunc(key_pressed_wrapper);
		m_pInput->setKeyReleasedCallbackFunc(key_released_wrapper);
		m_pInput->setMouseMovedCallbackFunc(mouse_moved_wrapper);
		m_pInput->setMouseWheelScrollCallbackFunc(mouse_wheel_scroll_wrapper);
		m_pInput->setMouseButtonPressedCallbackFunc(mouse_pressed_wrapper);
		m_pInput->setMouseButtonReleasedCallbackFunc(mouse_released_wrapper);
	}


	Application::~Application() {
		delete m_pWindow;
		delete m_pInput;
	}

	Application::Application(const Application& other) : m_pInput(other.m_pInput), m_pWindow(other.m_pWindow), m_MapLayout(other.m_MapLayout), m_pMap(other.m_pMap) {
	}

	Application* Application::getInstance()
	{
		// Set up application if it doesn't exist already
		if (!m_pInstance) {
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

	void Application::keyPressed(sf::Event::KeyEvent key) {
	}

	void Application::keyReleased(sf::Event::KeyEvent key) {
	}

	void Application::mouseMoved(sf::Event::MouseMoveEvent mouse) {
		// Control the map move speed
		float dragSpeed = 10.0f;	// this would be a programmer constant
		float dragMod = 2.0f;		// this would be a user setting (from 0.5f - 2.0f)

		// Get the amount we've dragged
		sf::Vector2i mouseDragOffset = m_pInput->getMouseDraggedOffset();
		m_pRenderer->getView().move(-mouseDragOffset.x * dragSpeed * dragMod, -mouseDragOffset.y * dragSpeed * dragMod);
	}

	void Application::mouseWheelScrolled(sf::Event::MouseWheelScrollEvent mouseScroll) {
		sf::View* view = &m_pRenderer->getView();
		view->zoom(mouseScroll.delta > 0 ? 0.9f : 1.1f);
	}

	void Application::mousePressed(sf::Event::MouseButtonEvent button) {
	}

	void Application::mouseReleased(sf::Event::MouseButtonEvent button) {
		if (m_pInput->WasMouseDragged()) return;
		
		// Convert mouse pixel position to world coords
		sf::Vector2f worldPos = m_pWindow->mapPixelToCoords(sf::Mouse::getPosition(*m_pWindow));

		// Use new world coords for selecting a tile we're hovering over
		Hex hover = Hex::pixel_to_hex(m_pMap->getLayout(), worldPos);

		// Select the tile
		setSelectedTile(m_pMap->getTile(hover));
		Tile* pSelected = getSelectedTile();
		if (pSelected != nullptr)
			std::cout << pSelected->getX() << " " << pSelected->getY() << std::endl;
	}

	void Application::setSelectedTile(Tile* pTile) {
		m_pSelectedTile = pTile;
	}
	
	Tile* Application::getSelectedTile() const {
		return m_pSelectedTile;
	}

}