#include "SceneLayer.h"

namespace Cygnus {
	namespace graphics {

		SceneLayer::SceneLayer(Shader *shader) : Layer(new StandardRenderer2D(),shader, maths::Mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)) {

		}

		SceneLayer::~SceneLayer() {

		}
	}
}