// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input/input_device_windows.hpp"

#include <functional>
#include <stdexcept>

namespace sunkell {

	input_device_windows::input_device_windows(HWND window) {
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

	void input_device_windows::update() {
		MSG msg;
		while(PeekMessage(&msg, m_target_window, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	LRESULT CALLBACK input_device_windows::window_proc(HWND   hwnd,
	                                                   UINT   msg,
	                                                   WPARAM wparam,
	                                                   LPARAM lparam) {
		switch(msg) {
			case WM_CHAR:
				// TODO: update keyboard state
				// There are other events like WM_DESTROY that we must process as well
				return 0;
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

} // namespace sunkell
