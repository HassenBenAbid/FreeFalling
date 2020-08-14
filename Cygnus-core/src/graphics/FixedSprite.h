#pragma once

#include "renderable2D.h"

namespace Cygnus {
	namespace graphics {

		class FixedSprite : public Renderable2D {
		private:

			VertexArray *m_vertexArray;
			Ibuffer *m_Ibuffer;
			Shader &m_shader;
		public:
			FixedSprite(float x, float y, float width, float height, maths::Vec4 const color, Shader &shader);
			~FixedSprite();

			inline const VertexArray *getVertexArray() const { return m_vertexArray; }
			inline const Ibuffer *getIbuffer() const { return m_Ibuffer; }

			inline Shader &getShader() const { return m_shader; }
		};
	}
}