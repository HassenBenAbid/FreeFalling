#pragma once

#include <iostream>
#include "maths.h"

namespace Cygnus {
	namespace maths {
		class Vec2 {
		public:
			Vec2();
			Vec2(float x, float y);

			float norme() const;
			Vec2 normalize() const;

			float produitVec(Vec2 &v, float angle);

			Vec2 operator+=(Vec2 const &v);
			Vec2 operator-=(Vec2 const &v);
			Vec2 operator*=(Vec2 const &v);
			Vec2 operator/=(Vec2 const &v);

			friend Vec2 operator+(Vec2 v1, Vec2 const &v2);
			friend Vec2 operator-(Vec2 v1, Vec2 const &v2);
			friend Vec2 operator*(Vec2 v1, Vec2 const &v2);
			friend Vec2 operator/(Vec2 v1, Vec2 const &v2);

			friend Vec2 operator*(Vec2 v, float f);

			friend bool operator==(Vec2 const &v1, Vec2 const &v2);
			friend bool operator!=(Vec2 const &v1, Vec2 const &v2);

			friend std::ostream& operator<<(std::ostream &out, Vec2 const &v);
			float x, y;
		private:

		};
	}
}