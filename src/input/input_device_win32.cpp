// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input/input_device_win32.hpp"

#include "input/input_enums.hpp"

#include <errhandlingapi.h>
#include <format>
#include <hidusage.h>
#include <stdexcept>

namespace sunkell {

	input_device::input_device() {
		// TODO: Handle other devices, multiple devices, etc.
		RAWINPUTDEVICE devices[2];

		devices[0].usUsagePage = HID_USAGE_PAGE_GAME;
		devices[0].usUsage     = HID_USAGE_GENERIC_KEYBOARD;
		devices[0].dwFlags     = RIDEV_NOLEGACY;
		devices[0].hwndTarget  = nullptr;

		devices[1].usUsagePage = HID_USAGE_PAGE_GAME;
		devices[1].usUsage     = HID_USAGE_GENERIC_MOUSE;
		devices[1].dwFlags     = RIDEV_NOLEGACY;
		devices[1].hwndTarget  = nullptr;

		if(!RegisterRawInputDevices(devices, 2, sizeof(RAWINPUTDEVICE))) {
			throw device_registration_error(
			  std::format("registering input devices failed with system error {}",
			              GetLastError()));
		}
	}

	constexpr input_device::key_state
	input_device::translate_keyboard_input(const RAWINPUT& input) const {
		button_state state    = (input.data.keyboard.Flags & RI_KEY_BREAK) ?
		                          button_state::released :
		                          button_state::pressed;
		bool         E0       = input.data.keyboard.Flags & RI_KEY_E0;
		bool         E1       = input.data.keyboard.Flags & RI_KEY_E1;
		USHORT       scancode = input.data.keyboard.MakeCode;
		switch(scancode) {
			case 0x1E:
				return {button::a, state};
			case 0x30:
				return {button::b, state};
			case 0x2E:
				return {button::c, state};
			case 0x20:
				return {button::d, state};
			case 0x12:
				return {button::e, state};
			case 0x21:
				return {button::f, state};
			case 0x22:
				return {button::g, state};
			case 0x23:
				return {button::h, state};
			case 0x17:
				return {button::i, state};
			case 0x24:
				return {button::j, state};
			case 0x25:
				return {button::k, state};
			case 0x26:
				return {button::l, state};
			case 0x32:
				return {button::m, state};
			case 0x31:
				return {button::n, state};
			case 0x18:
				return {button::o, state};
			case 0x19:
				return {button::p, state};
			case 0x10:
				return {button::q, state};
			case 0x13:
				return {button::r, state};
			case 0x1F:
				return {button::s, state};
			case 0x14:
				return {button::t, state};
			case 0x16:
				return {button::u, state};
			case 0x2F:
				return {button::v, state};
			case 0x11:
				return {button::w, state};
			case 0x2D:
				return {button::x, state};
			case 0x15:
				return {button::y, state};
			case 0x2C:
				return {button::z, state};
			case 0x02:
				return {button::one, state};
			case 0x03:
				return {button::two, state};
			case 0x04:
				return {button::three, state};
			case 0x05:
				return {button::four, state};
			case 0x06:
				return {button::five, state};
			case 0x07:
				return {button::six, state};
			case 0x08:
				return {button::seven, state};
			case 0x09:
				return {button::eight, state};
			case 0x0A:
				return {button::nine, state};
			case 0x0B:
				return {button::zero, state};
			case 0x1C:
				if(E0) { return {button::numpad_enter, state}; }
				return {button::enter, state};
			case 0x01:
				return {button::escape, state};
			case 0x0E:
				return {button::backspace, state};
			case 0x0F:
				return {button::tab, state};
			case 0x39:
				return {button::space, state};
			case 0x0C:
				return {button::hyphen, state};
			case 0x0D:
				return {button::equals, state};
			case 0x1A:
				return {button::left_brace, state};
			case 0x1B:
				return {button::right_brace, state};
			case 0x2B:
				return {button::backslash, state};
			case 0x27:
				return {button::semicolon, state};
			case 0x28:
				return {button::apostrophe, state};
			case 0x29:
				return {button::backtick, state};
			case 0x33:
				return {button::comma, state};
			case 0x34:
				return {button::period, state};
			case 0x35:
				if(E0) { return {button::numpad_divide, state}; }
				return {button::slash, state};
			case 0x3A:
				return {button::caps_lock, state};
			case 0x3B:
				return {button::f1, state};
			case 0x3C:
				return {button::f2, state};
			case 0x3D:
				return {button::f3, state};
			case 0x3E:
				return {button::f4, state};
			case 0x3F:
				return {button::f5, state};
			case 0x40:
				return {button::f6, state};
			case 0x41:
				return {button::f7, state};
			case 0x42:
				return {button::f8, state};
			case 0x43:
				return {button::f9, state};
			case 0x44:
				return {button::f10, state};
			case 0x57:
				return {button::f11, state};
			case 0x58:
				return {button::f12, state};
			case 0x37:
				if(E0) { return {button::print_screen, state}; }
				return {button::numpad_multiply, state};
			case 0x54:
				return {button::print_screen, state};
			case 0x46:
				return {button::scroll_lock, state};
			case 0x45:
				if(E1) { return {button::pause, state}; }
				return {button::num_lock, state};
			case 0x52:
				if(E0) { return {button::insert, state}; }
				return {button::numpad_zero, state};
			case 0x47:
				if(E0) { return {button::home, state}; }
				return {button::numpad_seven, state};
			case 0x49:
				if(E0) { return {button::page_up, state}; }
				return {button::numpad_nine, state};
			case 0x53:
				if(E0) { return {button::del, state}; }
				return {button::numpad_decimal, state};
			case 0x4F:
				if(E0) { return {button::end, state}; }
				return {button::numpad_one, state};
			case 0x51:
				if(E0) { return {button::page_down, state}; }
				return {button::numpad_three, state};
			case 0x4D:
				if(E0) { return {button::arrow_right, state}; }
				return {button::numpad_six, state};
			case 0x4B:
				if(E0) { return {button::arrow_left, state}; }
				return {button::numpad_four, state};
			case 0x50:
				if(E0) { return {button::arrow_down, state}; }
				return {button::numpad_two, state};
			case 0x48:
				if(E0) { return {button::arrow_up, state}; }
				return {button::numpad_eight, state};
			case 0x4A:
				return {button::numpad_minus, state};
			case 0x4E:
				return {button::numpad_plus, state};
			case 0x4C:
				return {button::numpad_five, state};
			case 0x5D:
				return {button::menu, state};
			case 0x1D:
				if(E0) { return {button::right_control, state}; }
				return {button::left_control, state};
			case 0x2A:
				return {button::left_shift, state};
			case 0x38:
				if(E0) { return {button::right_alt, state}; }
				return {button::left_alt, state};
			case 0x5B:
				return {button::left_super, state};
			case 0x36:
				return {button::right_shift, state};
			case 0x5C:
				return {button::right_super, state};
			default:
				return {button::unknown, button_state::released};
		}
	}

