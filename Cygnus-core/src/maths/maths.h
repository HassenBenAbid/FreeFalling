#pragma once

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat4.h"


namespace Cygnus {
	namespace maths {
		inline float toRadians(float degree) {

			return float((degree*M_PI) / 180.0f);
		}

		template<typename T> inline int sign(T n) {
			return (n < T(0)) ? -1 : 1;
		}

		inline float lerp(float a, float b, float t) {
			return (a * (1.0f - t)) + (b * t);
		}
	}
}
