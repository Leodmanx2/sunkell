// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "vec2.hpp"

#include <cmath>

namespace sunkell {

	template <typename T>
	struct mat2 final {
		T m[2][2];

		constexpr mat2() = default;
		constexpr mat2(T m00, T m01, T m10, T m11) : m{{m00, m01}, {m10, m11}} {}
		constexpr mat2(mat2&)                  = default;
		constexpr mat2(mat2&&)                 = default;
		constexpr mat2& operator=(const mat2&) = default;
		constexpr mat2& operator=(mat2&&)      = default;

		constexpr T& at(int i, int j) {
			switch(i) {
				case 0:
					switch(j) {
						case 0:
							return m[0][0];
						case 1:
							return m[0][1];
						default:
							throw std::out_of_range("mat2 index out of range");
					}
				case 1:
					switch(j) {
						case 0:
							return m[1][0];
						case 1:
							return m[1][1];
						default:
							throw std::out_of_range("mat2 index out of range");
					}
				default:
					throw std::out_of_range("mat2 index out of range");
			}
		}

		constexpr const T& at(int i, int j) const {
			return const_cast<mat2*>(this)->at(i, j);
		}

		constexpr mat2 operator+(const mat2& m) const {
			return {{this->m[0][0] + m.m[0][0], this->m[0][1] + m.m[0][1]},
			        {this->m[1][0] + m.m[1][0], this->m[1][1] + m.m[1][1]}};
		}

		constexpr mat2 operator-(const mat2& m) const {
			return {{this->m[0][0] - m.m[0][0], this->m[0][1] - m.m[0][1]},
			        {this->m[1][0] - m.m[1][0], this->m[1][1] - m.m[1][1]}};
		}

		constexpr mat2 operator*(T s) const {
			return {{this->m[0][0] * s, this->m[0][1] * s},
			        {this->m[1][0] * s, this->m[1][1] * s}};
		}

		constexpr mat2 operator/(T s) const {
			return {{this->m[0][0] / s, this->m[0][1] / s},
			        {this->m[1][0] / s, this->m[1][1] / s}};
		}

		constexpr mat2 operator-() {
			return {{-this->m[0][0], -this->m[0][1]},
			        {-this->m[1][0], -this->m[1][1]}};
		}

		constexpr vec2<T> operator*(const vec2<T>& v) const {
			return {this->m[0][0] * v.x + this->m[0][1] * v.y,
			        this->m[1][0] * v.x + this->m[1][1] * v.y};
		}

		constexpr mat2 operator*(const mat2& m) const {
			return {{this->m[0][0] * m.m[0][0] + this->m[0][1] * m.m[1][0],
			         this->m[0][0] * m.m[0][1] + this->m[0][1] * m.m[1][1]},
			        {this->m[1][0] * m.m[0][0] + this->m[1][1] * m.m[1][0],
			         this->m[1][0] * m.m[0][1] + this->m[1][1] * m.m[1][1]}};
		}

		constexpr mat2 operator*=(const mat2& m) const {
			mat2<T> result = this * m;
			this->m[0][0]  = result.m[0][0];
			this->m[0][1]  = result.m[0][1];
			this->m[1][0]  = result.m[1][0];
			this->m[1][1]  = result.m[1][1];
			return *this;
		}

		constexpr mat2 operator+=(const mat2& m) {
			this->m[0][0] += m.m[0][0];
			this->m[0][1] += m.m[0][1];
			this->m[1][0] += m.m[1][0];
			this->m[1][1] += m.m[1][1];
			return *this;
		}

		constexpr mat2 operator-=(const mat2& m) {
			this->m[0][0] -= m.m[0][0];
			this->m[0][1] -= m.m[0][1];
			this->m[1][0] -= m.m[1][0];
			this->m[1][1] -= m.m[1][1];
			return *this;
		}

		constexpr mat2 operator*=(T s) {
			this->m[0][0] *= s;
			this->m[0][1] *= s;
			this->m[1][0] *= s;
			this->m[1][1] *= s;
			return *this;
		}

		constexpr mat2 operator/=(T s) {
			this->m[0][0] /= s;
			this->m[0][1] /= s;
			this->m[1][0] /= s;
			this->m[1][1] /= s;
			return *this;
		}

		constexpr bool operator==(const mat2& m) const {
			return this->m[0][0] == m.m[0][0] && this->m[0][1] == m.m[0][1] &&
			       this->m[1][0] == m.m[1][0] && this->m[1][1] == m.m[1][1];
		}

		constexpr bool operator!=(const mat2& m) const {
			return this->m[0][0] != m.m[0][0] || this->m[0][1] != m.m[0][1] ||
			       this->m[1][0] != m.m[1][0] || this->m[1][1] != m.m[1][1];
		}
	}; // struct mat2

	// In the context of sunkell there is no significant difference
	// between column-major and row-major vectors. This operator allows
	// vectors to be treated as row-major. It is defined in this
	// translation unit rather than the unit of vec2 so as to avoid
	// creating a circular dependency which cannot otherwise be
	// avoided due to the constexpr specifier.
	template <typename T>
	constexpr vec2<T> operator*(const vec2<T>& v, const mat2<T>& m) {
		return {m.m[0][0] * v.x + m.m[0][1] * v.y,
		        m.m[1][0] * v.x + m.m[1][1] * v.y};
	}

	template <typename T>
	constexpr mat2<T> transpose(const mat2<T>& m) {
		return {{m.m[0][0], m.m[1][0]}, {m.m[0][1], m.m[1][1]}};
	}

	template <typename T>
	constexpr mat2<T> identity() {
		return {{1, 0}, {0, 1}};
	}

	template <typename T>
	constexpr mat2<T> rotation(T angle) {
		return {{cos(angle), sin(angle)}, {-sin(angle), cos(angle)}};
	}

	template <typename T>
	constexpr mat2<T> scale(const vec2<T>& v) {
		return {{v.x, 0}, {0, v.y}};
	}

	template <typename T>
	constexpr mat2<T> scale(T x, T y) {
		return {{x, 0}, {0, y}};
	}

	template <typename T>
	constexpr mat2<T> scale(T s) {
		return {{s, 0}, {0, s}};
	}

	template <typename T>
	constexpr mat2<T> inverse(const mat2<T>& m) {
		T det = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
		return {{m.m[1][1] / det, -m.m[0][1] / det},
		        {-m.m[1][0] / det, m.m[0][0] / det}};
	}

} // namespace sunkell
