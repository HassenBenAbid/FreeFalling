#pragma once

//#include "renderable2D.h"
#include <gl/glew.h>
#include <vector>
#include "../maths/maths.h"

namespace Cygnus {
	namespace graphics {

		class Renderable2D;
		class Renderer2D {
		protected:
			std::vector<maths::Mat4> m_transformationStack;
			maths::Mat4 const *m_transformationStackBack;

			Renderer2D() {
				m_transformationStack.push_back(maths::Mat4::identity());
				m_transformationStackBack = &m_transformationStack.back();
			}
		public:
			void push(const maths::Mat4 &matrix, bool override = false) {
				if (override) {
					m_transformationStack.push_back(matrix);
				}
				else {
					m_transformationStack.push_back(m_transformationStack.back() * matrix);
				}

				m_transformationStackBack = &m_transformationStack.back();
			}
			void pop() {
				if (m_transformationStack.size() > 1) {
					m_transformationStack.pop_back();
					m_transformationStackBack = &m_transformationStack.back();
				}
			}

			virtual void begin() {};
			virtual void end() {};
			virtual void submit(Renderable2D const *renderable) = 0;
			virtual void flush() = 0;
		};
	}
}