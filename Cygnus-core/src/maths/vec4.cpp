#include "vec4.h"

namespace Cygnus {
	namespace maths {

		Vec4::Vec4():x(0), y(0), z(0), w(0) {

		}

		Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

		}

		float Vec4::norme() const{

			return (sqrt(x*x + y * y + z * z + w*w));
		}

		Vec4 Vec4::normalize() const {
			float length = norme();
			return Vec4(x / length, y / length, z / length, w/length);

		}


		Vec4 Vec4::operator+=(Vec4 const &v) {
			x += v.x;
			y += v.y;
			z += v.z;
			w += v.w;

			return *this;
		}

		Vec4 Vec4::operator-=(Vec4 const &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;
			w -= v.w;
			
			return *this;
		}

		Vec4 Vec4::operator*=(Vec4 const &v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;
			w *= v.w;

			return *this;
		}

		Vec4 Vec4::operator/=(Vec4 const &v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;
			w /= v.w;

			return *this;
		}

		Vec4 operator+(Vec4 v1, Vec4 const &v2) {
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;
			v1.w += v2.w;

			return v1;
		}

		Vec4 operator-(Vec4 v1, Vec4 const &v2) {
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;
			v1.w -= v2.w;

			return v1;
		}

		Vec4 operator*(Vec4 v1, Vec4 const &v2) {
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;
			v1.w *= v2.w;

			return v1;
		}

		Vec4 operator/(Vec4 v1, Vec4 const &v2) {
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;
			v1.w /= v2.w;

			return v1;
		}

		Vec4 operator*(Vec4 v, float f) {
			return Vec4(v.x*f, v.y*f, v.z*f, v.w*f);
		}

		std::ostream& operator<<(std::ostream &out, Vec4 const &v) {
			out << "(" << v.x << "," << v.y << "," << v.z << "," << v.w << ")";

			return out;
		}

		bool operator==(Vec4 const &v1, Vec4 const &v2) {

			return !((v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z) || (v1.w != v2.w));
		}

		bool operator!=(Vec4 const &v1, Vec4 const &v2) {
			return !(v1 == v2);
		}


	}
}
