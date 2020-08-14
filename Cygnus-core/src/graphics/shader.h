#pragma once

#include "../utils/filesU.h"
#include "../maths/maths.h"
#include <GL/glew.h>
#include <vector>

namespace Cygnus {
	namespace graphics {

		class Shader {

		private: 
			GLuint shaderID;
			const char *m_vertexPath, *m_fragmentPath;

			GLuint load();
			GLint getUniformLocation(GLchar const *name);
		public:
			Shader(char const *vertexPath, char const *fragmentPath);
			~Shader();


			void enable() const;
			void disable() const;

			void setUniform1f(GLchar const *name, float f);
			void setUniform1fv(GLchar const *name, float* f, int count);
			void setUniform1i(GLchar const *name, int i);
			void setUniform1iv(GLchar const *name, int* i, int count);
			void setUniform2f(GLchar const *name, maths::Vec2 const &v);
			void setUniform3f(GLchar const *name, maths::Vec3 const &v);
			void setUniform4f(GLchar const *name, maths::Vec4 const &v);
			void setUniformMat4(GLchar const *name, maths::Mat4 const &m);

		};
	}
}