#pragma once
#include "vec2.h"

namespace Cygnus {
	namespace maths {

		Vec2::Vec2() {

		}

		Vec2::Vec2(float x, float y) : x(x), y(y) {

		}

		float Vec2::norme() const{
			
			return (sqrt(x*x + y * y));
		}

		Vec2 Vec2::normalize() const {
			float length = norme();
			return Vec2(x / length, y / length);

		}


		Vec2 Vec2::operator+=(Vec2 const &v) {
			x += v.x;
			y += v.y;

			return *this;
		}

		Vec2 Vec2::operator-=(Vec2 const &v) {
			x -= v.x;
			y -= v.y;

			return *this;
		}

		Vec2 Vec2::operator*=(Vec2 const &v) {
			x *= v.x;
			y *= v.y;

			return *this;
		}

		Vec2 Vec2::operator/=(Vec2 const &v) {
			x /= v.x;
			y /= v.y;

			return *this;
		}

		Vec2 operator+(Vec2 v1, Vec2 const &v2) {

			v1.x += v2.x;
			v1.y += v2.y;

			return v1;
		}

		Vec2 operator-(Vec2 v1, Vec2 const &v2) {
			v1.x -= v2.x;
			v1.y -= v2.y;

			return v1;
		}

		Vec2 operator*(Vec2 v1, Vec2 const &v2) {
			v1.x *= v2.x;
			v1.y *= v2.y;

			return v1;
		}

		Vec2 operator/(Vec2 v1, Vec2 const &v2) {
			v1.x /= v2.x;
			v1.y /= v2.y;

			return v1;
		}

		Vec2 operator*(Vec2 v, float f) {
			return Vec2(v.x*f, v.y*f);
		}

		std::ostream& operator<<(std::ostream &out, Vec2 const &v) {
			out << "(" << v.x << "," << v.y << ")";

			return out;
		}

		bool operator==(Vec2 const &v1, Vec2 const &v2) {

			return !((v1.x != v2.x) || (v1.y != v2.y));
		}

		bool operator!=(Vec2 const &v1, Vec2 const &v2) {
			return !(v1 == v2);
		}

		float Vec2::produitVec(Vec2 &v, float angle) {
		
			return (norme()*v.norme()*sin(toRadians(angle)));
		}

	}
}



