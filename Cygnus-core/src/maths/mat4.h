#pragma once

#define _USE_MATH_DEFINES

#include <iostream>
#include <math.h>
#include "maths.h"

namespace Cygnus {
	namespace maths {

		class Mat4 {

		public:

			union 
			{
				float matr[16];
				Vec4 column[4];
			};
			

			Mat4();
			Mat4(float a);
			Mat4(float matrix[16]);


			static Mat4 identity();

			friend Mat4 operator*(Mat4 const &m1, Mat4 const &m2);
			friend Vec3 operator*(Mat4 const &m, Vec3 const &v);
			friend Vec4 operator*(Mat4 const &m, Vec4 const &v);

			Mat4 static orthographic(float left, float right, float bottom, float top, float near, float far);
			Mat4 static perspective(float aspectRatio, float verticleAngle, float near, float far);

			Mat4 static translation(Vec3 const &v);
			Mat4 static scaling(Vec3 const &v);
			Mat4 static rotation(float angle, Vec3 const &axis);

			Mat4 static lookAt(Vec3 const &from, Vec3 const &to, Vec3 const &up);


		};
	}
}