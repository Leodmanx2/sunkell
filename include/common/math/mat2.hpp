// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "vec2.hpp"

#include <cmath>

namespace sunkell {

	template <typename T>
	class mat2 final {
		vec2<T> rows[2];

		public:
		constexpr mat2() = default;
		constexpr mat2(T m00, T m01, T m10, T m11) : rows{{m00, m01}, {m10, m11}} {}
		constexpr mat2(const vec2<T>& v1, const vec2<T>& v2)
		  : rows{{v1.x, v1.y}, {v2.x, v2.y}} {}
		constexpr mat2(mat2&)                  = default;
		constexpr mat2(mat2&&)                 = default;
		constexpr mat2& operator=(const mat2&) = default;
		constexpr mat2& operator=(mat2&&)      = default;

		static constexpr mat2 identity() { return {{1, 0}, {0, 1}}; }

		static constexpr mat2 rotation(T angle) {
			return {{cos(angle), sin(angle)}, {-sin(angle), cos(angle)}};
		}

		static constexpr mat2 scale(const vec2<T>& v) {
			return {{v.x, 0}, {0, v.y}};
		}

		static constexpr mat2 scale(T x, T y) { return {{x, 0}, {0, y}}; }

		static constexpr mat2 scale(T s) { return {{s, 0}, {0, s}}; }

		constexpr vec2<T>& operator[](int i) {
			switch(i) {
				case 0:
					return rows[0];
				case 1:
					return rows[1];
				default:
					throw std::out_of_range("mat2 index out of range");
			}
		}

		constexpr const vec2<T>& operator[](int i) const {
			return const_cast<mat2*>(this)->operator[](i);
		}

		constexpr mat2 operator-() {
			return {{-rows[0][0], -rows[0][1]}, {-rows[1][0], -rows[1][1]}};
		}

		constexpr mat2 operator+(const mat2& m) const {
			return {{rows[0][0] + m[0][0], rows[0][1] + m[0][1]},
			        {rows[1][0] + m[1][0], rows[1][1] + m[1][1]}};
		}

		constexpr mat2 operator-(const mat2& m) const {
			return {{rows[0][0] - m[0][0], rows[0][1] - m[0][1]},
			        {rows[1][0] - m[1][0], rows[1][1] - m[1][1]}};
		}

		constexpr mat2 operator*(T s) const {
			return {{rows[0][0] * s, rows[0][1] * s},
			        {rows[1][0] * s, rows[1][1] * s}};
		}

		constexpr mat2 operator/(T s) const {
			T s_inv = static_cast<T>(1) / s;
			return *this * s_inv;
		}

		constexpr vec2<T> operator*(const vec2<T>& v) const {
			return {rows[0][0] * v.x + rows[0][1] * v.y,
			        rows[1][0] * v.x + rows[1][1] * v.y};
		}

		constexpr mat2 operator*(const mat2& m) const {
			return {{rows[0][0] * m[0][0] + rows[0][1] * m[1][0],
			         rows[0][0] * m[0][1] + rows[0][1] * m[1][1]},
			        {rows[1][0] * m[0][0] + rows[1][1] * m[1][0],
			         rows[1][0] * m[0][1] + rows[1][1] * m[1][1]}};
		}

		constexpr mat2 operator*=(const mat2& m) const { return *this = *this * m; }

		constexpr mat2 operator+=(const mat2& m) { return *this = *this + m; }

		constexpr mat2 operator-=(const mat2& m) { return *this = *this - m; }

		constexpr mat2 operator*=(T s) { return *this = *this * s; }

		constexpr mat2 operator/=(T s) { return *this = *this / s; }

		constexpr bool operator==(const mat2& m) const {
			for(int i = 0; i < 2; ++i) {
				for(int j = 0; j < 2; ++j) {
					if(rows[i][j] != m[i][j]) { return false; }
				}
			}
			return true;
		}

		constexpr bool operator!=(const mat2& m) const { return !(*this == m); }
	}; // struct mat2

	template <typename T>
	constexpr vec2<T> operator*(const vec2<T>& v, const mat2<T>& m) {
		return m * v;
	}

	template <typename T>
	constexpr vec2<T> operator*(T s, const mat2<T>& m) {
		return m * s;
	}

	template <typename T>
	constexpr mat2<T> transpose(const mat2<T>& m) {
		return {{m[0][0], m[1][0]}, {m[0][1], m[1][1]}};
	}

} // namespace sunkell
