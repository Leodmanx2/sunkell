// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input/input_event_queue.hpp"

#include <doctest/doctest.h>

using namespace sunkell;

TEST_SUITE("input") {
	TEST_CASE("register callback") {
		// We don't have access to the underlying container, so we can't check
		// if the callback was added. We can only check if the iterator is
		// valid.
		input_event_queue queue;
		const event       e;
		int               i  = 0;
		auto              fn = [&i](event e) -> void { i = 1; };
		auto              it = queue.register_callback(e, fn);
		it->second(e);
		REQUIRE(i == 1);
	}
	TEST_CASE("unregister callback") {
		// We don't have access to the underlying container, so we can't check
		// if the callback was removed. We can only check that the iterator is
		// no longer valid.
		input_event_queue queue;
		const event       e;
		auto              fn = [](event e) -> void {};
		auto              it = queue.register_callback(e, fn);
		queue.unregister_callback(it);
		REQUIRE_THROWS_AS(it->second(e), std::out_of_range);
	}
}
