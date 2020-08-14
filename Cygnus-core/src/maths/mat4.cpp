#pragma once

#include "mat4.h"

namespace Cygnus {
	namespace maths{
		Mat4::Mat4() {

			for (int i = 0; i < 16; i++) {
				matr[i] = 0.0f;
			}
		}

		Mat4::Mat4(float a) {
			for (int i = 0; i < 16; i++) {
				if (i % 5 == 0)
					matr[i] = a;
				else
					matr[i] = 0.0f;
			}
		}

		Mat4::Mat4(float matrix[16]) {
			for (int i = 0; i < 16; i++) {
				matr[i] = matrix[i];
			}
		}

		Mat4 Mat4::identity() {
			Mat4 iden(1.0f);

			return iden;
		}

		Mat4 operator*(Mat4 const &m1, Mat4 const &m2) {
			Mat4 m;

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					float t = 0.0f;
					for (int d = 0; d < 4; d++) {
						t += m1.matr[i + d*4] * m2.matr[j*4 + d ];
					}
					m.matr[i + j * 4] = t;
				}
			}

			return m;
		}

		Vec3 operator*(Mat4 const &m, Vec3 const &v) {
			return Vec3{
				m.column[0].x * v.x + m.column[1].x * v.y + m.column[2].x * v.z + m.column[3].x,
				m.column[0].y * v.x + m.column[1].y * v.y + m.column[2].y * v.z + m.column[3].y,
				m.column[0].z * v.x + m.column[1].z * v.y + m.column[2].z * v.z + m.column[3].z
			};
		}

		Vec4 operator*(Mat4 const &m, Vec4 const &v) {
			return Vec4{
				m.column[0].x * v.x + m.column[1].x * v.y + m.column[2].x * v.z + m.column[3].x * v.w,
				m.column[0].y * v.x + m.column[1].y * v.y + m.column[2].y * v.z + m.column[3].y * v.w,
				m.column[0].z * v.x + m.column[1].z * v.y + m.column[2].z * v.z + m.column[3].z * v.w,
				m.column[0].z * v.x + m.column[1].z * v.y + m.column[2].z * v.z + m.column[3].z * v.w
			};
		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Mat4 o(1.0f);

			o.matr[0] = 2.0f / (right - left);
			o.matr[5] = 2.0f / (top - bottom);
			o.matr[10] = 2.0f / (near - far);
			o.matr[12] = (right + left) / (left - right);
			o.matr[13] = (bottom + top) / (bottom - top);
			o.matr[14] = (far + near) / (far - near);

			return o;
		}

		Mat4 Mat4::perspective(float aspectRatio, float verticleAngle, float near, float far) {
			Mat4 p;

			p.matr[0] = 1.0f / (aspectRatio*(tan(toRadians(verticleAngle) / 2.0f)));
			p.matr[5] = 1.0f / (tan(toRadians(verticleAngle) / 2.0f));
			p.matr[10] = - (near + far) / (far - near);
			p.matr[11] = -1.0f;
			p.matr[14] = -(2.0f * far*near) / (far - near);

			return p;
		}

		Mat4 Mat4::translation(Vec3 const &v) {
			Mat4 t(1.0f);

			t.matr[12] = v.x;
			t.matr[13] = v.y;
			t.matr[14] = v.z;

			return t;
		}

		Mat4 Mat4::scaling(Vec3 const &v) {
			Mat4 s(1.0f);

			s.matr[0] = v.x;
			s.matr[5] = v.y;
			s.matr[10] = v.z;

			return s;
		}

		Mat4 Mat4::rotation(float angle, Vec3 const &v) {
			float x = v.x;
			float y = v.y;
			float z = v.z;

			float o = toRadians(angle);
			float cosO = cos(o);
			float sinO = sin(o);
			float minusO = 1 - cosO;

			Mat4 r(1.0f);

			r.matr[0] = cosO + (x*x*minusO);
			r.matr[4] = (x * y * minusO) + (z*sinO);
			r.matr[8] = (z * x*minusO) - (y * sinO);

			r.matr[1] = (x * y * minusO) - (z * sinO);
			r.matr[5] = cosO + (y * y * minusO);
			r.matr[9] = (z * y * minusO) + (x * sinO);

			r.matr[2] = (x * z * minusO) + (y * sinO);
			r.matr[6] = (y * z * minusO) - (x * sinO);
			r.matr[10] = cosO + (z * z * minusO);

			return r;

			/*mat4 re(1.0f);

			re.matr[0] = m.matr[0] * r.matr[0] + m.matr[1] * r.matr[1] + m.matr[2] * r.matr[2];
			re.matr[1] = m.matr[0] * r.matr[4] + m.matr[1] * r.matr[5] + m.matr[2] * r.matr[6];
			re.matr[2] = m.matr[0] * r.matr[8] + m.matr[1] * r.matr[9] + m.matr[2] * r.matr[10];
			re.matr[3] = m.matr[3];

			return re;*/
		}

		Mat4 Mat4::lookAt(Vec3 const &from, Vec3 const &to, Vec3 const &up) {
			Mat4 res(1.0f);

			Vec3 f = (to - from).normalize();
			Vec3 r = (f.cross(up)).normalize();
			Vec3 u = r.cross(f);

			res.matr[0] = r.x;
			res.matr[1] = r.y;
			res.matr[2] = r.z;

			res.matr[4] = u.x;
			res.matr[5] = u.y;
			res.matr[6] = u.z;

			res.matr[8] = -f.x;
			res.matr[9] = -f.y;
			res.matr[10] = -f.z;

			res.matr[12] = -r.dot(from);
			res.matr[13] = -u.dot(from);
			res.matr[14] = f.dot(from);

			return res;

		}


	}
}