#pragma once

#include <GL/glew.h>

namespace Cygnus {
	namespace graphics {
		
		class Buffer {
		private: 
			GLuint m_bufferID;
			GLuint m_componentCount;
		public: 
			Buffer(GLfloat *data, GLsizei count, GLuint componentCount);
			~Buffer();

			void bind() const;
			void unbind() const;

			GLuint getComponentCount() const;
		};
	}
}