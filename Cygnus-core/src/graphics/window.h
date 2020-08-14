#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace Cygnus {
	namespace graphics {
	#define max_keys 1024
	#define max_buttons 32 
		
		void windowResize(GLFWwindow *window, int width, int height);

		class Window {
		private:
			int m_width, m_height;
			char const *m_name;
			GLFWwindow *m_window;
			bool m_closed;
			float m_lastFrame, m_deltaTime;

			bool m_keys[max_keys], m_buttons[max_buttons];
			double m_x, m_y;
		public:
			Window(char const *name, int width, int height);
			~Window();
			bool closed() const;
			void clear() const;
			void update();

			 bool keyPressed(unsigned int keyCode) const;
			 bool buttonPressed(unsigned int buttonCode) const;
			 void getMousePosition(double &x, double &y) const;
			 void closeWindow() const;
			 inline float getDeltaTime() const { return m_deltaTime; };
			 inline GLFWwindow *getGLFWWindow() const { return m_window; };
		private:
			float calculateDeltaTime();
			bool init();
			friend static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void buttonCallback(GLFWwindow *window, int button, int action, int mods);
			friend static void mousePositionCallback(GLFWwindow *window, double x, double y);


		};

	}
}
