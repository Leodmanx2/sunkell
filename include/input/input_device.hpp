// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"
#include <functional>
#include <iterator>

namespace sunkell {

	// input_device is an interface providing unified access to keyboard, mouse,
	// controller, and other input devices.
	class input_device {
		protected:
		using key_state = std::pair<button, button_state>;
		using callback = std::function<void(button)>;
		using callback_map = std::unordered_multimap<key_state, callback>;
		using callback_iterator = callback_map::iterator;

		callback_map m_callbacks;

		public:
		virtual ~input_device() = default;

		virtual callback_iterator pressed_callback(const callback& callback) {
			return m_callbacks.emplace(button_state::pressed, callback);
		}

		virtual callback_iterator released_callback(const callback& callback) {
			return m_callbacks.emplace(button_state::released, callback);
		}

		// Pause processing of device inputs so the game's data isn't updated mid-render or subsystem update.
		virtual void pause_processing() = 0;
		virtual void resume_processing() = 0;
	};

} // namespace sunkell
