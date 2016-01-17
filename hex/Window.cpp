#include "Window.h"

namespace mandr {
	Window::Window(int width, int height, const char * title, bool fullscreen) : m_Width(width), m_Height(height), m_Title(title) {
		m_Window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	}

	int Window::getWidth() const {
		return m_Width;
	}

	int Window::getHeight() const {
		return m_Height;
	}
}