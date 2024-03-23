// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "common/event.hpp"
#include "common/math/vec2.hpp"
#include "input/input_enums.hpp"

namespace sunkell {

	class key_event final : public event {
		button       m_button;
		button_state m_state;

		public:
		constexpr key_event(enum button button, button_state state)
		  : m_button(button), m_state(state) {}

		[[nodiscard]] constexpr enum button  button() const { return m_button; }
		[[nodiscard]] constexpr button_state state() const { return m_state; }
	};

	// The operating system polls mice for their current state and passes along
	// all the information at once. Sunkell does the same in order to avoid
	// adding any global state to the system. Generating individual button or
	// movement events would require storing the previous state of the mouse
	// and comparing it to the current state, which would require global state.
	class mouse_event final : public event {
		vec2<int>    m_position;
		vec2<int>    m_delta;
		double       m_scroll_delta;
		button_state m_left_button_state;
		button_state m_right_button_state;
		button_state m_middle_button_state;
		button_state m_x1_button_state;
		button_state m_x2_button_state;

		public:
		constexpr mouse_event(vec2<int>    position,
		                      vec2<int>    delta,
		                      double       scroll_delta,
		                      button_state left_button_state,
		                      button_state right_button_state,
		                      button_state middle_button_state,
		                      button_state x1_button_state,
		                      button_state x2_button_state)
		  : m_position(position)
		  , m_delta(delta)
		  , m_scroll_delta(scroll_delta)
		  , m_left_button_state(left_button_state)
		  , m_right_button_state(right_button_state)
		  , m_middle_button_state(middle_button_state)
		  , m_x1_button_state(x1_button_state)
		  , m_x2_button_state(x2_button_state) {}

		[[nodiscard]] constexpr vec2<int> position() const { return m_position; }
		[[nodiscard]] constexpr vec2<int> delta() const { return m_delta; }
		[[nodiscard]] constexpr double    scroll_delta() const {
      return m_scroll_delta;
		}
		[[nodiscard]] constexpr button_state left_button_state() const {
			return m_left_button_state;
		}
		[[nodiscard]] constexpr button_state right_button_state() const {
			return m_right_button_state;
		}
		[[nodiscard]] constexpr button_state middle_button_state() const {
			return m_middle_button_state;
		}
		[[nodiscard]] constexpr button_state x1_button_state() const {
			return m_x1_button_state;
		}
		[[nodiscard]] constexpr button_state x2_button_state() const {
			return m_x2_button_state;
		}
	};

} // namespace sunkell
