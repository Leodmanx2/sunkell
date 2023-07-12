// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_device.hpp"

#include <Windows.h>
#include <minwindef.h>
#include <stdexcept>

namespace sunkell {

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const char* message)
		  : std::runtime_error(message) {}
	};

	class input_device_windows : public input_device {
		HWND             m_target_window;
		LRESULT CALLBACK window_proc(HWND   hwnd,
		                             UINT   msg,
		                             WPARAM wparam,
		                             LPARAM lparam);

		public:
		explicit input_device_windows(HWND window);
		virtual ~input_device_windows();

		virtual void update() override;

		virtual bool pressed(button button) override;
		virtual bool released(button button) override;

		virtual bool is_down(button button) override;
		virtual bool is_up(button button) override;
	};

} // namespace sunkell
