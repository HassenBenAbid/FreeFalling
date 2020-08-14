#include "vec3.h"

namespace Cygnus {
	namespace maths {

		Vec3::Vec3() : x(0), y(0), z(0){

		}

		Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {

		}

		float Vec3::norme() const{
			
			return (sqrt(x*x + y * y + z*z));
		}

		Vec3 Vec3::normalize() const {
			float length = norme();
			return Vec3(x / length, y / length, z / length);

		}

		Vec3 Vec3::cross(Vec3 const &v) const {
			return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
		}

		float Vec3::dot(Vec3 const &v) const {
			return (x*v.x + y * v.y + z*v.z);
		}

		Vec3 Vec3::operator+=(Vec3 const &v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		Vec3 Vec3::operator-=(Vec3 const &v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		Vec3 Vec3::operator*=(Vec3 const &v) {
			x *= v.x;
			y *= v.y;
			z *= v.z;

			return *this;
		}

		Vec3 Vec3::operator/=(Vec3 const &v) {
			x /= v.x;
			y /= v.y;
			z /= v.z;

			return *this;
		}

		Vec3 operator+(Vec3 v1, Vec3 const &v2) {
			v1.x += v2.x;
			v1.y += v2.y;
			v1.z += v2.z;

			return v1;
		}

		Vec3 operator-(Vec3 v1, Vec3 const &v2) {
			v1.x -= v2.x;
			v1.y -= v2.y;
			v1.z -= v2.z;

			return v1;
		}

		Vec3 operator*(Vec3 v1, Vec3 const &v2) {
			v1.x *= v2.x;
			v1.y *= v2.y;
			v1.z *= v2.z;

			return v1;
		}

		Vec3 operator/(Vec3 v1, Vec3 const &v2) {
			v1.x /= v2.x;
			v1.y /= v2.y;
			v1.z /= v2.z;

			return v1;
		}

		Vec3 operator*(Vec3 v, float f) {
			return Vec3(f*v.x, f*v.y, f*v.z);
		}

		std::ostream& operator<<(std::ostream &out, Vec3 const &v) {
			out << "(" << v.x << "," << v.y << "," << v.z << ")";

			return out;
		}

		bool operator==(Vec3 const &v1, Vec3 const &v2) {

			return !((v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z));
		}

		bool operator!=(Vec3 const &v1, Vec3 const &v2) {
			return !(v1 == v2);
		}


	}
}
