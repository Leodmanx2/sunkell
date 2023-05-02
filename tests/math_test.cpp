// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "common/math.hpp"

#include <doctest/doctest.h>

using namespace sunkell;
using doctest::Approx;

TEST_SUITE("math") {
	TEST_CASE("vec2") {
		vec2<float> v1(1, 2);
		vec2<float> v2(3, 4);

		SUBCASE("vector addition") { REQUIRE(v1 + v2 == vec2<float>(4, 6)); }
		SUBCASE("vector subtraction") { REQUIRE(v1 - v2 == vec2<float>(-2, -2)); }
		SUBCASE("scalar multiplication") { REQUIRE(v1 * 2 == vec2<float>(2, 4)); }
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec2<float>(1 / 2.0, 2 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec2<float>(-1, -2)); }
		SUBCASE("equality") { REQUIRE(v1 == vec2<float>(1, 2)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec2<float>(2, 2)); }
		SUBCASE("dot product") { REQUIRE(dot(v1, v2) == 11); }
		SUBCASE("perpendicular dot product") { REQUIRE(perp_dot(v1, v2) == -2); }
		SUBCASE("length") { REQUIRE(length(v1) == Approx(2.2360679775)); }
		SUBCASE("normalize") {
			const vec2<float> norm = normalize(v1);
			REQUIRE(length(norm) == Approx(1));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(vec2<float>) == sizeof(float) * 2);
		}
	}
	TEST_CASE("vec3") {
		vec3<float> v1(1, 2, 3);
		vec3<float> v2(4, 5, 6);

		SUBCASE("vector addition") { REQUIRE(v1 + v2 == vec3<float>(5, 7, 9)); }
		SUBCASE("vector subtraction") {
			REQUIRE(v1 - v2 == vec3<float>(-3, -3, -3));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(v1 * 2 == vec3<float>(2, 4, 6));
		}
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec3<float>(1 / 2.0, 2 / 2.0, 3 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec3<float>(-1, -2, -3)); }
		SUBCASE("equality") { REQUIRE(v1 == vec3<float>(1, 2, 3)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec3<float>(2, 2, 2)); }
		SUBCASE("dot product") { REQUIRE(dot(v1, v2) == 32); }
		SUBCASE("cross product") {
			REQUIRE(cross(v1, v2) == vec3<float>(-3, 6, -3));
		}
		SUBCASE("length") { REQUIRE(length(v1) == Approx(3.74165738677)); }
		SUBCASE("normalize") {
			const vec3<float> norm = normalize(v1);
			REQUIRE(length(norm) == Approx(1));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(vec3<float>) == sizeof(float) * 3);
		}
	}
	TEST_CASE("vec4") {
		vec4<float> v1(1, 2, 3, 4);
		vec4<float> v2(5, 6, 7, 8);

		SUBCASE("vector addition") {
			REQUIRE(v1 + v2 == vec4<float>(6, 8, 10, 12));
		}
		SUBCASE("vector subtraction") {
			REQUIRE(v1 - v2 == vec4<float>(-4, -4, -4, -4));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(v1 * 2 == vec4<float>(2, 4, 6, 8));
		}
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec4<float>(1 / 2.0, 2 / 2.0, 3 / 2.0, 4 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec4<float>(-1, -2, -3, -4)); }
		SUBCASE("equality") { REQUIRE(v1 == vec4<float>(1, 2, 3, 4)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec4<float>(2, 2, 2, 2)); }
		SUBCASE("dot product") { REQUIRE(dot(v1, v2) == 70); }
		SUBCASE("length") { REQUIRE(length(v1) == Approx(5.47722557505)); }
		SUBCASE("normalize") {
			const vec4<float> norm = normalize(v1);
			REQUIRE(length(norm) == Approx(1));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(vec4<float>) == sizeof(float) * 4);
		}
	}
	TEST_CASE("mat2") {
		mat2<float> m1({1, 2}, {3, 4});
		mat2<float> m2({5, 6}, {7, 8});

		SUBCASE("matrix addition") {
			REQUIRE(m1 + m2 == mat2<float>({6, 8}, {10, 12}));
		}
		SUBCASE("matrix subtraction") {
			REQUIRE(m1 - m2 == mat2<float>({-4, -4}, {-4, -4}));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(m1 * 2 == mat2<float>({2, 4}, {6, 8}));
		}
		SUBCASE("scalar division") {
			REQUIRE(m1 / 2 == mat2<float>({1 / 2.0, 2 / 2.0}, {3 / 2.0, 4 / 2.0}));
		}
		SUBCASE("negation") { REQUIRE(-m1 == mat2<float>({-1, -2}, {-3, -4})); }
		SUBCASE("equality") { REQUIRE(m1 == mat2<float>({1, 2}, {3, 4})); }
		SUBCASE("inequality") { REQUIRE(m1 != mat2<float>({2, 2}, {2, 2})); }
		SUBCASE("matrix multiplication") {
			REQUIRE(m1 * m2 == mat2<float>({19, 22}, {43, 50}));
		}
		SUBCASE("vector multiplication") {
			REQUIRE(m1 * vec2<float>(1, 2) == vec2<float>(5, 11));
		}
		SUBCASE("vector pre-multiplication") {
			REQUIRE(vec2<float>(1, 2) * m1 == vec2<float>(5, 11));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(mat2<float>) == sizeof(float) * 4);
		}
	}
	TEST_CASE("mat3") {
		mat3<float> m1({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
		mat3<float> m2({10, 11, 12}, {13, 14, 15}, {16, 17, 18});

		SUBCASE("matrix addition") {
			REQUIRE(m1 + m2 == mat3<float>({11, 13, 15}, {17, 19, 21}, {23, 25, 27}));
		}
		SUBCASE("matrix subtraction") {
			REQUIRE(m1 - m2 == mat3<float>({-9, -9, -9}, {-9, -9, -9}, {-9, -9, -9}));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(m1 * 2 == mat3<float>({2, 4, 6}, {8, 10, 12}, {14, 16, 18}));
		}
		SUBCASE("scalar division") {
			REQUIRE(m1 / 2 == mat3<float>({1 / 2.0, 2 / 2.0, 3 / 2.0},
			                              {4 / 2.0, 5 / 2.0, 6 / 2.0},
			                              {7 / 2.0, 8 / 2.0, 9 / 2.0}));
		}
		SUBCASE("negation") {
			REQUIRE(-m1 == mat3<float>({-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}));
		}
		SUBCASE("equality") {
			REQUIRE(m1 == mat3<float>({1, 2, 3}, {4, 5, 6}, {7, 8, 9}));
		}
		SUBCASE("inequality") {
			REQUIRE(m1 != mat3<float>({2, 2, 2}, {2, 2, 2}, {2, 2, 2}));
		}
		SUBCASE("matrix multiplication") {
			REQUIRE(m1 * m2 ==
			        mat3<float>({84, 90, 96}, {201, 216, 231}, {318, 342, 366}));
		}
		SUBCASE("vector multiplication") {
			REQUIRE(m1 * vec3<float>(1, 2, 3) == vec3<float>(14, 32, 50));
		}
		SUBCASE("vector pre-multiplication") {
			REQUIRE(vec3<float>(1, 2, 3) * m1 == vec3<float>(14, 32, 50));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(mat3<float>) == sizeof(float) * 9);
		}
	}
	TEST_CASE("mat4") {
		mat4<float> m1(
		  {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
		mat4<float> m2(
		  {17, 18, 19, 20}, {21, 22, 23, 24}, {25, 26, 27, 28}, {29, 30, 31, 32});

		SUBCASE("matrix addition") {
			REQUIRE(m1 + m2 == mat4<float>({18, 20, 22, 24},
			                               {26, 28, 30, 32},
			                               {34, 36, 38, 40},
			                               {42, 44, 46, 48}));
		}
		SUBCASE("matrix subtraction") {
			REQUIRE(m1 - m2 == mat4<float>({-16, -16, -16, -16},
			                               {-16, -16, -16, -16},
			                               {-16, -16, -16, -16},
			                               {-16, -16, -16, -16}));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(m1 * 2 == mat4<float>({2, 4, 6, 8},
			                              {10, 12, 14, 16},
			                              {18, 20, 22, 24},
			                              {26, 28, 30, 32}));
		}
		SUBCASE("scalar division") {
			REQUIRE(m1 / 2 == mat4<float>({1 / 2.0, 2 / 2.0, 3 / 2.0, 4 / 2.0},
			                              {5 / 2.0, 6 / 2.0, 7 / 2.0, 8 / 2.0},
			                              {9 / 2.0, 10 / 2.0, 11 / 2.0, 12 / 2.0},
			                              {13 / 2.0, 14 / 2.0, 15 / 2.0, 16 / 2.0}));
		}
		SUBCASE("negation") {
			REQUIRE(-m1 == mat4<float>({-1, -2, -3, -4},
			                           {-5, -6, -7, -8},
			                           {-9, -10, -11, -12},
			                           {-13, -14, -15, -16}));
		}
		SUBCASE("equality") {
			REQUIRE(m1 ==
			        mat4<float>(
			          {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}));
		}
		SUBCASE("inequality") {
			REQUIRE(m1 != mat4<float>(
			                {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}, {2, 2, 2, 2}));
		}
		SUBCASE("matrix multiplication") {
			REQUIRE(m1 * m2 == mat4<float>({250, 260, 270, 280},
			                               {618, 644, 670, 696},
			                               {986, 1028, 1070, 1112},
			                               {1354, 1412, 1470, 1528}));
		}
		SUBCASE("vector multiplication") {
			REQUIRE(m1 * vec4<float>(1, 2, 3, 4) == vec4<float>(30, 70, 110, 150));
		}
		SUBCASE("vector pre-multiplication") {
			REQUIRE(vec4<float>(1, 2, 3, 4) * m1 == vec4<float>(30, 70, 110, 150));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(mat4<float>) == sizeof(float) * 16);
		}
	}
	TEST_CASE("quat") {
		quat<float> q1(1, 2, 3, 4);

		SUBCASE("3x3 matrix conversion") {
			mat3<float> m1 = q1.to_mat3();
			REQUIRE(m1[0][0] == Approx(0.13333333333));
			REQUIRE(m1[0][1] == Approx(-0.66666666666));
			REQUIRE(m1[0][2] == Approx(0.73333333333));
			REQUIRE(m1[1][0] == Approx(0.93333333333));
			REQUIRE(m1[1][1] == Approx(0.33333333333));
			REQUIRE(m1[1][2] == Approx(0.13333333333));
			REQUIRE(m1[2][0] == Approx(-0.33333333333));
			REQUIRE(m1[2][1] == Approx(0.66666666666));
			REQUIRE(m1[2][2] == Approx(0.66666666666));
		}
		SUBCASE("4x4 matrix conversion") {
			mat4<float> m1 = q1.to_mat4();
			REQUIRE(m1[0][0] == Approx(0.13333333333));
			REQUIRE(m1[0][1] == Approx(-0.66666666666));
			REQUIRE(m1[0][2] == Approx(0.73333333333));
			REQUIRE(m1[0][3] == Approx(0));
			REQUIRE(m1[1][0] == Approx(0.93333333333));
			REQUIRE(m1[1][1] == Approx(0.33333333333));
			REQUIRE(m1[1][2] == Approx(0.13333333333));
			REQUIRE(m1[1][3] == Approx(0));
			REQUIRE(m1[2][0] == Approx(-0.33333333333));
			REQUIRE(m1[2][1] == Approx(0.66666666666));
			REQUIRE(m1[2][2] == Approx(0.66666666666));
			REQUIRE(m1[2][3] == Approx(0));
			REQUIRE(m1[3][0] == Approx(0));
			REQUIRE(m1[3][1] == Approx(0));
			REQUIRE(m1[3][2] == Approx(0));
			REQUIRE(m1[3][3] == Approx(1));
		}
		SUBCASE("quaternion composition") {
			quat<float> q2(5, 6, 7, 8);
			REQUIRE(q1 * q2 == quat<float>(24, 48, 48, -6));
		}
	}
}
