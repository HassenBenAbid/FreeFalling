#pragma once

#include "renderable2D.h"

namespace Cygnus {
	namespace graphics {
		class Sprite : public Renderable2D {
		private: 

		public:
			Sprite(float x, float y, float width, float height, maths::Vec4 const color);
			Sprite(float x, float y, float width, float height, Texture *texture);
		};
	}
}