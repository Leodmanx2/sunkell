// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "entity-component-system.hpp"

#include <doctest/doctest.h>

using namespace sunkell;

class test_component : public component {
	public:
	test_component() = default;
};

TEST_SUITE("entity component system") {
	TEST_CASE("entity") {
		entity e;
		SUBCASE("add component that doesn't exist") {
			e.add_component(std::make_shared<test_component>());
			REQUIRE(e.get_component<test_component>() != nullptr);
		}
		SUBCASE("add component that exists") {
			e.add_component(std::make_shared<test_component>());
			std::shared_ptr c = std::make_shared<test_component>();
			e.add_component(c);
			REQUIRE(e.get_component<test_component>() == c);
		}
		SUBCASE("remove component that doesn't exist") {
			e.remove_component<test_component>();
			REQUIRE(e.get_component<test_component>() == nullptr);
		}
		SUBCASE("remove component that exists") {
			e.add_component(std::make_shared<test_component>());
			e.remove_component<test_component>();
			REQUIRE(e.get_component<test_component>() == nullptr);
		}
		SUBCASE("get component that doesn't exist") {
			REQUIRE(e.get_component<test_component>() == nullptr);
		}
		SUBCASE("get component that exists") {
			e.add_component(std::make_shared<test_component>());
			REQUIRE(e.get_component<test_component>() != nullptr);
		}
	}
}
