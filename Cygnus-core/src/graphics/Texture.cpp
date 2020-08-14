#include "Texture.h"
#include <iostream>

namespace Cygnus {
	namespace graphics {
		Texture::Texture(std::string const &filename) : m_filename(filename) {
			m_ID = load();
		}

		Texture::~Texture() {

		}

		GLuint Texture::load() {
			BYTE *pixels = loadImage(m_filename.c_str(), m_width, m_height);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			return result;
		}

		void Texture::bind() const {
			glBindTexture(GL_TEXTURE_2D, m_ID);
		}

		void Texture::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}