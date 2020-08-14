#pragma once

#include <GL/glew.h>

namespace Cygnus {
	namespace graphics {
	
		class Ibuffer {
		private:
			GLuint m_IbufferID;
			GLuint m_count;
		public:

			Ibuffer(GLushort *data, GLsizei count);
			~Ibuffer();

			void bind() const;
			void unbind() const;

			GLuint getCount() const;
		};
	}
}