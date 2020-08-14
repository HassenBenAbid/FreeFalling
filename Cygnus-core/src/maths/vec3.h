#pragma once

#include <iostream>

namespace Cygnus {
	namespace maths {
		class Vec3 {
		public:
			Vec3();
			Vec3(float x, float y, float z);

			float norme() const;
			Vec3 normalize() const;
			Vec3 cross(Vec3 const &v) const;
			float dot(Vec3 const &v) const;

			Vec3 operator+=(Vec3 const &v);
			Vec3 operator-=(Vec3 const &v);
			Vec3 operator*=(Vec3 const &v);
			Vec3 operator/=(Vec3 const &v);

			friend Vec3 operator+(Vec3 v1,Vec3 const &v2);
			friend Vec3 operator-(Vec3 v1,Vec3 const &v2);
			friend Vec3 operator*(Vec3 v1,Vec3 const &v2);
			friend Vec3 operator/(Vec3 v1,Vec3 const &v2);

			friend Vec3 operator*(Vec3 v, float f);
								  				  
			friend bool operator==(Vec3 const &v1,Vec3 const &v2);
			friend bool operator!=(Vec3 const &v1,Vec3 const &v2);

			friend std::ostream& operator<<(std::ostream &out, Vec3 const &v);

			float x, y, z;
		private:

		};
	}
}
