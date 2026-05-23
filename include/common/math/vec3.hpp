// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "vec2.hpp"

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <typename T>
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

		constexpr T dot(const vec3& v) const noexcept {
			return x * v.x + y * v.y + z * v.z;
		}

		constexpr T length() const noexcept { return sqrt(dot(*this)); }

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

	template <typename T>
	constexpr vec3<T> operator*(T s, vec3<T> v) noexcept {
		return {v.x * s, v.y * s, v.z * s};
	}

	template <typename T>
	constexpr vec3<T> operator/(T s, vec3<T> v) noexcept {
		return {v.x / s, v.y / s, v.z / s};
	}

} // namespace sunkell
