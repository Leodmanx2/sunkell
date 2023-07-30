// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"

#include <functional>
#include <stdexcept>

namespace sunkell {

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const char* message)
		  : std::runtime_error(message) {}
	};

	template <typename Derived>
	class input_device_interface {
		using key_state         = std::pair<button, button_state>;
		using callback          = std::function<void()>;
		using callback_map      = std::unordered_multimap<key_state, callback>;
		using callback_iterator = callback_map::iterator;

		public:
		constexpr void pause_processing() {
			static_cast<Derived*>(this)->pause_processing();
		}

		constexpr void resume_processing() {
			static_cast<Derived*>(this)->resume_processing();
		}

		inline callback_iterator register_callback(button          button,
		                                           button_state    state,
		                                           const callback& callback) {
			static_cast<Derived*>(this)->register_callback(button, state, callback);
		}

		inline void unregister_callback(callback_iterator iterator) {
			static_cast<Derived*>(this)->unregister_callback(iterator);
		}
	};

} // namespace sunkell
