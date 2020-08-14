#pragma once 

#include <iostream>

namespace Cygnus {
	namespace maths {
		class Vec4 {
		public:
			Vec4();
			Vec4(float x, float y, float z, float w);

			float norme() const;
			Vec4 normalize() const;


			Vec4 operator+=(Vec4 const &v);
			Vec4 operator-=(Vec4 const &v);
			Vec4 operator*=(Vec4 const &v);
			Vec4 operator/=(Vec4 const &v);

			friend Vec4 operator+(Vec4 v1, Vec4 const &v2);
			friend Vec4 operator-(Vec4 v1, Vec4 const &v2);
			friend Vec4 operator*(Vec4 v1, Vec4 const &v2);
			friend Vec4 operator/(Vec4 v1, Vec4 const &v2);

			friend Vec4 operator*(Vec4 v, float f);

			friend bool operator==(Vec4 const &v1, Vec4 const &v2);
			friend bool operator!=(Vec4 const &v1, Vec4 const &v2);

			friend std::ostream& operator<<(std::ostream &out, Vec4 const &v);

			float x, y, z, w;
		private:

		};
	}
}