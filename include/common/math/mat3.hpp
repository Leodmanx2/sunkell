// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "vec3.hpp"

#include <cmath>

namespace sunkell {

	template <typename T>
	class mat3 final {
		vec3<T> rows[3];

		public:
		constexpr mat3() = default;
		constexpr mat3(
		  T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
		  : rows{{m00, m01, m02}, {m10, m11, m12}, {m20, m21, m22}} {}
		constexpr mat3(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3)
		  : rows{{v1.x, v1.y, v1.z}, {v2.x, v2.y, v2.z}, {v3.x, v3.y, v3.z}} {}
		constexpr mat3(mat3&)                  = default;
		constexpr mat3(mat3&&)                 = default;
		constexpr mat3& operator=(const mat3&) = default;
		constexpr mat3& operator=(mat3&&)      = default;

		static constexpr mat3 identity() {
			return {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
		}

		static constexpr mat3 rotation(T angle) {
			T c = cos(angle);
			T s = sin(angle);
			return {{c, -s, 0}, {s, c, 0}, {0, 0, 1}};
		}

		static constexpr mat3 scale(const vec3<T>& v) {
			return {{v.x, 0}, {0, v.y}, {0, v.z}};
		}

		static constexpr mat3 scale(T x, T y) { return {{x, 0}, {0, y}, {0, 1}}; }

		static constexpr mat3 scale(T s) { return {{s, 0}, {0, s}, {0, 1}}; }

		constexpr vec3<T>& operator[](int i) {
			switch(i) {
				case 0:
					return rows[0];
				case 1:
					return rows[1];
				case 2:
					return rows[2];
				default:
					throw std::out_of_range("mat3 index out of range");
			}
		}

		constexpr const vec3<T>& operator[](int i) const {
			return const_cast<mat3*>(this)->operator[](i);
		}

		constexpr mat3 operator-() {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = -rows[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator+(const mat3& m) const {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] + m[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator-(const mat3& m) const {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] - m[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator*(T s) const {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] * s; }
			}
			return result;
		}

		constexpr mat3 operator/(T s) const {
			T s_inv = static_cast<T>(1) / s;
			return *this * s_inv;
		}

		constexpr vec3<T> operator*(const vec3<T>& v) const {
			vec3<T> result;
			for(int i = 0; i < 3; ++i) {
				result[i] = rows[i][0] * v.x + rows[i][1] * v.y + rows[i][2] * v.z;
			}
			return result;
		}

		constexpr mat3 operator*(const mat3& m) const {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) {
					result[i][j] =
					  rows[i][0] * m[0][j] + rows[i][1] * m[1][j] + rows[i][2] * m[2][j];
				}
			}
			return result;
		}

		constexpr mat3 operator*=(const mat3& m) const { return *this = *this * m; }

		constexpr mat3 operator-=(const mat3& m) { return *this = *this - m; }

		constexpr mat3 operator*=(T s) { return *this = *this * s; }

		constexpr mat3 operator/=(T s) { return *this = *this / s; }

		constexpr bool operator==(const mat3& m) const {
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) {
					if(rows[i][j] != m[i][j]) { return false; }
				}
			}
			return true;
		}

		constexpr bool operator!=(const mat3& m) const { return !(*this == m); }
	}; // struct mat3

	template <typename T>
	constexpr vec3<T> operator*(const vec3<T>& v, const mat3<T>& m) {
		return m * v;
	}

	template <typename T>
	constexpr vec3<T> operator*(T s, const mat3<T>& m) {
		return m * s;
	}

	template <typename T>
	constexpr mat3<T> transpose(const mat3<T>& m) {
		mat3<T> result;
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) { result[i][j] = m[j][i]; }
		}
		return result;
	}

} // namespace sunkell
