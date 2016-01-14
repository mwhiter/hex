#pragma once

#include <SFML/Window.hpp>

namespace mandr {

	class InputHandler
	{
	public:
		InputHandler(sf::Window* pWindow);
		~InputHandler();
		InputHandler(const InputHandler& other);
		InputHandler& operator=(const InputHandler& other);

		void processEvents();

		// Keyboard Events
		void setKeyPressedCallbackFunc(void(*callback)(sf::Event::KeyEvent));
		void setKeyReleasedCallbackFunc(void(*callback)(sf::Event::KeyEvent));

		// Mouse Events
		void setMouseMovedCallback(void(*callback)(sf::Event::MouseMoveEvent));
		void setMouseButtonPressedCallback(void(*callback)(sf::Event::MouseButtonEvent));
		void setMouseButtonReleasedCallback(void(*callback)(sf::Event::MouseButtonEvent));
	private:
		sf::Window* m_pWindow;

		// Event callbacks (so a user could define their own input functions instead of me defining them)
		void (*key_press_callback_func)(sf::Event::KeyEvent);
		void (*key_release_callback_func)(sf::Event::KeyEvent);
		void (*mouse_moved_callback_func)(sf::Event::MouseMoveEvent);
		void (*mouse_button_pressed_callback_func)(sf::Event::MouseButtonEvent);
		void (*mouse_button_released_callback_func)(sf::Event::MouseButtonEvent);
	};

}