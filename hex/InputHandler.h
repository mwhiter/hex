#pragma once

#include <SFML/Window.hpp>

namespace mandr {

	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();
		InputHandler(const InputHandler& other);
		InputHandler& operator=(const InputHandler& other);

		void processEvents(sf::Window& window);

		// Keyboard Events
		void setKeyPressedCallbackFunc(void(*callback)(sf::Event::KeyEvent));
		void setKeyReleasedCallbackFunc(void(*callback)(sf::Event::KeyEvent));

		// Mouse Events
		void setMouseMovedCallbackFunc(void(*callback)(sf::Event::MouseMoveEvent));
		void setMouseButtonPressedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent));
		void setMouseButtonReleasedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent));

		sf::Vector2i getMouseDraggedOffset() const;
		bool IsMouseBeingDragged() const;
	private:
		bool m_MouseBeingDragged;
		sf::Vector2i m_LastMousePosition;
		sf::Vector2i m_NewMousePosition;

		// Event callbacks (so a user could define their own input functions instead of me defining them)
		void (*key_press_callback_func)(sf::Event::KeyEvent);
		void (*key_release_callback_func)(sf::Event::KeyEvent);
		void (*mouse_moved_callback_func)(sf::Event::MouseMoveEvent);
		void (*mouse_button_pressed_callback_func)(sf::Event::MouseButtonEvent);
		void (*mouse_button_released_callback_func)(sf::Event::MouseButtonEvent);
	};

}