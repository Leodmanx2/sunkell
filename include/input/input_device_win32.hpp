// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"

#include <functional>
#include <stdexcept>
#include <windows.h>

namespace sunkell {

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const char* message)
		  : std::runtime_error(message) {}
	};

	class input_device {
		using key_state         = std::pair<button, button_state>;
		using callback          = std::function<void()>;
		using callback_map      = std::unordered_multimap<key_state, callback>;
		using callback_iterator = callback_map::iterator;

		callback_map m_callbacks;

		constexpr key_state translate_keyboard_input(const RAWINPUT& input) const;
		constexpr key_state translate_mouse_input(const RAWINPUT& input) const;
		constexpr key_state translate_input(const RAWINPUT& input) const;

		public:
		explicit input_device();

		void poll();

		callback_iterator register_callback(button          button,
		                                    button_state    state,
		                                    const callback& callback);
		void              unregister_callback(callback_iterator iterator);

		void pause_processing();

		void resume_processing();
	};

} // namespace sunkell
