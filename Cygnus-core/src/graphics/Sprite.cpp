#include "Sprite.h"

namespace Cygnus {
	namespace graphics {
		Sprite::Sprite(float x, float y, float width, float height, maths::Vec4 const color) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, height), color) {

		}


		Sprite::Sprite(float x, float y, float width, float height, Texture *texture) : Renderable2D(maths::Vec3(x, y, 0), maths::Vec2(width, height), maths::Vec4(1.0f, 0.0f, 1.0f, 1.0f)) {
			m_texture = texture;
		}
	}
}