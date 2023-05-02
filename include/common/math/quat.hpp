// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "mat3.hpp"
#include "mat4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include <cmath>
#include <stdexcept>

namespace sunkell {

	template <typename T>
	struct quat final {
		T x;
		T y;
		T z;
		T w;

		constexpr quat(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
		constexpr quat() : x(0), y(0), z(0), w(0) {}
		constexpr quat(const vec4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
		constexpr explicit quat(const vec3<T>& v) : x(v.x), y(v.y), z(v.z), w(0) {}
		constexpr quat(const vec3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}
		constexpr quat(const quat&)            = default;
		constexpr quat(quat&&)                 = default;
		constexpr quat& operator=(const quat&) = default;
		constexpr quat& operator=(quat&&)      = default;

		// Construct quaternion from Euler angles
		static constexpr quat from_euler(T roll, T pitch, T yaw) {
			T cr = cos(roll * 0.5);
			T sr = sin(roll * 0.5);
			T cp = cos(pitch * 0.5);
			T sp = sin(pitch * 0.5);
			T cy = cos(yaw * 0.5);
			T sy = sin(yaw * 0.5);

			T z = sr * cp * cy - cr * sp * sy;
			T x = cr * sp * cy + sr * cp * sy;
			T y = cr * cp * sy - sr * sp * cy;
			T w = cr * cp * cy + sr * sp * sy;

			return {x, y, z, w};
		}

		// Construct quaternion from axis and angle
		static constexpr quat from_axis(const vec3<T>& axis, T angle) {
			const vec3<T> n = axis.normalized();
			T             s = sin(angle * 0.5);
			T             x = n.x * s;
			T             y = n.y * s;
			T             z = n.z * s;
			T             w = cos(angle * 0.5);
			return {x, y, z, w};
		}

		constexpr T dot(const quat& q) const {
			return x * q.x + y * q.y + z * q.z + w * q.w;
		}

		constexpr T length() const { return std::sqrt(dot(*this)); }

		constexpr quat normalized() const { return *this / length(); }

		constexpr mat3<T> to_mat3() const {
			const vec4<T> q = normalized();

			T x2 = q.x * q.x;
			T y2 = q.y * q.y;
			T z2 = q.z * q.z;
			T xy = q.x * q.y;
			T xz = q.x * q.z;
			T yz = q.y * q.z;
			T wx = q.w * q.x;
			T wy = q.w * q.y;
			T wz = q.w * q.z;

			return {{1 - 2 * (y2 + z2), 2 * (xy - wz), 2 * (xz + wy)},
			        {2 * (xy + wz), 1 - 2 * (x2 + z2), 2 * (yz - wx)},
			        {2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (x2 + y2)}};
		}

		constexpr mat4<T> to_mat4() const {
			const mat3 m = to_mat3();
			return {{m[0], 0}, {m[1], 0}, {m[2], 0}, {0, 0, 0, 1}};
		}

		constexpr operator vec4<T>() const { return {x, y, z, w}; }

		explicit constexpr operator mat3<T>() const { return to_mat3(); }

		explicit constexpr operator mat4<T>() const { return to_mat4(); }

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
					throw std::out_of_range("quat index out of range");
			}
		}

		constexpr const T& operator[](int i) const {
			return const_cast<quat*>(this)->operator[](i);
		}

		constexpr quat operator+(const quat& v) const {
			return {x + v.x, y + v.y, z + v.z, w + v.w};
		}

		constexpr quat operator-(const quat& v) const {
			return {x - v.x, y - v.y, z - v.z, w - v.w};
		}

		constexpr quat operator*(T s) const { return {x * s, y * s, z * s, w * s}; }

		constexpr quat operator/(T s) const { return {x / s, y / s, z / s, w / s}; }

		constexpr quat operator*(const quat& q) const {
			return {this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
			        this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
			        this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
			        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z};
		}

		constexpr quat operator-() const { return {-x, -y, -z, -w}; }

		constexpr quat operator+=(const quat& v) { return *this = *this + v; }

		constexpr quat operator-=(const quat& v) { return *this = *this - v; }

		constexpr quat operator*=(T s) { return *this = *this * s; }

		constexpr quat operator/=(T s) { return *this = *this / s; }

		constexpr quat& operator*=(const quat& q) { return *this = *this * q; }

		constexpr bool operator==(const quat& v) const {
			return x == v.x && y == v.y && z == v.z && w == v.w;
		}

		constexpr bool operator!=(const quat& v) const {
			return x != v.x || y != v.y || z != v.z || w != v.w;
		}
	}; // struct quat

} // namespace sunkell
