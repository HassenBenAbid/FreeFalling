#pragma once

#include "layer.h"
#include "../standardRenderer2D.h"

namespace Cygnus {
	namespace graphics {
		class SceneLayer : public Layer {

		public:
			SceneLayer(Shader* shader);
			~SceneLayer();
		};
	}
}