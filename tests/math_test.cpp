// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "common/math.hpp"

#include <cmath>
#include <concepts>
#include <doctest/doctest.h>
#include <numbers>
#include <stdexcept>

using namespace sunkell;
using doctest::Approx;

namespace {

	template <typename T>
	concept supports_int_left_multiply = requires(const T& value) { 2 * value; };

	template <typename T>
	concept supports_scalar_predivide =
	  requires(const T& value) { 1.0f / value; };

	template <typename Q, typename V>
	concept supports_direct_product =
	  requires(const Q& lhs, const V& rhs) { lhs * rhs; };

	template <typename T>
	concept supports_add_assign = requires(T value, const T& other) {
		{ value += other } -> std::same_as<T&>;
	};

	template <typename T>
	concept supports_sub_assign = requires(T value, const T& other) {
		{ value -= other } -> std::same_as<T&>;
	};

	template <typename T>
	concept supports_mul_assign = requires(T value, const T& other) {
		{ value *= other } -> std::same_as<T&>;
	};

	template <typename T>
	concept supports_float_mul_assign = requires(T value) {
		{ value *= 2.0f } -> std::same_as<T&>;
	};

	template <typename T>
	concept supports_float_div_assign = requires(T value) {
		{ value /= 2.0f } -> std::same_as<T&>;
	};

	template <typename T>
	concept supports_const_perp_inner_product =
	  requires(const vec2<T>& a, const vec2<T>& b) {
		  { a.perp_inner_product(b) } -> std::same_as<T>;
	  };

	constexpr float half_pi = std::numbers::pi_v<float> / 2.0f;

	void check_close(const vec2<float>& actual, const vec2<float>& expected) {
		CHECK(actual.x == Approx(expected.x));
		CHECK(actual.y == Approx(expected.y));
	}

	void check_close(const vec3<float>& actual, const vec3<float>& expected) {
		CHECK(actual.x == Approx(expected.x));
		CHECK(actual.y == Approx(expected.y));
		CHECK(actual.z == Approx(expected.z));
	}

	void check_close(const vec4<float>& actual, const vec4<float>& expected) {
		CHECK(actual.x == Approx(expected.x));
		CHECK(actual.y == Approx(expected.y));
		CHECK(actual.z == Approx(expected.z));
		CHECK(actual.w == Approx(expected.w));
	}

	template <typename T>
	void require_int_left_multiply(const T&    value,
	                               const T&    expected,
	                               const char* message) {
		REQUIRE_MESSAGE((supports_int_left_multiply<T>), message);

		if constexpr(supports_int_left_multiply<T>) {
			REQUIRE(2 * value == expected);
		}
	}

	template <typename T>
	void require_scalar_predivide_absent(const char* message) {
		REQUIRE_FALSE_MESSAGE((supports_scalar_predivide<T>), message);
	}

	template <typename Q, typename V>
	void require_direct_product(const Q&    lhs,
	                            const V&    rhs,
	                            const V&    expected,
	                            const char* message) {
		REQUIRE_MESSAGE((supports_direct_product<Q, V>), message);

		if constexpr(supports_direct_product<Q, V>) {
			check_close(lhs * rhs, expected);
		}
	}

} // namespace

