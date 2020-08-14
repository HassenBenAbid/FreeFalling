#include "layer.h"

namespace Cygnus {
	namespace graphics {

		Layer::Layer() {

		}

		Layer::Layer(Renderer2D *renderer, Shader *shader, maths::Mat4 projectionMatrix) : m_renderer(renderer), m_shader(shader), m_projectionMatrix(projectionMatrix) {
			m_shader->enable();
			m_shader->setUniformMat4("pr_matrix", m_projectionMatrix);
			m_shader->disable();
		}

		Layer::~Layer() {
			delete m_shader;
			delete m_renderer;

			for (int i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}
		
		void Layer::add(Renderable2D *renderable) {
			m_renderables.push_back(renderable);
		}

		void Layer::draw() {
			m_shader->enable();

			m_renderer->begin();
			for (Renderable2D const *renderable : m_renderables) {
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);
				renderable->submit(m_renderer);
			}
			m_renderer->end();

			m_renderer->flush();
		}
	}
}