// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "common/event.hpp"
#include "common/math/vec2.hpp"
#include "input/input_enums.hpp"

#if SUNKELL_PLATFORM == SUNKELL_PLATFORM_WIN32
#include <windows.h>
#else
#error "Unsupported platform"
#endif

namespace sunkell {

	struct key_event final : public event {
		const button       button;
		const button_state state;
		constexpr key_event(enum button button, button_state state)
		  : button(button), state(state) {}
	};

	// The operating system polls mice for their current state and passes along
	// all the information at once. Sunkell does the same in order to avoid
	// adding any global state to the system. Generating individual button or
	// movement events would require storing the previous state of the mouse
	// and comparing it to the current state, which would require global state.
	struct mouse_event final : public event {
		const vec2<int>    position;
		const vec2<int>    delta;
		const int          scroll_delta;
		const button_state left_button_state;
		const button_state right_button_state;
		const button_state middle_button_state;
		const button_state x1_button_state;
		const button_state x2_button_state;

		constexpr mouse_event(vec2<int>    position,
		                      vec2<int>    delta,
		                      int          scroll_delta,
		                      button_state left_button_state,
		                      button_state right_button_state,
		                      button_state middle_button_state,
		                      button_state x1_button_state,
		                      button_state x2_button_state)
		  : position(position)
		  , delta(delta)
		  , scroll_delta(scroll_delta)
		  , left_button_state(left_button_state)
		  , right_button_state(right_button_state)
		  , middle_button_state(middle_button_state)
		  , x1_button_state(x1_button_state)
		  , x2_button_state(x2_button_state) {}
	};

#if SUNKELL_PLATFORM == SUNKELL_PLATFORM_WIN32
	constexpr event translate_event(const RAWINPUT& input);
#endif

} // namespace sunkell
