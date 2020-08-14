#pragma once 

#include "renderer2D.h"
#include "renderable2D.h"
#include <cstddef>

namespace Cygnus {
	namespace graphics {

	#define RENDERER_MAX_SPRITES 10000
	#define RENDERER_VERTEX_SIZE sizeof(VertexData)
	#define RENDERER_SPRITE_SIZE RENDERER_VERTEX_SIZE * 4
	#define RENDERER_BUFFER_SIZE RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
	#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6

	#define SHADER_VERTEX_INDEX 0 
	#define SHADER_TEXCOORD_INDEX 1 
	#define SHADER_TEXID_INDEX 2 
	#define SHADER_COLOR_INDEX 3 
 
		class StandardRenderer2D : public Renderer2D {

		private:
			VertexData *m_bufferMap;
			GLuint m_VAO, m_VBO;
			Ibuffer *m_IBO;
			GLsizei m_IndexCount;
			std::vector<GLuint> m_texSlots;

			void init();
		public:
			StandardRenderer2D();
			~StandardRenderer2D();

			void begin() override;
			void submit(Renderable2D const *renderable) override;
			void end() override;
			void flush() override;

			

		};
	}
}