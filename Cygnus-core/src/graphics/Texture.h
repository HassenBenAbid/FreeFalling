#pragma once

#include "../utils/LoadImage.h"
#include <string>

namespace Cygnus {
	namespace graphics {
		class Texture {
		private:
			std::string const m_filename;
			GLuint m_ID;
			GLsizei m_width, m_height;
			 
			GLuint load();
		public:
			Texture(std::string const &filename);
			~Texture();

			void bind() const;
			void unbind() const;

			inline unsigned int const getID() { return m_ID; }
		};
	}
}
