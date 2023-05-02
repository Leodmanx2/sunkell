// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "mat3.hpp"
#include "mat4.hpp"
#include "vec4.hpp"

namespace sunkell {

	template <typename T>
	struct quat : public vec4<T> {
		using vec4<T>::vec4;

		constexpr mat3<T> to_mat3() const {
			const vec4<T> q = normalize(*this);

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

		explicit constexpr operator mat3<T>() const { return to_mat3(); }

		explicit constexpr operator mat4<T>() const { return to_mat4(); }

		constexpr quat operator*(const quat& q) const {
			return {this->w * q.x + this->x * q.w + this->y * q.z - this->z * q.y,
			        this->w * q.y + this->y * q.w + this->z * q.x - this->x * q.z,
			        this->w * q.z + this->z * q.w + this->x * q.y - this->y * q.x,
			        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z};
		}

		constexpr quat& operator*=(const quat& q) { return *this = *this * q; }
	};

} // namespace sunkell
