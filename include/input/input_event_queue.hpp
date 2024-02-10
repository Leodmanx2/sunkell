// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "common/event.hpp"
#include "input/input_events.hpp"

#include <functional>
#include <queue>
#include <stdexcept>

#ifdef SUNKELL_PLATFORM_WIN32
#include <windows.h>
using sunkell::input_event_queue =
  sunkell::input_event_queue<sunkell::Platform::Win32>;
#endif

namespace sunkell {

	enum class Platform { Win32 };

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const std::string& message)
		  : std::runtime_error(message) {}
	};

	class input_poll_failure : public std::runtime_error {
		public:
		explicit input_poll_failure(const std::string& message)
		  : std::runtime_error(message) {}
	};

	template <Platform T>
	class input_event_queue {
		// This template will only be used if there is no explicit specialization
		// for the given platform T. If there is no explicit specialization, it
		// means the platform is not supported and we want the compilation to fail.
		static_assert(false,
		              "input_event_queue declared with unsupported platform");
	};

	template <>
	class input_event_queue<Platform::Win32> {
		using callback_map = std::unordered_multimap<event, std::function<void()>>;
		callback_map m_callback;

		std::queue<event> m_event_queue;

		// The position from the previous mouse event needs to be stored so that
		// the delta can be calculated.
		// There will only be one cursor per system, so it is safe to make this
		// static, which enables the translation functions to be constexpr.
		static vec2<int> s_last_mouse_position;

		constexpr key_event   translate_keyboard_input(const RAWINPUT& input) const;
		constexpr mouse_event translate_mouse_input(const RAWINPUT& input) const;
		constexpr event       translate_input(const RAWINPUT& input) const;

		void register_raw_input_devices();

		public:
		input_event_queue();

		void
		poll(); // TODO: Make the other functions poll if the queue is looking empty
		void  dispatch_next_event();
		event peek_next_event();
		void  skip_next_event();

		callback_map::iterator
		register_callback(event event, const std::function<void(void)> callback);
		void unregister_callback(callback_map::iterator iterator);
	};

} // namespace sunkell
