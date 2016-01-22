#include "PCH.h"

namespace mandr {

	Renderer::Renderer() : m_View(sf::View(sf::Vector2f(0,0), sf::Vector2f(512 * 16, 512 * 9))) {
	}


	Renderer::~Renderer() {
	}

	/////////////////////////////////////////////////
	/// \brief Construct a rectangle equal to world coordinates shown by the camera
	///
	/// This function returns a rectangle detailing the world coordinates currently in the window's current view's screen.
	/// This is useful for determining if a pixel is currently shown on the camera or not. 
	///
	/// \param window The window to check
	/// \param padding A % of the screen's borders to check. If <100, then you check less of the screen. If >100, then you extend your check outside the screen's borders
	///
	/// \return The construct float rectangle
	/////////////////////////////////////////////////
	sf::FloatRect Renderer::getWindowScreenWorldBounds(sf::RenderWindow& window, float padding) const {
		sf::Vector2f world_topLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
		sf::Vector2f world_bottomRight = window.mapPixelToCoords(sf::Vector2i(window.getSize().x, window.getSize().y));

		sf::Vector2f world_size = world_bottomRight - world_topLeft;
		sf::Vector2f new_size = world_size * padding;

		world_topLeft -= (new_size - world_size) * 0.5f;

		return sf::FloatRect(world_topLeft, new_size);
	}

	void Renderer::draw(sf::RenderWindow& window) {
		window.setView(m_View);
		draw_func(window);
	}

	void Renderer::SetRenderCallbackFunc(void(*callback)(sf::RenderWindow&)) {
		draw_func = callback;
	}

	sf::View& Renderer::getView() {
		return m_View;
	}
}