#include "Group.h"

namespace Cygnus {
	namespace graphics {
		Group::Group(maths::Mat4 const matrix): m_transformationMatrix(matrix) {

		}

		Group::~Group() {
			for (Renderable2D *renderable : m_renderables) {
				delete renderable;
			}
		}

		void Group::submit(Renderer2D *renderer) const {
			
			renderer->push(m_transformationMatrix);

			for (Renderable2D *renderable : m_renderables) {
				renderable->submit(renderer);
			}

			renderer->pop();
		}

		void Group::add(Renderable2D *renderable) {
			m_renderables.push_back(renderable);
		}

	}
}