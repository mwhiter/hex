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

namespace mandr {

	// Static declaration of class to ensure it exists
	Application* Application::m_pInstance = NULL;


	Application::Application() :
		m_pWindow(new sf::RenderWindow(sf::VideoMode(1600, 900), "Hex Test", sf::Style::Close)),
		m_MapLayout(HexMapLayout(HexMap::Orientation_Horizontal, sf::Vector2f(24, 24), sf::Vector2f(64, 64)))
	{
		m_pMap = new HexMap(m_MapLayout, 20, 20);

		m_pInput = new InputHandler(m_pWindow);
		m_pInput->setKeyPressedCallbackFunc(key_pressed_wrapper);
		m_pInput->setKeyReleasedCallbackFunc(key_released_wrapper);
		m_pInput->setMouseMovedCallback(mouse_moved_wrapper);
		m_pInput->setMouseButtonPressedCallback(mouse_pressed_wrapper);
		m_pInput->setMouseButtonReleasedCallback(mouse_released_wrapper);
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
			m_pInput->processEvents();
			draw();
		}
	}

	void Application::draw() {
		m_pWindow->clear();
		m_pMap->draw(*m_pWindow);
		m_pWindow->display();
	}

	void Application::keyPressed(sf::Event::KeyEvent key) {
		std::cout << "Key Pressed: " << key.code << std::endl;
	}

	void Application::keyReleased(sf::Event::KeyEvent key) {
		std::cout << "Key Released: " << key.code << std::endl;
	}

	void Application::mouseMoved(sf::Event::MouseMoveEvent mouse) {
		std::cout << mouse.x << " " << mouse.y << std::endl;
	}

	void Application::mousePressed(sf::Event::MouseButtonEvent button) {
		std::cout << button.button << " " << button.x << " " << button.y << std::endl;
	}

	void Application::mouseReleased(sf::Event::MouseButtonEvent button) {
		std::cout << button.button << " " << button.x << " " << button.y << std::endl;
	}

}