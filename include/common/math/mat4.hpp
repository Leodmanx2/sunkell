// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "definitions.hpp"
#include "mat3.hpp"
#include "vec4.hpp"

namespace sunkell {

	template <Arithmetic T>
	class mat4 final {
		vec4<T> rows[4];

		public:
		constexpr mat4() = default;
		constexpr mat4(const vec4<T>& v1,
		               const vec4<T>& v2,
		               const vec4<T>& v3,
		               const vec4<T>& v4)
		  : rows{{v1.x, v1.y, v1.z, v1.w},
		         {v2.x, v2.y, v2.z, v2.w},
		         {v3.x, v3.y, v3.z, v3.w},
		         {v4.x, v4.y, v4.z, v4.w}} {}
		explicit constexpr mat4(const mat3<T>& m)
		  : rows{{m[0][0], m[0][1], m[0][2], 0},
		         {m[1][0], m[1][1], m[1][2], 0},
		         {m[2][0], m[2][1], m[2][2], 0},
		         {0, 0, 0, 1}} {}
		constexpr mat4(mat4&)                  = default;
		constexpr mat4(mat4&&)                 = default;
		constexpr mat4& operator=(const mat4&) = default;
		constexpr mat4& operator=(mat4&&)      = default;
		constexpr ~mat4()                      = default;

		constexpr vec4<T>& operator[](int i) {
			switch(i) {
				case 0:
					return rows[0];
				case 1:
					return rows[1];
				case 2:
					return rows[2];
				case 3:
					return rows[3];
				default:
					throw std::out_of_range("mat4 index out of range");
			}
		}

		constexpr const vec4<T>& operator[](int i) const {
			switch(i) {
				case 0:
					return rows[0];
				case 1:
					return rows[1];
				case 2:
					return rows[2];
				case 3:
					return rows[3];
				default:
					throw std::out_of_range("mat4 index out of range");
			}
		}

		constexpr mat4 operator-() const noexcept {
			mat4 result;
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) { result[i][j] = -rows[i][j]; }
			}
			return result;
		}

		constexpr mat4 operator+(const mat4& m) const noexcept {
			mat4 result;
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) { result[i][j] = rows[i][j] + m[i][j]; }
			}
			return result;
		}

		constexpr mat4 operator-(const mat4& m) const noexcept {
			mat4 result;
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) { result[i][j] = rows[i][j] - m[i][j]; }
			}
			return result;
		}

		constexpr mat4 operator*(T s) const noexcept {
			mat4 result;
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) { result[i][j] = rows[i][j] * s; }
			}
			return result;
		}

		constexpr mat4 operator/(T s) const noexcept {
			T s_inv = static_cast<T>(1) / s;
			return *this * s_inv;
		}

		constexpr vec4<T> operator*(const vec4<T>& v) const noexcept {
			vec4<T> result;
			for(int i = 0; i < 4; ++i) {
				result[i] = rows[i][0] * v.x + rows[i][1] * v.y + rows[i][2] * v.z +
				            rows[i][3] * v.w;
			}
			return result;
		}

		constexpr mat4 operator*(const mat4& m) const noexcept {
			mat4 result;
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) {
					result[i][j] = rows[i][0] * m[0][j] + rows[i][1] * m[1][j] +
					               rows[i][2] * m[2][j] + rows[i][3] * m[3][j];
				}
			}
			return result;
		}

		constexpr mat4& operator*=(const mat4& m) noexcept {
			return *this = *this * m;
		}

		constexpr mat4& operator-=(const mat4& m) noexcept {
			return *this = *this - m;
		}

		constexpr mat4& operator*=(T s) noexcept { return *this = *this * s; }

		constexpr mat4& operator/=(T s) noexcept { return *this = *this / s; }

		constexpr bool operator==(const mat4& m) const noexcept {
			for(int i = 0; i < 4; ++i) {
				for(int j = 0; j < 4; ++j) {
					if(rows[i][j] != m[i][j]) { return false; }
				}
			}
			return true;
		}

		constexpr bool operator!=(const mat4& m) const noexcept {
			return !(*this == m);
		}
	}; // struct mat4

	template <Arithmetic T>
	constexpr mat4<T> operator*(T s, const mat4<T>& m) noexcept {
		return m * s;
	}

	template <Arithmetic T>
	constexpr vec4<T> operator*(const vec4<T>& v, const mat4<T>& m) noexcept {
		return m * v;
	}

	template <Arithmetic T>
	constexpr mat4<T> outer_product(const vec4<T>& c, const vec4<T>& r) noexcept {
		mat4<T> result;
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) { result[i][j] = c[i] * r[j]; }
		}
		return result;
	}

	template <Arithmetic T>
	constexpr mat4<T> operator/(T s, const mat4<T>& m) noexcept {
		return m / s;
	}

	template <Arithmetic T>
	constexpr mat4<T> transpose(const mat4<T>& m) noexcept {
		mat4<T> result;
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) { result[i][j] = m[j][i]; }
		}
		return result;
	}

} // namespace sunkell
