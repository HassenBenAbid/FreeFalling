#include "window.h"

namespace Cygnus {
	namespace graphics {

		Window::Window(char const *name, int width, int height) : m_name(name), m_width(width), m_height(height) {
			if (!init())
				glfwTerminate();

			for(int i=0; i<max_keys; i++){
				m_keys[i] = false;
			}

			for (int i = 0; i < max_buttons; i++) {
				m_buttons[i] = false;
			}
			
			m_lastFrame = 0;
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
		}

		Window::~Window() {
			glfwTerminate();
		}

		void keyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_keys[key] = (action != GLFW_RELEASE);
		}

		void buttonCallback(GLFWwindow * window, int button, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_buttons[button] = (action != GLFW_RELEASE);
		}

		void mousePositionCallback(GLFWwindow *window, double x, double y) {
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->m_x = x;
			win->m_y = y;

		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}
			m_window = glfwCreateWindow(m_width, m_height, m_name, NULL, NULL);
			if (!m_window) {
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, windowResize);
			glfwSetKeyCallback(m_window, keyCallback);
			glfwSetMouseButtonCallback(m_window, buttonCallback);
			glfwSetCursorPosCallback(m_window, mousePositionCallback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}



			return true;
		}

		bool Window::closed() const{
			return glfwWindowShouldClose(m_window);
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		float Window::calculateDeltaTime() {

			float currentFrame = (float)glfwGetTime();
			float d = currentFrame - m_lastFrame;
			m_lastFrame = currentFrame;

			return d;
		}

		void Window::update(){

			glfwPollEvents();
			
			glfwSwapBuffers(m_window);

			m_deltaTime = calculateDeltaTime();

			GLenum errors = glGetError();

			if (errors != GL_NO_ERROR)
				std::cout << "GL ERROR : " << errors << std::endl;

		}

		bool Window::keyPressed(unsigned int keyCode) const{
			if (keyCode >= max_keys)
				return false;

			return m_keys[keyCode];
		}

		bool Window::buttonPressed(unsigned int buttonCode) const{
			if (buttonCode >= max_buttons)
				return false;

			return m_buttons[buttonCode];
		}

		void Window::getMousePosition(double &x, double &y) const{
			x = m_x;
			y = m_y;
		}

		void windowResize(GLFWwindow *window, int width, int height) {
			//glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		void Window::closeWindow() const {
			glfwSetWindowShouldClose(m_window, true);
		}

} }