#include "simpleRenderer2D.h"
#include "renderable2D.h"

namespace Cygnus {
	namespace graphics {
		void SimpleRenderer2D::submit(Renderable2D const *renderable) {
			m_renderableQueue.push_back((FixedSprite *)renderable);
		}

		void SimpleRenderer2D::flush() {
			while (!m_renderableQueue.empty()) {
				FixedSprite const *renderable = m_renderableQueue.front();

				renderable->getVertexArray()->bind();
				renderable->getIbuffer()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", maths::Mat4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIbuffer()->getCount(), GL_UNSIGNED_SHORT, 0);

				renderable->getIbuffer()->unbind();
				renderable->getVertexArray()->unbind();

				m_renderableQueue.pop_front();
			}
		}
	}
}