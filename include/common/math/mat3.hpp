// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "definitions.hpp"
#include "mat2.hpp"
#include "vec3.hpp"

namespace sunkell {

	template <Arithmetic T>
	class mat3 final {
		vec3<T> rows[3];

		public:
		constexpr mat3()
		  : rows{{static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)},
		         {static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)},
		         {static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)}} {}
		constexpr mat3(const vec3<T>& v1, const vec3<T>& v2, const vec3<T>& v3)
		  : rows{{v1.x, v1.y, v1.z}, {v2.x, v2.y, v2.z}, {v3.x, v3.y, v3.z}} {}
		explicit constexpr mat3(const mat2<T>& m)
		  : rows{{m[0][0], m[0][1], 0}, {m[1][0], m[1][1], 0}, {0, 0, 1}} {}
		constexpr mat3(const mat3&)            = default;
		constexpr mat3(mat3&&)                 = default;
		constexpr mat3& operator=(const mat3&) = default;
		constexpr mat3& operator=(mat3&&)      = default;
		constexpr ~mat3()                      = default;

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

		constexpr mat3 operator-() const noexcept {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = -rows[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator+(const mat3& m) const noexcept {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] + m[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator-(const mat3& m) const noexcept {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] - m[i][j]; }
			}
			return result;
		}

		constexpr mat3 operator*(T s) const noexcept {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) { result[i][j] = rows[i][j] * s; }
			}
			return result;
		}

		constexpr mat3 operator/(T s) const noexcept {
			T s_inv = static_cast<T>(1) / s;
			return *this * s_inv;
		}

		constexpr vec3<T> operator*(const vec3<T>& v) const noexcept {
			vec3<T> result;
			for(int i = 0; i < 3; ++i) {
				result[i] = rows[i][0] * v.x + rows[i][1] * v.y + rows[i][2] * v.z;
			}
			return result;
		}

		constexpr mat3 operator*(const mat3& m) const noexcept {
			mat3 result;
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) {
					result[i][j] =
					  rows[i][0] * m[0][j] + rows[i][1] * m[1][j] + rows[i][2] * m[2][j];
				}
			}
			return result;
		}

		constexpr mat3& operator*=(const mat3& m) noexcept {
			return *this = *this * m;
		}

		constexpr mat3& operator+=(const mat3& m) noexcept {
			return *this = *this + m;
		}

		constexpr mat3& operator-=(const mat3& m) noexcept {
			return *this = *this - m;
		}

		constexpr mat3& operator*=(T s) noexcept { return *this = *this * s; }

		constexpr mat3& operator/=(T s) noexcept { return *this = *this / s; }

		constexpr bool operator==(const mat3& m) const noexcept {
			for(int i = 0; i < 3; ++i) {
				for(int j = 0; j < 3; ++j) {
					if(rows[i][j] != m[i][j]) { return false; }
				}
			}
			return true;
		}

		constexpr bool operator!=(const mat3& m) const noexcept {
			return !(*this == m);
		}
	}; // struct mat3

	template <Arithmetic S, Arithmetic T>
	constexpr mat3<T> operator*(S s, const mat3<T>& m) noexcept {
		return m * s;
	}

	template <Arithmetic T>
	constexpr vec3<T> operator*(const vec3<T>& v, const mat3<T>& m) noexcept {
		return {v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0],
		        v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1],
		        v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2]};
	}

	template <Arithmetic T>
	constexpr mat3<T> outer_product(const vec3<T>& c, const vec3<T>& r) noexcept {
		mat3<T> result;
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) { result[i][j] = c[i] * r[j]; }
		}
		return result;
	}

	template <Arithmetic T>
	constexpr mat3<T> transpose(const mat3<T>& m) noexcept {
		mat3<T> result;
		for(int i = 0; i < 3; ++i) {
			for(int j = 0; j < 3; ++j) { result[i][j] = m[j][i]; }
		}
		return result;
	}

} // namespace sunkell
