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
			return const_cast<vec3*>(this)->operator[](i);
		}

		constexpr vec3 operator+(const vec3& v) const {
			return {x + v.x, y + v.y, z + v.z};
		}

		constexpr vec3 operator-(const vec3& v) const {
			return {x - v.x, y - v.y, z - v.z};
		}

		constexpr vec3 operator*(T s) const { return {x * s, y * s, z * s}; }

		constexpr vec3 operator/(T s) const { return {x / s, y / s, z / s}; }

		constexpr vec3 operator-() const { return {-x, -y, -z}; }

		constexpr vec3 operator+=(const vec3& v) { return *this = *this + v; }

		constexpr vec3 operator-=(const vec3& v) { return *this = *this - v; }

		constexpr vec3 operator*=(T s) { return *this = *this * s; }

		constexpr vec3 operator/=(T s) { return *this = *this / s; }

		constexpr bool operator==(const vec3& v) const {
			return x == v.x && y == v.y && z == v.z;
		}

		constexpr bool operator!=(const vec3& v) const {
			return x != v.x || y != v.y || z != v.z;
		}
	}; // struct vec3

	template <typename T>
	constexpr T dot(const vec3<T>& a, const vec3<T>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template <typename T>
	constexpr vec3<T> cross(const vec3<T>& a, const vec3<T>& b) {
		return {
		  a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
	}

	template <typename T>
	constexpr T length(const vec3<T>& v) {
		return std::sqrt(dot(v, v));
	}

	template <typename T>
	constexpr vec3<T> normalize(const vec3<T>& v) {
		return v / length(v);
	}

} // namespace sunkell
