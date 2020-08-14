#pragma once

#include <GL/glew.h>
#include <vector>

#include "buffers/buffer.h"

namespace Cygnus {
	namespace graphics {
		class VertexArray {
		private: 
			GLuint m_vArrayID;
			std::vector<Buffer*> m_buffers;
		public:

			VertexArray();
			~VertexArray();

			void bind() const;
			void unbind() const;
			void addBuffer(Buffer *b, GLuint index);
		};
	}
}