	// TODO: Handle mouse wheel
	// TODO: Handle mouse movement
	// Reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
	constexpr input_device::key_state
	input_device::translate_mouse_input(const RAWINPUT& input) const {
		switch(input.data.mouse.usButtonFlags) {
			case RI_MOUSE_LEFT_BUTTON_DOWN:
				return {button::mouse_left, button_state::pressed};
			case RI_MOUSE_LEFT_BUTTON_UP:
				return {button::mouse_left, button_state::released};
			case RI_MOUSE_RIGHT_BUTTON_DOWN:
				return {button::mouse_right, button_state::pressed};
			case RI_MOUSE_RIGHT_BUTTON_UP:
				return {button::mouse_right, button_state::released};
			case RI_MOUSE_MIDDLE_BUTTON_DOWN:
				return {button::mouse_middle, button_state::pressed};
			case RI_MOUSE_MIDDLE_BUTTON_UP:
				return {button::mouse_middle, button_state::released};
			case RI_MOUSE_BUTTON_4_DOWN:
				return {button::mouse_x1, button_state::pressed};
			case RI_MOUSE_BUTTON_4_UP:
				return {button::mouse_x1, button_state::released};
			case RI_MOUSE_BUTTON_5_DOWN:
				return {button::mouse_x2, button_state::pressed};
			case RI_MOUSE_BUTTON_5_UP:
				return {button::mouse_x2, button_state::released};
			default:
				return {button::unknown, button_state::unknown};
		}
	}

	constexpr input_device::key_state
	input_device::translate_input(const RAWINPUT& input) const {
		switch(input.header.dwType) {
			case RIM_TYPEKEYBOARD:
				return translate_keyboard_input(input);
			case RIM_TYPEMOUSE:
				return translate_mouse_input(input);
		}
	}

	void input_device::poll() {
		UINT buffer_size = 0;
		GetRawInputBuffer(NULL, &buffer_size, sizeof(RAWINPUTHEADER));
		RAWINPUT buffer[buffer_size];
		if(!GetRawInputBuffer(buffer, &buffer_size, sizeof(RAWINPUTHEADER))) {
			throw input_poll_failure(std::format(
			  "polling for inputs failed with system error {}", GetLastError()));
		}
		for(size_t i = 0; i < buffer_size; ++i) {
			const RAWINPUT& input = buffer[i];
			static_assert(false, "polling implementation unfinished");
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
