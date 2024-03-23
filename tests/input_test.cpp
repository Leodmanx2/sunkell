// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input.hpp"

#include <doctest/doctest.h>

#ifdef SUNKELL_PLATFORM_WIN32
#include <windows.h>
#endif // SUNKELL_PLATFORM_WIN32

using namespace sunkell;

TEST_SUITE("input") {
#ifdef SUNKELL_PLATFORM_WIN32
	TEST_CASE("input event triggers callback") {
		input_event_queue                queue;
		const std::shared_ptr<key_event> trigger_event =
		  std::make_shared<key_event>(button::a, button_state::down);
		int  i        = 0;
		auto callback = [&i](std::shared_ptr<event> e) -> void { i = 1; };
		auto receipt  = queue.register_callback(trigger_event, callback);

		// Simulate keyboard input
		INPUT input;
		input.type           = INPUT_KEYBOARD;
		input.ki.wVk         = 'A';
		input.ki.dwFlags     = 0;
		input.ki.time        = 0;
		input.ki.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(INPUT));

		queue.poll();
		queue.dispatch_next_event();
		REQUIRE(i == 1);
	}
#endif // SUNKELL_PLATFORM_WIN32
}
