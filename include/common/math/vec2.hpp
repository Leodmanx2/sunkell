// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "definitions.hpp"

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <Arithmetic T>
	struct vec2 final {
		T x;
		T y;

		constexpr vec2(T x, T y) : x(x), y(y) {}
		constexpr vec2() : x(0), y(0) {}
		constexpr vec2(const vec2&)            = default;
		constexpr vec2(vec2&&)                 = default;
		constexpr vec2& operator=(const vec2&) = default;
		constexpr vec2& operator=(vec2&&)      = default;
		constexpr ~vec2()                      = default;

		constexpr T dot(const vec2& v) const noexcept { return x * v.x + y * v.y; }

		constexpr T length() const noexcept { return sqrt(dot(*this)); }

		constexpr vec2 normalized() const {
			if(length() == 0) { return *this; }
			return *this / length();
		}

		constexpr T perp_dot(const vec2& v) { return x * v.y - y * v.x; }

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

		constexpr const T& operator[](int i) const {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				default:
					throw std::out_of_range("vec2 index out of range");
			}
		}

		constexpr vec2 operator+(const vec2& v) const noexcept {
			return {x + v.x, y + v.y};
		}

		constexpr vec2 operator-(const vec2& v) const noexcept {
			return {x - v.x, y - v.y};
		}

		constexpr vec2 operator*(T s) const noexcept { return {x * s, y * s}; }

		constexpr vec2 operator/(T s) const noexcept { return {x / s, y / s}; }

		constexpr vec2 operator-() const noexcept { return {-x, -y}; }

		constexpr vec2& operator+=(const vec2& v) noexcept {
			return *this = *this + v;
		}

		constexpr vec2& operator-=(const vec2& v) noexcept {
			return *this = *this - v;
		}

		constexpr vec2& operator*=(T s) noexcept { return *this = *this * s; }

		constexpr vec2& operator/=(T s) noexcept { return *this = *this / s; }

		constexpr bool operator==(const vec2& v) const noexcept {
			return x == v.x && y == v.y;
		}

		constexpr bool operator!=(const vec2& v) const noexcept {
			return x != v.x || y != v.y;
		}
	}; // struct vec2

	template <Arithmetic T>
	constexpr T dot(const vec2<T>& a, const vec2<T>& b) {
		return a.x * b.x + a.y * b.y;
	}

	template <Arithmetic T>
	constexpr T length(const vec2<T>& v) {
		return sqrt(dot(v, v));
	}

	template <Arithmetic T>
	constexpr vec2<T> normalize(const vec2<T>& v) {
		if(length(v) == 0) { return v; }
		return v / length(v);
	}

	template <Arithmetic T>
	constexpr T perp_dot(const vec2<T>& a, const vec2<T>& b) {
		return a.x * b.y - a.y * b.x;
	}

	template <Arithmetic T>
	constexpr vec2<T> operator*(T s, vec2<T> v) noexcept {
		return {v.x * s, v.y * s};
	}

	template <Arithmetic T>
	constexpr vec2<T> operator/(T s, vec2<T> v) noexcept {
		return {v.x / s, v.y / s};
	}

} // namespace sunkell
