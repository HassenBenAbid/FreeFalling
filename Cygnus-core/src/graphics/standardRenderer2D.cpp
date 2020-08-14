#include "standardRenderer2D.h"

namespace Cygnus {
	namespace graphics {
		StandardRenderer2D::StandardRenderer2D() {
			init();
		}

		StandardRenderer2D::~StandardRenderer2D() {
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void StandardRenderer2D::init() {

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void *)0);
			glVertexAttribPointer(SHADER_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void *)(offsetof(VertexData, VertexData::texCoord)));
			glVertexAttribPointer(SHADER_TEXID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void *)(offsetof(VertexData, VertexData::texID)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void *)(offsetof(VertexData, VertexData	::color)));
			
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_TEXCOORD_INDEX);
			glEnableVertexAttribArray(SHADER_TEXID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLushort indices[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6) {
				indices[i]     = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new Ibuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		void StandardRenderer2D::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_bufferMap = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void StandardRenderer2D::submit(Renderable2D const *renderable) {

			const maths::Vec3& position = renderable->getPosition();
			const maths::Vec2& size = renderable->getSize();
			const maths::Vec4& color = renderable->getColor();
			const maths::Mat4& m_transformationMatrix = renderable->getTransformationMatrix();
			const std::vector<maths::Vec2> &texCoord = renderable->getTexCoord();
			const GLuint textureID = renderable->getTextureID();

			maths::Vec4 c = maths::Vec4(0, 0, 0, 0);
			c = color;

			float texSlot = 0;
			if (textureID > 0) {
				bool found = false;
				for (int i = 0; i < m_texSlots.size(); i++) {
					if (m_texSlots[i] == textureID) {
						texSlot = (float)i+1;
						found = true;
						break;
					}
				}

				if (!found) {
					if (m_texSlots.size() >= 32) {
						end();
						flush();
						begin();
					}
					m_texSlots.push_back(textureID);
					texSlot = (float)(m_texSlots.size() - 1);
				}
			}
			else {
				c = color;
			}

			m_bufferMap->vertex = *m_transformationStackBack * m_transformationMatrix * position;
			m_bufferMap->texCoord = texCoord[0];
			m_bufferMap->texID = texSlot;
			m_bufferMap->color = c;
			m_bufferMap++;

			m_bufferMap->vertex = *m_transformationStackBack * m_transformationMatrix * maths::Vec3(position.x, position.y + size.y, position.z);
			m_bufferMap->texCoord = texCoord[1];
			m_bufferMap->texID = texSlot;
			m_bufferMap->color = c;
			m_bufferMap++;

			m_bufferMap->vertex = *m_transformationStackBack * m_transformationMatrix * maths::Vec3(position.x + size.x, position.y + size.y, position.z);
			m_bufferMap->texCoord = texCoord[2];
			m_bufferMap->texID = texSlot;
			m_bufferMap->color = c;
			m_bufferMap++;

			m_bufferMap->vertex = *m_transformationStackBack * m_transformationMatrix * maths::Vec3(position.x + size.x, position.y, position.z);
			m_bufferMap->texCoord = texCoord[3];
			m_bufferMap->texID = texSlot;
			m_bufferMap->color = c;
			m_bufferMap++;

			m_IndexCount += 6;

		}

		void StandardRenderer2D::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void StandardRenderer2D::flush() {

			for (int i = 0; i < m_texSlots.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_texSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_SHORT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_IndexCount = 0;
		}

	}
}