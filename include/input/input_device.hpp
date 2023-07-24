// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"

namespace sunkell {

	// input_device is an interface providing unified access to keyboard, mouse,
	// controller, and other input devices.
	class input_device {
		protected:
		using key_state = std::pair<button, button_state>;

		std::unordered_multimap<key_state, std::function<void(button)>>
		  m_callbacks;

		public:
		virtual ~input_device() = default;

		// Called once per frame to update the device state
		virtual void update() = 0;

		// pressed() and released() return true only if the button's state changed
		// on the current update
		virtual bool pressed(button button)  = 0;
		virtual bool released(button button) = 0;

		virtual bool is_down(button button) = 0;
		virtual bool is_up(button button)   = 0;

		virtual void pressed_callback(const std::function<void(button)>& callback) {
			m_callbacks.emplace(button_state::pressed, callback);
		}

		virtual void released_callback(const std::function<void(button)>& callback) {
			m_callbacks.emplace(button_state::released, callback);
		}

		// TODO: Add a callback to be called when a mouse, stick, or trigger axis moves
		/* virtual void callback(axis                                axis,
			std::function<void(decltype(axis))> callback) {
			m_callbacks.emplace(axis, callback);
		}*/
	};

} // namespace sunkell
