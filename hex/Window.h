#pragma once

#include <GLFW/glfw3.h>

namespace mandr {

	class Window {
	private:
		GLFWwindow* m_Window;
		int m_Width;
		int m_Height;
		const char* m_Title;
	public:
		Window(int width, int height, const char* title, bool fullscreen);

		int getWidth() const;
		int getHeight() const;
	};

}