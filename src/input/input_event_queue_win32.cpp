// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifdef SUNKELL_PLATFORM_WIN32

#include "input/input_enums.hpp"
#include "input/input_event_queue.hpp"
#include "input/input_events.hpp"

#include <errhandlingapi.h>
#include <format>
#include <hidusage.h>
#include <windows.h>

namespace sunkell {

	struct input_event_queue::platform_specific {
		// The position from the previous mouse event needs to be stored so that
		// the delta can be calculated.
		// There will only be one cursor per system, so it is safe to make this
		// static, which enables the translation functions to be constexpr.
		static vec2<int> s_last_mouse_position;

		// By default, Windows does not send events for raw input devices. We
		// need to register the devices we want to receive events for.
		void register_raw_input_devices();

		constexpr key_event   translate_keyboard_input(const RAWINPUT& input) const;
		constexpr mouse_event translate_mouse_input(const RAWINPUT& input) const;
		constexpr event       translate_input(const RAWINPUT& input) const;

		platform_specific();
	};

	input_event_queue::platform_specific::platform_specific() {
		s_last_mouse_position = {0, 0};
	}

	void input_event_queue::platform_specific::register_raw_input_devices() {
		// TODO: Handle other devices, multiple devices, etc.
		RAWINPUTDEVICE devices[2];

		// Keyboard description
		devices[0].usUsagePage = HID_USAGE_PAGE_GAME;
		devices[0].usUsage     = HID_USAGE_GENERIC_KEYBOARD;
		devices[0].dwFlags     = RIDEV_NOLEGACY;
		devices[0].hwndTarget  = nullptr;

		// Mouse description
		devices[1].usUsagePage = HID_USAGE_PAGE_GAME;
		devices[1].usUsage     = HID_USAGE_GENERIC_MOUSE;
		devices[1].dwFlags     = RIDEV_NOLEGACY;
		devices[1].hwndTarget  = nullptr;

		// Register devices
		if(!RegisterRawInputDevices(devices, 2, sizeof(RAWINPUTDEVICE))) {
			throw device_registration_error(
			  std::format("registering input devices failed with system error {}",
			              GetLastError()));
		}
	}

	constexpr key_event
	input_event_queue::platform_specific::translate_keyboard_input(
	  const RAWINPUT& input) const {
		button_state state    = (input.data.keyboard.Flags & RI_KEY_BREAK) ?
		                          button_state::up :
		                          button_state::down;
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
				return {button::unknown, button_state::up};
		}
	}

	// Reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
	constexpr mouse_event
	input_event_queue::platform_specific::translate_mouse_input(
	  const RAWINPUT& input) const {
		vec2<int> position;
		vec2<int> delta;
		if(input.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) {
			position.x = input.data.mouse.lLastX;
			position.y = input.data.mouse.lLastY;
			delta.x    = position.x - m_platform->s_last_mouse_position.x;
			delta.y    = position.y - m_platform->s_last_mouse_position.y;
		} else {
			delta.x    = input.data.mouse.lLastX;
			delta.y    = input.data.mouse.lLastY;
			position.x = m_platform->s_last_mouse_position.x + delta.x;
			position.y = m_platform->s_last_mouse_position.y + delta.y;
		}
		m_platform->s_last_mouse_position = position;

		// TODO: Add support for horizontal scrolling
		bool isHorizontalScroll =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_HWHEEL) == RI_MOUSE_HWHEEL;
		int scroll_delta =
		  !isHorizontalScroll ?
		    static_cast<double>(input.data.mouse.usButtonData) / WHEEL_DELTA :
		    0;

		button_state left_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) ?
		    button_state::down :
		    button_state::up;

		button_state right_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) ?
		    button_state::down :
		    button_state::up;

		button_state middle_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) ?
		    button_state::down :
		    button_state::up;

		button_state x1_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) ?
		    button_state::down :
		    button_state::up;

		button_state x2_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) ?
		    button_state::down :
		    button_state::up;

		return {position,
		        delta,
		        scroll_delta,
		        left_button_state,
		        right_button_state,
		        middle_button_state,
		        x1_button_state,
		        x2_button_state};
	}

	constexpr event input_event_queue::platform_specific::translate_input(
	  const RAWINPUT& input) const {
		switch(input.header.dwType) {
			case RIM_TYPEKEYBOARD:
				return input_event_queue::translate_keyboard_input(input);
			case RIM_TYPEMOUSE:
				return input_event_queue::translate_mouse_input(input);
			case RIM_TYPEHID:
				// NOTE: Add support for other human input devices here
			default:
				// TODO: Log that an unknown input type was received
				return {};
		}
	}

	input_event_queue::input_event_queue() {
		m_platform->register_raw_input_devices();
	}

	void input_event_queue::poll() {
		UINT buffer_size = 0;
		GetRawInputBuffer(NULL, &buffer_size, sizeof(RAWINPUTHEADER));
		RAWINPUT buffer[buffer_size];
		if(!GetRawInputBuffer(buffer, &buffer_size, sizeof(RAWINPUTHEADER))) {
			throw input_poll_failure(std::format(
			  "polling for inputs failed with system error {}", GetLastError()));
		}
		for(size_t i = 0; i < buffer_size; ++i) {
			const RAWINPUT& input            = buffer[i];
			const event     translated_event = translate_input(input);
			m_event_queue.push(translated_event);
		}
	}

	void input_event_queue::dispatch_next_event() {
		auto event     = m_event_queue.front();
		auto callbacks = m_callbacks.equal_range(m_event_queue.front());
		for(auto it = callbacks.first; it != callbacks.second; ++it) {
			it->second(event);
		}
		m_event_queue.pop();
	}

	event input_event_queue::peek_next_event() { return m_event_queue.front(); }

	void input_event_queue::skip_next_event() { m_event_queue.pop(); }

	input_event_queue::callback_map::iterator
	input_event_queue::register_callback(
	  event event, const std::function<void(sunkell::event)> callback) {
		return m_callbacks.emplace(event, callback);
	}

	void input_event_queue::unregister_callback(
	  input_event_queue::callback_map::iterator iterator) {
		m_callbacks.erase(iterator);
	}

} // namespace sunkell

#endif // SUNKELL_PLATFORM_WIN32
