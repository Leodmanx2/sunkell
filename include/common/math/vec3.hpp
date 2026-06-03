// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "definitions.hpp"
#include "vec2.hpp"

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <Arithmetic T>
	struct vec3 final {
		T x;
		T y;
		T z;

		constexpr vec3(T x, T y, T z) : x(x), y(y), z(z) {}
		constexpr vec3() : x(0), y(0), z(0) {}
		constexpr explicit vec3(const vec2<T>& v) : x(v.x), y(v.y), z(0) {}
		constexpr vec3(const vec2<T>& v, T z) : x(v.x), y(v.y), z(z) {}
		constexpr vec3(const vec3&)            = default;
		constexpr vec3(vec3&&)                 = default;
		constexpr vec3& operator=(const vec3&) = default;
		constexpr vec3& operator=(vec3&&)      = default;
		constexpr ~vec3()                      = default;

		constexpr T inner_product(const vec3& v) const noexcept {
			return x * v.x + y * v.y + z * v.z;
		}

		constexpr T length() const noexcept { return sqrt(inner_product(*this)); }

		constexpr vec3 normalized() const noexcept {
			if(length() == 0) { return *this; }
			return *this / length();
		}

		constexpr vec3 cross(const vec3& v) const noexcept {
			return {y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
		}

		constexpr T& operator[](int i) {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					throw std::out_of_range("vec3 index out of range");
			}
		}

		constexpr const T& operator[](int i) const {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				default:
					throw std::out_of_range("vec3 index out of range");
			}
		}

		constexpr vec3 operator+(const vec3& v) const noexcept {
			return {x + v.x, y + v.y, z + v.z};
		}

		constexpr vec3 operator-(const vec3& v) const noexcept {
			return {x - v.x, y - v.y, z - v.z};
		}

		constexpr vec3 operator*(T s) const noexcept {
			return {x * s, y * s, z * s};
		}

		constexpr vec3 operator/(T s) const noexcept {
			return {x / s, y / s, z / s};
		}

		constexpr vec3 operator-() const noexcept { return {-x, -y, -z}; }

		constexpr vec3& operator+=(const vec3& v) noexcept {
			return *this = *this + v;
		}

		constexpr vec3& operator-=(const vec3& v) noexcept {
			return *this = *this - v;
		}

		constexpr vec3& operator*=(T s) noexcept { return *this = *this * s; }

		constexpr vec3& operator/=(T s) noexcept { return *this = *this / s; }

		constexpr bool operator==(const vec3& v) const noexcept {
			return x == v.x && y == v.y && z == v.z;
		}

		constexpr bool operator!=(const vec3& v) const noexcept {
			return x != v.x || y != v.y || z != v.z;
		}
	}; // struct vec3

	template <Arithmetic T>
	constexpr T inner_product(const vec3<T>& a, const vec3<T>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template <Arithmetic T>
	constexpr T length(const vec3<T>& v) {
		return sqrt(inner_product(v, v));
	}

	template <Arithmetic T>
	constexpr vec3<T> normalize(const vec3<T>& v) {
		if(length(v) == 0) { return v; }
		return v / length(v);
	}

	template <Arithmetic T>
	constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b) {
		return {
		  a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
	}

	template <Arithmetic S, Arithmetic T>
	constexpr vec3<T> operator*(S s, vec3<T> v) noexcept {
		return v * static_cast<T>(s);
	}

} // namespace sunkell
