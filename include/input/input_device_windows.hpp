// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_device.hpp"

#include <Windows.h>
#include <minwindef.h>
#include <stdexcept>
#include <winrt/Windows.UI.Core.h>

namespace sunkell {

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const char* message)
		  : std::runtime_error(message) {}
	};

	class input_device_windows : public input_device {
		winrt::Windows::UI::Core::CoreWindow m_target_window;

		void key_down_callback(const winrt::Windows::UI::Core::CoreWindow& window,
		                       const winrt::Windows::UI::Core::KeyEventArgs& args);

		void key_up_callback(const winrt::Windows::UI::Core::CoreWindow&   window,
		                       const winrt::Windows::UI::Core::KeyEventArgs& args);

		public:
		explicit input_device_windows();
		virtual ~input_device_windows();

		virtual void update() override;

		virtual bool pressed(button button) override;
		virtual bool released(button button) override;

		virtual bool is_down(button button) override;
		virtual bool is_up(button button) override;
	};

} // namespace sunkell
