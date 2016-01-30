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
		void setMouseWheelScrollCallbackFunc(void(*callback)(sf::Event::MouseWheelScrollEvent));
		void setMouseButtonPressedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent));
		void setMouseButtonReleasedCallbackFunc(void(*callback)(sf::Event::MouseButtonEvent));

		/* Returns the distance between the mouse start and stop
		@return: double The distance from the start of the mouse drag to the stop
		**/
		double getMouseDraggedTotalDistance() const;

		/* Returns the difference between the last mouse position and the new mouse position if the mouse is being dragged
		@return: sf::Vector2i The offset vector of the new position from the old position
		**/
		sf::Vector2i getMouseDraggedOffset() const;
		
		/* Returns the difference between the last mouse position and the new mouse position if the mouse is being dragged
		@return: sf::Mouse::Button The button that is being dragged, or nullptr if no button
		**/
		sf::Mouse::Button* getMouseDraggedButton() const;

		/* Is the mouse currently being dragged?
		 @return: bool True if the mouse is currently being dragged
		**/
		bool IsMouseBeingDragged() const;
		
		/* Was the mouse just dragged when the button was released?
		 @return: bool True if the mouse was just dragged
		*/
		bool WasMouseDragged() const;
	private:
		void reset();

		void StartDrag(sf::Event::MouseButtonEvent& mouse);
		void StopDrag(sf::Event::MouseButtonEvent& mouse);

		sf::Mouse::Button* m_Dragged;
		bool m_WasDragged;

		sf::Vector2i m_MouseStartDrag;
		sf::Vector2i m_MouseEndDrag;

		sf::Vector2i m_LastMousePosition;
		sf::Vector2i m_NewMousePosition;

		void (*key_press_callback_func)(sf::Event::KeyEvent);
		void (*key_release_callback_func)(sf::Event::KeyEvent);
		void (*mouse_moved_callback_func)(sf::Event::MouseMoveEvent);
		void (*mouse_wheel_scroll_callback_func)(sf::Event::MouseWheelScrollEvent);
		void (*mouse_button_pressed_callback_func)(sf::Event::MouseButtonEvent);
		void (*mouse_button_released_callback_func)(sf::Event::MouseButtonEvent);
	};

}