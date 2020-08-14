#pragma once

//#include "../renderer2D.h"
#include "../renderable2D.h"

namespace Cygnus {
	namespace graphics {
		class Group : public Renderable2D {
		private:
			std::vector<Renderable2D*> m_renderables;
			maths::Mat4 m_transformationMatrix;
		public:
			Group(maths::Mat4 const matrix);
			~Group();
			void submit(Renderer2D *renderer) const override;
			void add(Renderable2D *renderable);

		};
	}
}