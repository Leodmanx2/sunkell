// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input/input_device_win32.hpp"

#include <stdexcept>

namespace sunkell {

	input_device::input_device(HWND target_window)
	  : m_target_window(target_window) {
		if(!RegisterRawInputDevices(&m_target_window, 1, sizeof(RAWINPUTDEVICE))) {
			throw device_registration_error("could not register device");
		}
	}

	input_device::callback_iterator input_device::register_callback(
	  button button, button_state state, const callback& callback) {
		return m_callbacks.emplace(std::make_pair(button, state), callback);
	}

	void input_device::unregister_callback(callback_iterator iterator) {
		m_callbacks.erase(iterator);
	}

	void input_device::pause_processing() {
		throw std::logic_error("not implemented");
	}

	void input_device::resume_processing() {
		throw std::logic_error("not implemented");
	}

} // namespace sunkell