TEST_SUITE("math") {
	TEST_CASE("vec2") {
		vec2<float> v1(1, 2);
		vec2<float> v2(3, 4);

		SUBCASE("vector addition") { REQUIRE(v1 + v2 == vec2<float>(4, 6)); }
		SUBCASE("vector subtraction") { REQUIRE(v1 - v2 == vec2<float>(-2, -2)); }
		SUBCASE("scalar multiplication") { REQUIRE(v1 * 2 == vec2<float>(2, 4)); }
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * v1 == vec2<float>(2, 4));
		}
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec2<float>(1 / 2.0, 2 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec2<float>(-1, -2)); }
		SUBCASE("equality") { REQUIRE(v1 == vec2<float>(1, 2)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec2<float>(2, 2)); }
		SUBCASE("inner product") { REQUIRE(v1.inner_product(v2) == 11); }
		SUBCASE("perpendicular inner product") {
			REQUIRE(v1.perp_inner_product(v2) == -2);
		}
		SUBCASE("length") { REQUIRE(v1.length() == Approx(2.2360679775)); }
		SUBCASE("free function helpers") {
			REQUIRE(inner_product(v1, v2) == 11);
			REQUIRE(perp_inner_product(v1, v2) == -2);
			REQUIRE(length(v1) == Approx(2.2360679775));
			REQUIRE(normalize(v1).length() == Approx(1));
		}
		SUBCASE("normalize") {
			const vec2<float> norm = v1.normalized();
			REQUIRE(norm.length() == Approx(1));
		}
		SUBCASE("zero vector normalization") {
			REQUIRE(vec2<float>().normalized() == vec2<float>());
			REQUIRE(normalize(vec2<float>()) == vec2<float>());
		}
		SUBCASE("compound assignment") {
			auto v = v1;
			v += v2;
			REQUIRE(v == vec2<float>(4, 6));
			v -= v1;
			REQUIRE(v == v2);
			v *= 2;
			REQUIRE(v == vec2<float>(6, 8));
			v /= 2;
			REQUIRE(v == v2);
		}
		SUBCASE("index access") {
			REQUIRE(v1[0] == 1);
			REQUIRE(v1[1] == 2);
			v1[0] = 5;
			v1[1] = 6;
			REQUIRE(v1 == vec2<float>(5, 6));

			const vec2<float> cv(1, 2);
			REQUIRE(cv[0] == 1);
			REQUIRE(cv[1] == 2);
		}
		SUBCASE("index bounds checks") {
			const vec2<float> cv(1, 2);
			REQUIRE_THROWS_AS(v1[2], std::out_of_range);
			REQUIRE_THROWS_AS(cv[-1], std::out_of_range);
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
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * v1 == vec3<float>(2, 4, 6));
		}
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec3<float>(1 / 2.0, 2 / 2.0, 3 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec3<float>(-1, -2, -3)); }
		SUBCASE("equality") { REQUIRE(v1 == vec3<float>(1, 2, 3)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec3<float>(2, 2, 2)); }
		SUBCASE("inner product") { REQUIRE(v1.inner_product(v2) == 32); }
		SUBCASE("cross product") {
			REQUIRE(v1.cross(v2) == vec3<float>(-3, 6, -3));
		}
		SUBCASE("construction from vec2") {
			const vec2<float> base(1, 2);
			REQUIRE(vec3<float>(base) == vec3<float>(1, 2, 0));
			REQUIRE(vec3<float>(base, 3) == vec3<float>(1, 2, 3));
		}
		SUBCASE("length") { REQUIRE(v1.length() == Approx(3.74165738677)); }
		SUBCASE("free function helpers") {
			REQUIRE(inner_product(v1, v2) == 32);
			REQUIRE(cross(v1, v2) == vec3<float>(-3, 6, -3));
			REQUIRE(length(v1) == Approx(3.74165738677));
			REQUIRE(normalize(v1).length() == Approx(1));
		}
		SUBCASE("normalize") {
			const vec3<float> norm = v1.normalized();
			REQUIRE(norm.length() == Approx(1));
		}
		SUBCASE("zero vector normalization") {
			REQUIRE(vec3<float>().normalized() == vec3<float>());
			REQUIRE(normalize(vec3<float>()) == vec3<float>());
		}
		SUBCASE("cross product orthogonality") {
			const auto c = v1.cross(v2);
			REQUIRE(c.inner_product(v1) == 0);
			REQUIRE(c.inner_product(v2) == 0);
			REQUIRE(c == -cross(v2, v1));
		}
		SUBCASE("compound assignment") {
			auto v = v1;
			v += v2;
			REQUIRE(v == vec3<float>(5, 7, 9));
			v -= v1;
			REQUIRE(v == v2);
			v *= 2;
			REQUIRE(v == vec3<float>(8, 10, 12));
			v /= 2;
			REQUIRE(v == v2);
		}
		SUBCASE("index access") {
			REQUIRE(v1[0] == 1);
			REQUIRE(v1[1] == 2);
			REQUIRE(v1[2] == 3);
			v1[0] = 4;
			v1[1] = 5;
			v1[2] = 6;
			REQUIRE(v1 == vec3<float>(4, 5, 6));

			const vec3<float> cv(1, 2, 3);
			REQUIRE(cv[0] == 1);
			REQUIRE(cv[1] == 2);
			REQUIRE(cv[2] == 3);
		}
		SUBCASE("index bounds checks") {
			const vec3<float> cv(1, 2, 3);
			REQUIRE_THROWS_AS(v1[3], std::out_of_range);
			REQUIRE_THROWS_AS(cv[-1], std::out_of_range);
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
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * v1 == vec4<float>(2, 4, 6, 8));
		}
		SUBCASE("scalar division") {
			REQUIRE(v1 / 2 == vec4<float>(1 / 2.0, 2 / 2.0, 3 / 2.0, 4 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-v1 == vec4<float>(-1, -2, -3, -4)); }
		SUBCASE("equality") { REQUIRE(v1 == vec4<float>(1, 2, 3, 4)); }
		SUBCASE("inequality") { REQUIRE(v1 != vec4<float>(2, 2, 2, 2)); }
		SUBCASE("inner product") { REQUIRE(v1.inner_product(v2) == 70); }
		SUBCASE("construction from vec3") {
			const vec3<float> base(1, 2, 3);
			REQUIRE(vec4<float>(base) == vec4<float>(1, 2, 3, 0));
			REQUIRE(vec4<float>(base, 4) == vec4<float>(1, 2, 3, 4));
		}
		SUBCASE("length") { REQUIRE(v1.length() == Approx(5.47722557505)); }
		SUBCASE("free function helpers") {
			REQUIRE(inner_product(v1, v2) == 70);
			REQUIRE(length(v1) == Approx(5.47722557505));
			REQUIRE(normalize(v1).length() == Approx(1));
		}
		SUBCASE("normalize") {
			const vec4<float> norm = v1.normalized();
			REQUIRE(norm.length() == Approx(1));
		}
		SUBCASE("zero vector normalization") {
			REQUIRE(vec4<float>().normalized() == vec4<float>());
			REQUIRE(normalize(vec4<float>()) == vec4<float>());
		}
		SUBCASE("compound assignment") {
			auto v = v1;
			v += v2;
			REQUIRE(v == vec4<float>(6, 8, 10, 12));
			v -= v1;
			REQUIRE(v == v2);
			v *= 2;
			REQUIRE(v == vec4<float>(10, 12, 14, 16));
			v /= 2;
			REQUIRE(v == v2);
		}
		SUBCASE("index access") {
			REQUIRE(v1[0] == 1);
			REQUIRE(v1[1] == 2);
			REQUIRE(v1[2] == 3);
			REQUIRE(v1[3] == 4);
			v1[0] = 5;
			v1[1] = 6;
			v1[2] = 7;
			v1[3] = 8;
			REQUIRE(v1 == vec4<float>(5, 6, 7, 8));

			const vec4<float> cv(1, 2, 3, 4);
			REQUIRE(cv[0] == 1);
			REQUIRE(cv[1] == 2);
			REQUIRE(cv[2] == 3);
			REQUIRE(cv[3] == 4);
		}
		SUBCASE("index bounds checks") {
			const vec4<float> cv(1, 2, 3, 4);
			REQUIRE_THROWS_AS(v1[4], std::out_of_range);
			REQUIRE_THROWS_AS(cv[-1], std::out_of_range);
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
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * m1 == mat2<float>({2, 4}, {6, 8}));
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
			REQUIRE(vec2<float>(1, 2) * m1 == vec2<float>(7, 10));
		}
		SUBCASE("transpose") {
			REQUIRE(transpose(m1) == mat2<float>({1, 3}, {2, 4}));
		}
		SUBCASE("outer product") {
			REQUIRE(outer_product(vec2<float>(1, 2), vec2<float>(3, 4)) ==
			        mat2<float>({3, 4}, {6, 8}));
		}
		SUBCASE("compound assignment") {
			auto sum = m1;
			sum += m2;
			REQUIRE(sum == mat2<float>({6, 8}, {10, 12}));
			sum -= m1;
			REQUIRE(sum == m2);

			auto scaled = m1;
			scaled *= 2;
			REQUIRE(scaled == mat2<float>({2, 4}, {6, 8}));
			scaled /= 2;
			REQUIRE(scaled == m1);

			auto product = m1;
			product *= m2;
			REQUIRE(product == mat2<float>({19, 22}, {43, 50}));
		}
		SUBCASE("index access") {
			REQUIRE(m1[0] == vec2<float>(1, 2));
			REQUIRE(m1[1] == vec2<float>(3, 4));
			m1[1][0] = 9;
			REQUIRE(m1[1] == vec2<float>(9, 4));

			const mat2<float> cm({1, 2}, {3, 4});
			REQUIRE(cm[0][0] == 1);
			REQUIRE(cm[0][1] == 2);
			REQUIRE(cm[1][0] == 3);
			REQUIRE(cm[1][1] == 4);
		}
		SUBCASE("index bounds checks") {
			const mat2<float> cm({1, 2}, {3, 4});
			REQUIRE_THROWS_AS(m1[2], std::out_of_range);
			REQUIRE_THROWS_AS(cm[-1], std::out_of_range);
			REQUIRE_THROWS_AS(m1[0][2], std::out_of_range);
			REQUIRE_THROWS_AS(cm[0][-1], std::out_of_range);
		}
		SUBCASE("copy construction from const matrix") {
			const mat2<float> source({1, 2}, {3, 4});
			const mat2<float> copy = source;
			REQUIRE(copy == source);
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
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * m1 == mat3<float>({2, 4, 6}, {8, 10, 12}, {14, 16, 18}));
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
			REQUIRE(vec3<float>(1, 2, 3) * m1 == vec3<float>(30, 36, 42));
		}
		SUBCASE("construction from mat2") {
			const mat2<float> base({1, 2}, {3, 4});
			REQUIRE(mat3<float>(base) ==
			        mat3<float>({1, 2, 0}, {3, 4, 0}, {0, 0, 1}));
		}
		SUBCASE("transpose") {
			REQUIRE(transpose(m1) == mat3<float>({1, 4, 7}, {2, 5, 8}, {3, 6, 9}));
		}
		SUBCASE("outer product") {
			REQUIRE(outer_product(vec3<float>(1, 2, 3), vec3<float>(4, 5, 6)) ==
			        mat3<float>({4, 5, 6}, {8, 10, 12}, {12, 15, 18}));
		}
		SUBCASE("compound assignment") {
			auto difference = m1;
			difference -= m2;
			REQUIRE(difference ==
			        mat3<float>({-9, -9, -9}, {-9, -9, -9}, {-9, -9, -9}));

			auto scaled = m1;
			scaled *= 2;
			REQUIRE(scaled == mat3<float>({2, 4, 6}, {8, 10, 12}, {14, 16, 18}));
			scaled /= 2;
			REQUIRE(scaled == m1);

			auto product = m1;
			product *= m2;
			REQUIRE(product ==
			        mat3<float>({84, 90, 96}, {201, 216, 231}, {318, 342, 366}));
		}
		SUBCASE("index access") {
			REQUIRE(m1[0] == vec3<float>(1, 2, 3));
			REQUIRE(m1[1] == vec3<float>(4, 5, 6));
			REQUIRE(m1[2] == vec3<float>(7, 8, 9));
			m1[2][1] = 10;
			REQUIRE(m1[2] == vec3<float>(7, 10, 9));

			const mat3<float> cm({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
			REQUIRE(cm[0][0] == 1);
			REQUIRE(cm[1][1] == 5);
			REQUIRE(cm[2][2] == 9);
		}
		SUBCASE("index bounds checks") {
			const mat3<float> cm({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
			REQUIRE_THROWS_AS(m1[3], std::out_of_range);
			REQUIRE_THROWS_AS(cm[-1], std::out_of_range);
			REQUIRE_THROWS_AS(m1[0][3], std::out_of_range);
			REQUIRE_THROWS_AS(cm[0][-1], std::out_of_range);
		}
		SUBCASE("copy construction from const matrix") {
			const mat3<float> source({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
			const mat3<float> copy = source;
			REQUIRE(copy == source);
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
		SUBCASE("left scalar multiplication") {
			REQUIRE(2.0f * m1 == mat4<float>({2, 4, 6, 8},
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
			REQUIRE(vec4<float>(1, 2, 3, 4) * m1 == vec4<float>(90, 100, 110, 120));
		}
		SUBCASE("construction from mat3") {
			const mat3<float> base({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
			REQUIRE(
			  mat4<float>(base) ==
			  mat4<float>({1, 2, 3, 0}, {4, 5, 6, 0}, {7, 8, 9, 0}, {0, 0, 0, 1}));
		}
		SUBCASE("transpose") {
			REQUIRE(transpose(m1) ==
			        mat4<float>(
			          {1, 5, 9, 13}, {2, 6, 10, 14}, {3, 7, 11, 15}, {4, 8, 12, 16}));
		}
		SUBCASE("outer product") {
			REQUIRE(
			  outer_product(vec4<float>(1, 2, 3, 4), vec4<float>(5, 6, 7, 8)) ==
			  mat4<float>(
			    {5, 6, 7, 8}, {10, 12, 14, 16}, {15, 18, 21, 24}, {20, 24, 28, 32}));
		}
		SUBCASE("compound assignment") {
			auto difference = m1;
			difference -= m2;
			REQUIRE(difference == mat4<float>({-16, -16, -16, -16},
			                                  {-16, -16, -16, -16},
			                                  {-16, -16, -16, -16},
			                                  {-16, -16, -16, -16}));

			auto scaled = m1;
			scaled *= 2;
			REQUIRE(scaled == mat4<float>({2, 4, 6, 8},
			                              {10, 12, 14, 16},
			                              {18, 20, 22, 24},
			                              {26, 28, 30, 32}));
			scaled /= 2;
			REQUIRE(scaled == m1);

			auto product = m1;
			product *= m2;
			REQUIRE(product == mat4<float>({250, 260, 270, 280},
			                               {618, 644, 670, 696},
			                               {986, 1028, 1070, 1112},
			                               {1354, 1412, 1470, 1528}));
		}
		SUBCASE("index access") {
			REQUIRE(m1[0] == vec4<float>(1, 2, 3, 4));
			REQUIRE(m1[1] == vec4<float>(5, 6, 7, 8));
			REQUIRE(m1[2] == vec4<float>(9, 10, 11, 12));
			REQUIRE(m1[3] == vec4<float>(13, 14, 15, 16));
			m1[3][2] = 20;
			REQUIRE(m1[3] == vec4<float>(13, 14, 20, 16));

			const mat4<float> cm(
			  {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
			REQUIRE(cm[0][0] == 1);
			REQUIRE(cm[1][1] == 6);
			REQUIRE(cm[2][2] == 11);
			REQUIRE(cm[3][3] == 16);
		}
		SUBCASE("index bounds checks") {
			const mat4<float> cm(
			  {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
			REQUIRE_THROWS_AS(m1[4], std::out_of_range);
			REQUIRE_THROWS_AS(cm[-1], std::out_of_range);
			REQUIRE_THROWS_AS(m1[0][4], std::out_of_range);
			REQUIRE_THROWS_AS(cm[0][-1], std::out_of_range);
		}
		SUBCASE("copy construction from const matrix") {
			const mat4<float> source(
			  {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
			const mat4<float> copy = source;
			REQUIRE(copy == source);
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(mat4<float>) == sizeof(float) * 16);
		}
	}
	TEST_CASE("quat") {
		quat<float> q1(1, 2, 3, 4);

		SUBCASE("construction from vectors") {
			REQUIRE(quat<float>(vec4<float>(1, 2, 3, 4)) == quat<float>(1, 2, 3, 4));
			REQUIRE(quat<float>(vec3<float>(1, 2, 3)) == quat<float>(1, 2, 3, 0));
			REQUIRE(quat<float>(vec3<float>(1, 2, 3), 4) == quat<float>(1, 2, 3, 4));
		}
		SUBCASE("addition and subtraction") {
			quat<float> q2(5, 6, 7, 8);
			REQUIRE(q1 + q2 == quat<float>(6, 8, 10, 12));
			REQUIRE(q2 - q1 == quat<float>(4, 4, 4, 4));
		}
		SUBCASE("scalar multiplication and division") {
			REQUIRE(q1 * 2 == quat<float>(2, 4, 6, 8));
			REQUIRE(q1 / 2 == quat<float>(1 / 2.0, 2 / 2.0, 3 / 2.0, 4 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-q1 == quat<float>(-1, -2, -3, -4)); }
		SUBCASE("equality") { REQUIRE(q1 == quat<float>(1, 2, 3, 4)); }
		SUBCASE("inequality") { REQUIRE(q1 != quat<float>(4, 3, 2, 1)); }
		SUBCASE("inner product") {
			REQUIRE(q1.inner_product(q1) == Approx(30));
			REQUIRE(inner_product(q1, q1) == Approx(30));
		}
		SUBCASE("length") { REQUIRE(q1.length() == Approx(5.47722557505)); }
		SUBCASE("normalization") {
			quat<float> normalized = q1.normalized();
			REQUIRE(normalized.x == Approx(0.18257418583));
			REQUIRE(normalized.y == Approx(0.36514837167));
			REQUIRE(normalized.z == Approx(0.54772255750));
			REQUIRE(normalized.w == Approx(0.73029674334));
		}
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
		SUBCASE("compound assignment") {
			quat<float> q2(5, 6, 7, 8);

			auto sum = q1;
			sum += q2;
			REQUIRE(sum == quat<float>(6, 8, 10, 12));
			sum -= q1;
			REQUIRE(sum == q2);

			auto scaled = q1;
			scaled *= 2;
			REQUIRE(scaled == quat<float>(2, 4, 6, 8));
			scaled /= 2;
			REQUIRE(scaled == q1);

			auto product = q1;
			product *= q2;
			REQUIRE(product == q1 * q2);
		}
		SUBCASE("construction from Euler angles") {
			quat<float> q2         = quat<float>::from_euler(1, 2, 3);
			quat<float> normalized = q2.normalized();
			REQUIRE(normalized.x == Approx(-0.718287));
			REQUIRE(normalized.y == Approx(0.3106225));
			REQUIRE(normalized.z == Approx(0.4444351));
			REQUIRE(normalized.w == Approx(0.4359528));
		}
		SUBCASE("construction for axis-angle") {
			quat<float> q2         = quat<float>::from_axis({1, 2, 3}, 4);
			quat<float> normalized = q2.normalized();
			REQUIRE(normalized.x == Approx(0.24302));
			REQUIRE(normalized.y == Approx(0.4860399));
			REQUIRE(normalized.z == Approx(0.7290599));
			REQUIRE(normalized.w == Approx(-0.4161468));
		}
		SUBCASE("axis-angle construction normalizes the axis") {
			const quat<float> q2 = quat<float>::from_axis({2, 0, 0}, 1);
			const quat<float> q3 = quat<float>::from_axis({1, 0, 0}, 1);
			REQUIRE(q2.x == Approx(q3.x));
			REQUIRE(q2.y == Approx(q3.y));
			REQUIRE(q2.z == Approx(q3.z));
			REQUIRE(q2.w == Approx(q3.w));
		}
		SUBCASE("identity rotation") {
			const quat<float> identity = quat<float>::from_euler(0, 0, 0);
			REQUIRE(identity.x == Approx(0));
			REQUIRE(identity.y == Approx(0));
			REQUIRE(identity.z == Approx(0));
			REQUIRE(identity.w == Approx(1));
			REQUIRE(identity.to_mat3() ==
			        mat3<float>({1, 0, 0}, {0, 1, 0}, {0, 0, 1}));
			REQUIRE(
			  identity.to_mat4() ==
			  mat4<float>({1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}));
		}
		SUBCASE("conversion operators") {
			REQUIRE(static_cast<vec4<float>>(q1) == vec4<float>(1, 2, 3, 4));
			REQUIRE(static_cast<mat3<float>>(q1) == q1.to_mat3());
			REQUIRE(static_cast<mat4<float>>(q1) == q1.to_mat4());
		}
		SUBCASE("index access") {
			REQUIRE(q1[0] == 1);
			REQUIRE(q1[1] == 2);
			REQUIRE(q1[2] == 3);
			REQUIRE(q1[3] == 4);
			q1[0] = 5;
			q1[1] = 6;
			q1[2] = 7;
			q1[3] = 8;
			REQUIRE(q1 == quat<float>(5, 6, 7, 8));

			const quat<float> cq(1, 2, 3, 4);
			REQUIRE(cq[0] == 1);
			REQUIRE(cq[1] == 2);
			REQUIRE(cq[2] == 3);
			REQUIRE(cq[3] == 4);
		}
		SUBCASE("index bounds checks") {
			const quat<float> cq(1, 2, 3, 4);
			REQUIRE_THROWS_AS(q1[4], std::out_of_range);
			REQUIRE_THROWS_AS(cq[-1], std::out_of_range);
		}
	}

	TEST_CASE("api: default matrices behave as identity transforms") {
		SUBCASE("mat2 preserves 2D directions") {
			const mat2<float> transform;
			const vec2<float> direction(3, -4);

			REQUIRE(transform * direction == direction);
			REQUIRE(direction * transform == direction);
		}

		SUBCASE("mat3 preserves 2D homogeneous points") {
			const mat3<float> transform;
			const vec3<float> point(3, -4, 1);

			REQUIRE(transform * point == point);
			REQUIRE(point * transform == point);
		}

		SUBCASE("mat4 preserves 3D homogeneous points") {
			const mat4<float> transform;
			const vec4<float> point(3, -4, 5, 1);

			REQUIRE(transform * point == point);
			REQUIRE(point * transform == point);
		}

		SUBCASE("mat4 composes as identity") {
			const mat4<float> identity;
			const mat4<float> transform(
			  {1, 0, 0, 5}, {0, 1, 0, -2}, {0, 0, 1, 7}, {0, 0, 0, 1});

			REQUIRE(identity * transform == transform);
			REQUIRE(transform * identity == transform);
		}
	}

	TEST_CASE(
	  "api: homogeneous transforms translate points from the last column") {
		SUBCASE("mat3 translates 2D points") {
			const mat3<float> translate({1, 0, 5}, {0, 1, -2}, {0, 0, 1});
			const vec3<float> point(1, 2, 1);

			REQUIRE(translate * point == vec3<float>(6, 0, 1));
		}

		SUBCASE("mat3 does not translate 2D directions") {
			const mat3<float> translate({1, 0, 5}, {0, 1, -2}, {0, 0, 1});
			const vec3<float> direction(1, 2, 0);

			REQUIRE(translate * direction == direction);
		}

		SUBCASE("mat4 translates 3D points") {
			const mat4<float> translate(
			  {1, 0, 0, 5}, {0, 1, 0, -2}, {0, 0, 1, 7}, {0, 0, 0, 1});
			const vec4<float> point(1, 2, 3, 1);

			REQUIRE(translate * point == vec4<float>(6, 0, 10, 1));
		}

		SUBCASE("mat4 does not translate 3D directions") {
			const mat4<float> translate(
			  {1, 0, 0, 5}, {0, 1, 0, -2}, {0, 0, 1, 7}, {0, 0, 0, 1});
			const vec4<float> direction(1, 2, 3, 0);

			REQUIRE(translate * direction == direction);
		}
	}

	TEST_CASE("api: float math types accept integer literal left scaling") {
		SUBCASE("vec2") {
			require_int_left_multiply(
			  vec2<float>(1, 2),
			  vec2<float>(2, 4),
			  "vec2<float> should accept `2 * v` without `2.0f`");
		}

		SUBCASE("vec3") {
			require_int_left_multiply(
			  vec3<float>(1, 2, 3),
			  vec3<float>(2, 4, 6),
			  "vec3<float> should accept `2 * v` without `2.0f`");
		}

		SUBCASE("vec4") {
			require_int_left_multiply(
			  vec4<float>(1, 2, 3, 4),
			  vec4<float>(2, 4, 6, 8),
			  "vec4<float> should accept `2 * v` without `2.0f`");
		}

		SUBCASE("mat2") {
			require_int_left_multiply(
			  mat2<float>({1, 2}, {3, 4}),
			  mat2<float>({2, 4}, {6, 8}),
			  "mat2<float> should accept `2 * m` without `2.0f`");
		}

		SUBCASE("mat3") {
			require_int_left_multiply(
			  mat3<float>({1, 2, 3}, {4, 5, 6}, {7, 8, 9}),
			  mat3<float>({2, 4, 6}, {8, 10, 12}, {14, 16, 18}),
			  "mat3<float> should accept `2 * m` without `2.0f`");
		}

		SUBCASE("mat4") {
			require_int_left_multiply(
			  mat4<float>(
			    {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}),
			  mat4<float>(
			    {2, 4, 6, 8}, {10, 12, 14, 16}, {18, 20, 22, 24}, {26, 28, 30, 32}),
			  "mat4<float> should accept `2 * m` without `2.0f`");
		}
	}

	TEST_CASE("api: scalar predivision is not exposed for vectors and matrices") {
		SUBCASE("vec2") {
			require_scalar_predivide_absent<vec2<float>>(
			  "`scalar / vec2` is surprising and should not exist");
		}

		SUBCASE("vec3") {
			require_scalar_predivide_absent<vec3<float>>(
			  "`scalar / vec3` is surprising and should not exist");
		}

		SUBCASE("vec4") {
			require_scalar_predivide_absent<vec4<float>>(
			  "`scalar / vec4` is surprising and should not exist");
		}

		SUBCASE("mat2") {
			require_scalar_predivide_absent<mat2<float>>(
			  "`scalar / mat2` is surprising and should not exist");
		}

		SUBCASE("mat3") {
			require_scalar_predivide_absent<mat3<float>>(
			  "`scalar / mat3` is surprising and should not exist");
		}

		SUBCASE("mat4") {
			require_scalar_predivide_absent<mat4<float>>(
			  "`scalar / mat4` is surprising and should not exist");
		}
	}

	TEST_CASE("api: vector-vector products stay explicit") {
		SUBCASE("operator multiply is not used for vector-vector products") {
			REQUIRE_FALSE_MESSAGE(
			  (supports_direct_product<vec2<float>, vec2<float>>),
			  "`vec * vec` is ambiguous in engine code; use named products instead");
			REQUIRE_FALSE_MESSAGE(
			  (supports_direct_product<vec3<float>, vec3<float>>),
			  "`vec * vec` is ambiguous in engine code; use named products instead");
			REQUIRE_FALSE_MESSAGE(
			  (supports_direct_product<vec4<float>, vec4<float>>),
			  "`vec * vec` is ambiguous in engine code; use named products instead");
		}

		SUBCASE("named products remain available") {
			REQUIRE(inner_product(vec2<float>(1, 2), vec2<float>(3, 4)) == 11.0f);
			REQUIRE(outer_product(vec2<float>(1, 2), vec2<float>(3, 4)) ==
			        mat2<float>({3, 4}, {6, 8}));
		}
	}

	TEST_CASE("api: vector pre multiplication follows row vector semantics") {
		SUBCASE("mat2") {
			const mat2<float> transform({1, 2}, {3, 4});
			const vec2<float> vector(1, 2);

			REQUIRE(transform * vector == vec2<float>(5, 11));
			REQUIRE(vector * transform == vec2<float>(7, 10));
		}

		SUBCASE("mat3") {
			const mat3<float> transform({1, 2, 3}, {4, 5, 6}, {7, 8, 9});
			const vec3<float> vector(1, 2, 1);

			REQUIRE(transform * vector == vec3<float>(8, 20, 32));
			REQUIRE(vector * transform == vec3<float>(16, 20, 24));
		}

		SUBCASE("mat4") {
			const mat4<float> transform(
			  {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16});
			const vec4<float> vector(1, 2, 3, 1);

			REQUIRE(transform * vector == vec4<float>(18, 46, 74, 102));
			REQUIRE(vector * transform == vec4<float>(51, 58, 65, 72));
		}
	}

	TEST_CASE("api: related types expose consistent compound assignment") {
		SUBCASE("all matrix sizes support +=") {
			REQUIRE((supports_add_assign<mat2<float>>));
			REQUIRE((supports_add_assign<mat3<float>>));
			REQUIRE((supports_add_assign<mat4<float>>));
		}

		SUBCASE("all matrix sizes support -=") {
			REQUIRE((supports_sub_assign<mat2<float>>));
			REQUIRE((supports_sub_assign<mat3<float>>));
			REQUIRE((supports_sub_assign<mat4<float>>));
		}

		SUBCASE("all matrix sizes support scalar *= and /=") {
			REQUIRE((supports_float_mul_assign<mat2<float>>));
			REQUIRE((supports_float_div_assign<mat2<float>>));
			REQUIRE((supports_float_mul_assign<mat3<float>>));
			REQUIRE((supports_float_div_assign<mat3<float>>));
			REQUIRE((supports_float_mul_assign<mat4<float>>));
			REQUIRE((supports_float_div_assign<mat4<float>>));
		}

		SUBCASE("quaternion compound assignment supports chaining") {
			REQUIRE((supports_add_assign<quat<float>>));
			REQUIRE((supports_sub_assign<quat<float>>));
			REQUIRE((supports_mul_assign<quat<float>>));
			REQUIRE((supports_float_mul_assign<quat<float>>));
			REQUIRE((supports_float_div_assign<quat<float>>));
		}
	}

	TEST_CASE("api: const vectors expose geometric helpers") {
		REQUIRE_MESSAGE(
		  (supports_const_perp_inner_product<float>),
		  "`vec2::perp_inner_product()` should be callable on const vectors like "
		  "other queries");
	}

	TEST_CASE("api: default quaternion is the identity rotation") {
		const quat<float> rotation;

		REQUIRE(rotation.x == Approx(0.0f));
		REQUIRE(rotation.y == Approx(0.0f));
		REQUIRE(rotation.z == Approx(0.0f));
		REQUIRE(rotation.w == Approx(1.0f));
	}

	TEST_CASE("api: default quaternion normalizes and converts safely") {
		const quat<float> rotation;

		SUBCASE("normalization is finite and still identity") {
			const quat<float> normalized = rotation.normalized();

			REQUIRE(std::isfinite(normalized.x));
			REQUIRE(std::isfinite(normalized.y));
			REQUIRE(std::isfinite(normalized.z));
			REQUIRE(std::isfinite(normalized.w));

			REQUIRE(normalized.x == Approx(0.0f));
			REQUIRE(normalized.y == Approx(0.0f));
			REQUIRE(normalized.z == Approx(0.0f));
			REQUIRE(normalized.w == Approx(1.0f));
		}

		SUBCASE("3x3 conversion preserves directions") {
			const vec3<float> direction(2, -3, 4);
			const vec3<float> transformed = rotation.to_mat3() * direction;

			REQUIRE(std::isfinite(transformed.x));
			REQUIRE(std::isfinite(transformed.y));
			REQUIRE(std::isfinite(transformed.z));
			check_close(transformed, direction);
		}

		SUBCASE("4x4 conversion preserves homogeneous points") {
			const vec4<float> point(2, -3, 4, 1);
			const vec4<float> transformed = rotation.to_mat4() * point;

			REQUIRE(std::isfinite(transformed.x));
			REQUIRE(std::isfinite(transformed.y));
			REQUIRE(std::isfinite(transformed.z));
			REQUIRE(std::isfinite(transformed.w));
			check_close(transformed, point);
		}
	}

	TEST_CASE("api: axis angle rotations use the right hand rule") {
		const quat<float> rotation = quat<float>::from_axis({0, 0, 1}, half_pi);
		const vec3<float> right(1, 0, 0);
		const vec3<float> rotated = rotation.to_mat3() * right;

		check_close(rotated, vec3<float>(0, 1, 0));
	}

	TEST_CASE("api: euler factory matches its named axes") {
		SUBCASE("roll rotates around x") {
			const vec3<float> up(0, 1, 0);
			const vec3<float> rotated =
			  quat<float>::from_euler(half_pi, 0.0f, 0.0f).to_mat3() * up;

			check_close(rotated, vec3<float>(0, 0, 1));
		}

		SUBCASE("pitch rotates around y") {
			const vec3<float> forward(0, 0, 1);
			const vec3<float> rotated =
			  quat<float>::from_euler(0.0f, half_pi, 0.0f).to_mat3() * forward;

			check_close(rotated, vec3<float>(1, 0, 0));
		}

		SUBCASE("yaw rotates around z") {
			const vec3<float> right(1, 0, 0);
			const vec3<float> rotated =
			  quat<float>::from_euler(0.0f, 0.0f, half_pi).to_mat3() * right;

			check_close(rotated, vec3<float>(0, 1, 0));
		}
	}

	TEST_CASE("api: quaternion composition matches sequential transform order") {
		const quat<float> yaw  = quat<float>::from_axis({0, 1, 0}, half_pi);
		const quat<float> roll = quat<float>::from_axis({0, 0, 1}, half_pi);
		const vec3<float> forward(0, 0, 1);

		const vec3<float> sequential = roll.to_mat3() * (yaw.to_mat3() * forward);
		const vec3<float> combined   = (roll * yaw).to_mat3() * forward;

		check_close(combined, sequential);
		check_close(combined, vec3<float>(0, 1, 0));
	}

	TEST_CASE("api: quaternions rotate direction vectors directly") {
		require_direct_product(
		  quat<float>::from_axis({0, 0, 1}, half_pi),
		  vec3<float>(1, 0, 0),
		  vec3<float>(0, 1, 0),
		  "Game-engine math APIs should allow direct quaternion-vector rotation");
	}
}
