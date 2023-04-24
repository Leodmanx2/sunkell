// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <typename T>
	struct vec2 {
		T x;
		T y;

		constexpr vec2(T x, T y) : x(x), y(y) {}
		constexpr vec2() : x(0), y(0) {}
		constexpr vec2(const vec2&)            = default;
		constexpr vec2(vec2&&)                 = default;
		constexpr vec2& operator=(const vec2&) = default;
		constexpr vec2& operator=(vec2&&)      = default;

		constexpr T operator[](int i) const {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw std::out_of_range("vec2 index out of range");
			}
		}

		constexpr T& operator[](int i) {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw std::out_of_range("vec2 index out of range");
			}
		}

		constexpr vec2 operator+(const vec2& v) const { return {x + v.x, y + v.y}; }

		constexpr vec2 operator-(const vec2& v) const { return {x - v.x, y - v.y}; }

		constexpr vec2 operator*(T s) const { return {x * s, y * s}; }

		constexpr vec2 operator/(T s) const { return {x / s, y / s}; }

		constexpr vec2 operator-() const { return {-x, -y}; }

		constexpr vec2 operator+=(const vec2& v) {
			x += v.x;
			y += v.y;
			return *this;
		}

		constexpr vec2 operator-=(const vec2& v) {
			x -= v.x;
			y -= v.y;
			return *this;
		}

		constexpr vec2 operator*=(T s) {
			x *= s;
			y *= s;
			return *this;
		}

		constexpr vec2 operator/=(T s) {
			x /= s;
			y /= s;
			return *this;
		}

		constexpr bool operator==(const vec2& v) const {
			return x == v.x && y == v.y;
		}

		constexpr bool operator!=(const vec2& v) const {
			return x != v.x || y != v.y;
		}
	};

	template <typename T>
	constexpr T dot(const vec2<T>& a, const vec2<T>& b) {
		return a.x * b.x + a.y * b.y;
	}

	template <typename T>
	constexpr T cross(const vec2<T>& a, const vec2<T>& b) {
		return a.x * b.y - a.y * b.x;
	}

	template <typename T>
	constexpr T length(const vec2<T>& v) {
		return std::sqrt(dot(v, v));
	}

	template <typename T>
	constexpr vec2<T> normalize(const vec2<T>& v) {
		return v / length(v);
	}

	using vec2f = vec2<float>;
	using vec2d = vec2<double>;

} // namespace sunkell
