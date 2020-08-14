#pragma once

#include "Ibuffer.h"

namespace Cygnus {
	namespace graphics {
		Ibuffer::Ibuffer(GLushort *data, GLsizei count): m_count(count) {

			glGenBuffers(1, &m_IbufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IbufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		Ibuffer::~Ibuffer() {
			glDeleteBuffers(1, &m_IbufferID);
		}

		void Ibuffer::bind() const {
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IbufferID);
		}

		void Ibuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		GLuint Ibuffer::getCount() const {
			return m_count;
		}
	}
}