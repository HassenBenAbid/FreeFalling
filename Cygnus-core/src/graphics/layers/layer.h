#pragma once 

#include "../renderer2D.h"
#include "../renderable2D.h"

#include <vector>

namespace Cygnus {
	namespace graphics {

		class Layer {
		protected:
			Renderer2D *m_renderer;
			std::vector<Renderable2D*> m_renderables;
			Shader *m_shader;
			maths::Mat4 m_projectionMatrix;
		protected:
			Layer();
			Layer(Renderer2D *renderer, Shader *shader, maths::Mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D *renderable);
			virtual void draw();

		};
	}
}