// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input/input_device_windows.hpp"

#include <functional>
#include <stdexcept>

namespace sunkell {

	input_device_windows::input_device_windows() : m_target_window(winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread()) {
		m_target_window.KeyDown(key_down_callback);
		m_target_window.KeyUp(key_up_callback);
	}

	input_device_windows::~input_device_windows() {
		m_target_window.KeyDown(nullptr);
		m_target_window.KeyUp(nullptr);
	}

	void input_device_windows::update() {
		
	}

} // namespace sunkell
