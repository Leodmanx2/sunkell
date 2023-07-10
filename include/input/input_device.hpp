// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"

namespace sunkell {

	// Forward declaration
	class Window;

	// input_device is an interface providing unified access to keyboard, mouse,
	// controller, and other input devices.
	class input_device {
		public:
		input_device(const Window& window);
		virtual ~input_device() = default;

		// Called once per frame to update the device state
		virtual void update() = 0;

		// pressed() and released() return true only if the button's state changed
		// on the current update
		virtual bool pressed(button button)  = 0;
		virtual bool released(button button) = 0;

		virtual bool is_down(button button) = 0;
		virtual bool is_up(button button)   = 0;
	};

} // namespace sunkell
