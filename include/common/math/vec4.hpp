// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "vec3.hpp"

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <typename T>
	struct vec4 final {
		T x;
		T y;
		T z;
		T w;

		constexpr vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		constexpr vec4() : x(0), y(0), z(0), w(0) {}
		constexpr explicit vec4(const vec3<T>& v) : x(v.x), y(v.y), z(v.z), w(0) {}
		constexpr vec4(const vec3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
		constexpr vec4(const vec4&)            = default;
		constexpr vec4(vec4&&)                 = default;
		constexpr vec4& operator=(const vec4&) = default;
		constexpr vec4& operator=(vec4&&)      = default;

		constexpr T dot(const vec4& v) const {
			return x * v.x + y * v.y + z * v.z + w * v.w;
		}

		constexpr T length() const { return sqrt(dot(*this)); }

		constexpr vec4 normalized() const { return *this / length(); }

		constexpr T& operator[](int i) {
			switch(i) {
				case 0:
					return x;
				case 1:
					return y;
				case 2:
					return z;
				case 3:
					return w;
				default:
					throw std::out_of_range("vec4 index out of range");
			}
		}

		constexpr const T& operator[](int i) const {
			return const_cast<vec4*>(this)->operator[](i);
		}

		constexpr vec4 operator+(const vec4& v) const {
			return {x + v.x, y + v.y, z + v.z, w + v.w};
		}

		constexpr vec4 operator-(const vec4& v) const {
			return {x - v.x, y - v.y, z - v.z, w - v.w};
		}

		constexpr vec4 operator*(T s) const { return {x * s, y * s, z * s, w * s}; }

		constexpr vec4 operator/(T s) const { return {x / s, y / s, z / s, w / s}; }

		constexpr vec4 operator-() const { return {-x, -y, -z, -w}; }

		constexpr vec4 operator+=(const vec4& v) { return *this = *this + v; }

		constexpr vec4 operator-=(const vec4& v) { return *this = *this - v; }

		constexpr vec4 operator*=(T s) { return *this = *this * s; }

		constexpr vec4 operator/=(T s) { return *this = *this / s; }

		constexpr bool operator==(const vec4& v) const {
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}

		constexpr bool operator!=(const vec4& v) const {
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}
	}; // struct vec4

	template <typename T>
	constexpr T dot(const vec4<T>& a, const vec4<T>& b) {
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	template <typename T>
	constexpr T length(const vec4<T>& v) {
		return sqrt(dot(v, v));
	}

	template <typename T>
	constexpr vec4<T> normalize(const vec4<T>& v) {
		return v / length(v);
	}

} // namespace sunkell
