#include "InputHandler.h"

namespace mandr {

	InputHandler::InputHandler() :
		key_press_callback_func(NULL),
		key_release_callback_func(NULL),
		mouse_moved_callback_func(NULL),
		mouse_button_pressed_callback_func(NULL),
		mouse_button_released_callback_func(NULL),
		m_MouseBeingDragged(false)
	{
	}


	InputHandler::~InputHandler() {
	}


	InputHandler::InputHandler(const InputHandler& other) :
		key_press_callback_func(other.key_press_callback_func),
		key_release_callback_func(other.key_release_callback_func),
		mouse_moved_callback_func(other.mouse_moved_callback_func),
		mouse_button_pressed_callback_func(other.mouse_button_pressed_callback_func),
		mouse_button_released_callback_func(other.mouse_button_released_callback_func)
	{
	}

	InputHandler& InputHandler::operator=(const InputHandler& other) {
		key_press_callback_func = other.key_press_callback_func;
		key_release_callback_func = other.key_release_callback_func;
		mouse_moved_callback_func = other.mouse_moved_callback_func;
		mouse_button_pressed_callback_func = other.mouse_button_pressed_callback_func;
		mouse_button_released_callback_func = other.mouse_button_released_callback_func;
		return *this;
	}

	void InputHandler::processEvents(sf::Window& window) {
		sf::Event event;
		while (window.pollEvent(event)) {
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
					m_MouseBeingDragged = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
					m_NewMousePosition.x = event.mouseMove.x;
					m_NewMousePosition.y = event.mouseMove.y;

					if (mouse_moved_callback_func != NULL)
						mouse_moved_callback_func(event.mouseMove);

					m_LastMousePosition.x = event.mouseMove.x;
					m_LastMousePosition.y = event.mouseMove.y;
					break;
				case sf::Event::MouseWheelScrolled:
					if (mouse_wheel_scroll_callback_func != NULL)
						mouse_wheel_scroll_callback_func(event.mouseWheelScroll);
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
					window.close();
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

	void InputHandler::setMouseMovedCallbackFunc(void(*callback)(sf::Event::MouseMoveEvent)) {
		mouse_moved_callback_func = callback;
	}

	void InputHandler::setMouseWheelScrollCallbackFunc(void(*callback)(sf::Event::MouseWheelScrollEvent)) {
		mouse_wheel_scroll_callback_func = callback;
	}

	void InputHandler::setMouseButtonPressedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent)) {
		mouse_button_pressed_callback_func = callback;
	}

	void InputHandler::setMouseButtonReleasedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent)) {
		mouse_button_released_callback_func = callback;
	}

	sf::Vector2i InputHandler::getMouseDraggedOffset() const
	{
		if (!IsMouseBeingDragged())
			return sf::Vector2i(0, 0);
		return sf::Vector2i(m_NewMousePosition.x - m_LastMousePosition.x, m_NewMousePosition.y - m_LastMousePosition.y);
	}

	bool InputHandler::IsMouseBeingDragged() const {
		return m_MouseBeingDragged;
	}

}