#pragma once

#include "buffers/Ibuffer.h"
#include "vertexArray.h"
#include "shader.h"	
#include "../maths/maths.h"
#include "Texture.h"

#include "renderer2D.h"

namespace Cygnus{
	namespace graphics {

		struct VertexData {
			maths::Vec3 vertex;
			maths::Vec2 texCoord;
			float texID;
			maths::Vec4 color;
		};

		class Renderable2D {
		
		private:

			void setDefaultTexCoord() {
				m_texCoord.push_back(maths::Vec2(0.0f, 0.0f));
				m_texCoord.push_back(maths::Vec2(0.0f, 1.0f));
				m_texCoord.push_back(maths::Vec2(1.0f, 1.0f));
				m_texCoord.push_back(maths::Vec2(1.0f, 0.0f));
			}

		protected:
			maths::Vec3 m_position;
			maths::Vec4 m_color;
			maths::Vec2 m_size;
			std::vector<maths::Vec2> m_texCoord;
			Texture *m_texture;
			maths::Mat4 m_transformationMatrix;

			Renderable2D() {
				setDefaultTexCoord();
				m_transformationMatrix = maths::Mat4::identity();
			};

		public: 
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 color) : m_position(position), m_color(color), m_size(size){
				setDefaultTexCoord();
				m_transformationMatrix = maths::Mat4::identity();
			}

			virtual ~Renderable2D() {}

			virtual void submit(Renderer2D *renderer) const {
				renderer->submit(this);
			};

			inline const maths::Vec3 &getPosition() const { return m_position; } 
			inline const maths::Vec4 &getColor() const { return m_color; }
			inline const maths::Vec2 &getSize() const { return m_size; }
			inline const maths::Mat4 &getTransformationMatrix() const { return m_transformationMatrix; }
			inline void setPosition(maths::Vec3 position) { m_position = position; }
			inline const std::vector<maths::Vec2>& getTexCoord() const { return m_texCoord; }
			inline void setTransformationMatrix(maths::Mat4 matrix) { m_transformationMatrix = matrix; }
			inline void moveXPosition(float Xpos) { m_position.x += Xpos; }
			inline void setXPosition(float Xpos) { m_position.x = Xpos; }
			inline void setColor(maths::Vec4 color) { m_color = color; }
			inline void setSize(maths::Vec2 size) { m_size = size; }

			inline const GLuint getTextureID() const { return m_texture == nullptr ? 0 : m_texture->getID(); };
		};


	}
}