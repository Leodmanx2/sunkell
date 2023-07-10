// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input/input_device_windows.hpp"

#include <stdexcept>

namespace sunkell {

	input_device_windows::input_device_windows(const Window& window) {
		// Register keyboard
		RAWINPUTDEVICE keyboard;
		keyboard.usUsagePage = 0x01;
		keyboard.usUsage     = 0x06;
		keyboard.dwFlags     = 0;
		keyboard.hwndTarget  = window;

		if(!RegisterRawInputDevices(&keyboard, 1, sizeof(keyboard))) {
			throw device_registration_error("Failed to register keyboard device");
		}

		// Register mouse
		RAWINPUTDEVICE mouse;
		mouse.usUsagePage = 0x01;
		mouse.usUsage     = 0x02;
		mouse.dwFlags     = 0;
		mouse.hwndTarget  = window;
		if(!RegisterRawInputDevices(&mouse, 1, sizeof(mouse))) {
			throw device_registration_error("Failed to register mouse device");
		}
	}

	input_device_windows::~input_device_windows() {
		// Register keyboard
		RAWINPUTDEVICE keyboard;
		keyboard.usUsagePage = 0x01;
		keyboard.usUsage     = 0x06;
		keyboard.dwFlags     = 0;
		keyboard.hwndTarget  = 0;
		RegisterRawInputDevices(&keyboard, 1, sizeof(keyboard));

		// Register mouse
		RAWINPUTDEVICE mouse;
		mouse.usUsagePage = 0x01;
		mouse.usUsage     = 0x02;
		mouse.dwFlags     = 0;
		mouse.hwndTarget  = 0;
		RegisterRawInputDevices(&mouse, 1, sizeof(mouse));
	}

} // namespace sunkell
