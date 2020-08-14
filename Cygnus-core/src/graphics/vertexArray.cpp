
#include "vertexArray.h"

namespace Cygnus {
	namespace graphics {
		VertexArray::VertexArray() {

			glGenVertexArrays(1, &m_vArrayID);
			
		}

		VertexArray::~VertexArray() {

			for (int i = 0; i < m_buffers.size(); i++) {
				delete m_buffers[i];
			}
		}

		void VertexArray::addBuffer(Buffer *b, GLuint index) {
			bind();
			b->bind();

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, b->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);

			b->unbind();
			unbind();
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_vArrayID);
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
		}
	}
}