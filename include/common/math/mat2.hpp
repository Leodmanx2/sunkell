// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "definitions.hpp"
#include "vec2.hpp"

namespace sunkell {

	template <Arithmetic T>
	class mat2 final {
		vec2<T> rows[2];

		public:
		constexpr mat2()
		  : rows{{static_cast<T>(1), static_cast<T>(0)},
		         {static_cast<T>(0), static_cast<T>(1)}} {}
		constexpr mat2(const vec2<T>& v1, const vec2<T>& v2)
		  : rows{{v1.x, v1.y}, {v2.x, v2.y}} {}
		constexpr mat2(const mat2&)            = default;
		constexpr mat2(mat2&&)                 = default;
		constexpr mat2& operator=(const mat2&) = default;
		constexpr mat2& operator=(mat2&&)      = default;
		constexpr ~mat2()                      = default;

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
			switch(i) {
				case 0:
					return rows[0];
				case 1:
					return rows[1];
				default:
					throw std::out_of_range("mat2 index out of range");
			}
		}

		constexpr mat2 operator-() const noexcept {
			return {{-rows[0][0], -rows[0][1]}, {-rows[1][0], -rows[1][1]}};
		}

		constexpr mat2 operator+(const mat2& m) const noexcept {
			return {{rows[0][0] + m[0][0], rows[0][1] + m[0][1]},
			        {rows[1][0] + m[1][0], rows[1][1] + m[1][1]}};
		}

		constexpr mat2 operator-(const mat2& m) const noexcept {
			return {{rows[0][0] - m[0][0], rows[0][1] - m[0][1]},
			        {rows[1][0] - m[1][0], rows[1][1] - m[1][1]}};
		}

		constexpr mat2 operator*(T s) const noexcept {
			return {{rows[0][0] * s, rows[0][1] * s},
			        {rows[1][0] * s, rows[1][1] * s}};
		}

		constexpr mat2 operator/(T s) const noexcept {
			T s_inv = static_cast<T>(1) / s;
			return *this * s_inv;
		}

		constexpr vec2<T> operator*(const vec2<T>& v) const noexcept {
			return {rows[0][0] * v.x + rows[0][1] * v.y,
			        rows[1][0] * v.x + rows[1][1] * v.y};
		}

		constexpr mat2 operator*(const mat2& m) const noexcept {
			return {{rows[0][0] * m[0][0] + rows[0][1] * m[1][0],
			         rows[0][0] * m[0][1] + rows[0][1] * m[1][1]},
			        {rows[1][0] * m[0][0] + rows[1][1] * m[1][0],
			         rows[1][0] * m[0][1] + rows[1][1] * m[1][1]}};
		}

		constexpr mat2& operator*=(const mat2& m) noexcept {
			return *this = *this * m;
		}

		constexpr mat2& operator+=(const mat2& m) noexcept {
			return *this = *this + m;
		}

		constexpr mat2& operator-=(const mat2& m) noexcept {
			return *this = *this - m;
		}

		constexpr mat2& operator*=(T s) noexcept { return *this = *this * s; }

		constexpr mat2& operator/=(T s) noexcept { return *this = *this / s; }

		constexpr bool operator==(const mat2& m) const noexcept {
			for(int i = 0; i < 2; ++i) {
				for(int j = 0; j < 2; ++j) {
					if(rows[i][j] != m[i][j]) { return false; }
				}
			}
			return true;
		}

		constexpr bool operator!=(const mat2& m) const noexcept {
			return !(*this == m);
		}
	}; // struct mat2

	template <Arithmetic S, Arithmetic T>
	constexpr mat2<T> operator*(S s, const mat2<T>& m) noexcept {
		return m * s;
	}

	template <Arithmetic T>
	constexpr vec2<T> operator*(const vec2<T>& v, const mat2<T>& m) noexcept {
		return {v.x * m[0][0] + v.y * m[1][0], v.x * m[0][1] + v.y * m[1][1]};
	}

	template <Arithmetic T>
	constexpr mat2<T> outer_product(const vec2<T>& c, const vec2<T>& r) noexcept {
		return {{c.x * r.x, c.x * r.y}, {c.y * r.x, c.y * r.y}};
	}

	template <Arithmetic T>
	constexpr mat2<T> transpose(const mat2<T>& m) noexcept {
		return {{m[0][0], m[1][0]}, {m[0][1], m[1][1]}};
	}

} // namespace sunkell
