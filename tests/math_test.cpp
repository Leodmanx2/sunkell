// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "common/math.hpp"

using namespace sunkell;

#include <doctest/doctest.h>

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
		SUBCASE("length") { REQUIRE(length(v1) == doctest::Approx(2.2360679775)); }
		SUBCASE("normalize") {
			const vec2<float> norm = normalize(v1);
			REQUIRE(length(norm) == doctest::Approx(1));
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
		SUBCASE("length") { REQUIRE(length(v1) == doctest::Approx(3.74165738677)); }
		SUBCASE("normalize") {
			const vec3<float> norm = normalize(v1);
			REQUIRE(length(norm) == doctest::Approx(1));
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
		SUBCASE("length") { REQUIRE(length(v1) == doctest::Approx(5.47722557505)); }
		SUBCASE("normalize") {
			const vec4<float> norm = normalize(v1);
			REQUIRE(length(norm) == doctest::Approx(1));
		}
		SUBCASE("class dos not consume extra memory") {
			REQUIRE(sizeof(vec4<float>) == sizeof(float) * 4);
		}
	}
	TEST_CASE("mat2") {
		mat2<float> m1(1, 2, 3, 4);
		mat2<float> m2(5, 6, 7, 8);

		SUBCASE("matrix addition") {
			REQUIRE(m1 + m2 == mat2<float>(6, 8, 10, 12));
		}
		SUBCASE("matrix subtraction") {
			REQUIRE(m1 - m2 == mat2<float>(-4, -4, -4, -4));
		}
		SUBCASE("scalar multiplication") {
			REQUIRE(m1 * 2 == mat2<float>(2, 4, 6, 8));
		}
		SUBCASE("scalar division") {
			REQUIRE(m1 / 2 == mat2<float>(1 / 2.0, 2 / 2.0, 3 / 2.0, 4 / 2.0));
		}
		SUBCASE("negation") { REQUIRE(-m1 == mat2<float>(-1, -2, -3, -4)); }
		SUBCASE("equality") { REQUIRE(m1 == mat2<float>(1, 2, 3, 4)); }
		SUBCASE("inequality") { REQUIRE(m1 != mat2<float>(2, 2, 2, 2)); }
		SUBCASE("matrix multiplication") {
			REQUIRE(m1 * m2 == mat2<float>(19, 22, 43, 50));
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
}
