#include "FixedSprite.h"

namespace Cygnus {
	namespace graphics {

		FixedSprite::FixedSprite(float x, float y, float width,float height, maths::Vec4 const color, Shader &shader): 
			Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width,height), color), m_shader(shader) 
		{
			m_vertexArray = new VertexArray();

			GLfloat vertices[]{
				0, 0, 0,
				0, height, 0,
				width, height, 0,
				width, 0, 0
			};

			GLfloat colors[]{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_vertexArray->addBuffer(new Buffer(vertices, 12, 3), 0);
			m_vertexArray->addBuffer(new Buffer(colors, 16, 4), 1);


			GLushort indices[]{
				0,1,2,
				2,3,0
			};

			m_Ibuffer = new Ibuffer(indices, 6);
		}

		FixedSprite::~FixedSprite() {
			delete m_vertexArray;
			delete m_Ibuffer;
		}
	}
}