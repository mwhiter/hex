#include "InputHandler.h"

namespace mandr {

	InputHandler::InputHandler(sf::Window* pWindow) :
		m_pWindow(pWindow),
		key_press_callback_func(NULL),
		key_release_callback_func(NULL),
		mouse_moved_callback_func(NULL),
		mouse_button_pressed_callback_func(NULL),
		mouse_button_released_callback_func(NULL)
	{
	}


	InputHandler::~InputHandler() {
	}


	InputHandler::InputHandler(const InputHandler& other) :
		m_pWindow(other.m_pWindow),
		key_press_callback_func(other.key_press_callback_func),
		key_release_callback_func(other.key_release_callback_func),
		mouse_moved_callback_func(other.mouse_moved_callback_func),
		mouse_button_pressed_callback_func(other.mouse_button_pressed_callback_func),
		mouse_button_released_callback_func(other.mouse_button_released_callback_func)
	{
	}

	InputHandler& InputHandler::operator=(const InputHandler& other) {
		m_pWindow = other.m_pWindow;
		key_press_callback_func = other.key_press_callback_func;
		key_release_callback_func = other.key_release_callback_func;
		mouse_moved_callback_func = other.mouse_moved_callback_func;
		mouse_button_pressed_callback_func = other.mouse_button_pressed_callback_func;
		mouse_button_released_callback_func = other.mouse_button_released_callback_func;
		return *this;
	}

	void InputHandler::processEvents() {
		sf::Event event;
		while (m_pWindow->pollEvent(event)) {
			switch (event.type) {
				case sf::Event::KeyPressed:
					if (key_press_callback_func != NULL)
						key_press_callback_func(event.key);
					break;
				case sf::Event::KeyReleased:
					if (key_release_callback_func != NULL)
						key_release_callback_func(event.key);
					break;
				case sf::Event::MouseMoved:
					if (mouse_moved_callback_func != NULL)
						mouse_moved_callback_func(event.mouseMove);
					break;
				case sf::Event::MouseButtonPressed:
					if (mouse_button_pressed_callback_func != NULL)
						mouse_button_pressed_callback_func(event.mouseButton);
					break;
				case sf::Event::MouseButtonReleased:
					if (mouse_button_released_callback_func != NULL)
						mouse_button_released_callback_func(event.mouseButton);
					break;
				case sf::Event::Closed:
					m_pWindow->close();
					break;
			}
		}
	}

	void InputHandler::setKeyPressedCallbackFunc(void(*callback)(sf::Event::KeyEvent)) {
		key_press_callback_func = callback;
	}

	void InputHandler::setKeyReleasedCallbackFunc(void(*callback)(sf::Event::KeyEvent)) {
		key_release_callback_func = callback;
	}

	void InputHandler::setMouseMovedCallback(void(*callback)(sf::Event::MouseMoveEvent)) {
		mouse_moved_callback_func = callback;
	}

	void InputHandler::setMouseButtonPressedCallback(void(*callback)(sf::Event::MouseButtonEvent)) {
		mouse_button_pressed_callback_func = callback;
	}

	void InputHandler::setMouseButtonReleasedCallback(void(*callback)(sf::Event::MouseButtonEvent)) {
		mouse_button_released_callback_func = callback;
	}

}