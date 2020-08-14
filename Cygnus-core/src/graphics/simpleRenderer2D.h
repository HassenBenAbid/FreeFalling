#pragma once

#include "renderer2D.h"
#include "FixedSprite.h"
#include <deque>

namespace Cygnus {
	namespace graphics {
		class SimpleRenderer2D : public Renderer2D {
		private:
			std::deque<const FixedSprite*> m_renderableQueue;

		public:
			void submit(Renderable2D const *renderable) override;
			void flush() override;
		};
	}
}