// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input.hpp"

#include <doctest/doctest.h>

#ifdef SUNKELL_PLATFORM_WIN32
#include "common/windowing.hpp"

#include <windows.h>

TEST_CASE("input queue receives events") {
	// Create a window in the same thread as the queue
	sunkell::window_builder builder;
	builder.width(800).height(600).title("Test Window");
	auto window = builder.build();

	// Show the window
	window.show();

	// Ensure the window is in keyboard focus
	window.focus();

	// Initialize the queue
	sunkell::input_event_queue queue;

	// Send a simulated 'a' button press to the window
	INPUT input          = {};
	input.type           = INPUT_KEYBOARD;
	input.ki.wVk         = 0x41;
	input.ki.dwFlags     = 0;
	input.ki.time        = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wScan       = MapVirtualKey(0x41, MAPVK_VK_TO_VSC);
	SendInput(1, &input, sizeof(INPUT));

	queue.poll();

	// Ensure the queue has received the event
	// There may be other events in the queue, so we need to look for the one we sent
	bool found = false;
	while(!queue.empty()) {
		auto event     = queue.peek_next_event();
		auto key_event = std::dynamic_pointer_cast<sunkell::key_event>(event);
		if(key_event && key_event->button() == sunkell::button::a) {
			found = true;
			break;
		}
		queue.skip_next_event();
	}
	REQUIRE(found);
}

#endif // SUNKELL_PLATFORM_WIN32

using namespace sunkell;
