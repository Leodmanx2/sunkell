// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "common/windowing/window.hpp"
#ifdef SUNKELL_PLATFORM_WIN32

#include "input/input_enums.hpp"
#include "input/input_event_queue.hpp"
#include "input/input_events.hpp"

#include <errhandlingapi.h>
#include <format>
#include <hidusage.h>
#include <memory>
#include <windows.h>

namespace sunkell {

	// --------------------------------------------------------------------------
	// Forward declarations
	// --------------------------------------------------------------------------

	std::shared_ptr<key_event>   translate_keyboard_input(const RAWINPUT& input);
	std::shared_ptr<mouse_event> translate_mouse_input(const RAWINPUT& input);
	std::shared_ptr<event>       translate_input(const RAWINPUT& input);

	// By default, Windows does not automatically send events for raw input
	// devices. We need to explicitly register the specific devices we want to
	// receive events for. The operating system will only send these raw input
	// events to a thread that has a window in keyboard focus. If nullptr is
	// passed as the target window, the events will be received from all windows
	// on the queue's thread, whenever the application is in focus. However, if a
	// specific target window is set, the events will only be received when that
	// particular window is in focus.
	constexpr void register_raw_input_devices(HWND target_window);

	namespace {
		// The position from the previous mouse event needs to be stored so that
		// the delta can be calculated.
		// There will only be one cursor per system, so it is safe to make this
		// static, which enables the translation functions to be constexpr.
		vec2<int> s_last_mouse_position = {0, 0};
	} // namespace

	// --------------------------------------------------------------------------

	constexpr void register_raw_input_devices(HWND target_window) {
		// TODO: Handle other devices, multiple devices, etc.
		std::array<RAWINPUTDEVICE, 2> devices{};

		// Keyboard description
		devices[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
		devices[0].usUsage     = HID_USAGE_GENERIC_KEYBOARD;
		devices[0].dwFlags     = RIDEV_NOLEGACY;
		devices[0].hwndTarget  = target_window;

		// Mouse description
		devices[1].usUsagePage = HID_USAGE_PAGE_GENERIC;
		devices[1].usUsage     = HID_USAGE_GENERIC_MOUSE;
		devices[1].dwFlags     = RIDEV_NOLEGACY;
		devices[1].hwndTarget  = target_window;

		// Register devices
		if(RegisterRawInputDevices(static_cast<PRAWINPUTDEVICE>(devices.data()),
		                           2,
		                           sizeof(RAWINPUTDEVICE)) == 0) {
			throw device_registration_error(
			  std::format("registering input devices failed with system error {}",
			              GetLastError()));
		}
	}

	std::shared_ptr<key_event> translate_keyboard_input(const RAWINPUT& input) {
		button_state state    = (input.data.keyboard.Flags & RI_KEY_BREAK) != 0 ?
		                          button_state::up :
		                          button_state::down;
		bool         E0       = (input.data.keyboard.Flags & RI_KEY_E0) != 0;
		bool         E1       = (input.data.keyboard.Flags & RI_KEY_E1) != 0;
		USHORT       scancode = input.data.keyboard.MakeCode;
		switch(scancode) {
			case 0x1E:
				return std::make_shared<key_event>(button::a, state);
			case 0x30:
				return std::make_shared<key_event>(button::b, state);
			case 0x2E:
				return std::make_shared<key_event>(button::c, state);
			case 0x20:
				return std::make_shared<key_event>(button::d, state);
			case 0x12:
				return std::make_shared<key_event>(button::e, state);
			case 0x21:
				return std::make_shared<key_event>(button::f, state);
			case 0x22:
				return std::make_shared<key_event>(button::g, state);
			case 0x23:
				return std::make_shared<key_event>(button::h, state);
			case 0x17:
				return std::make_shared<key_event>(button::i, state);
			case 0x24:
				return std::make_shared<key_event>(button::j, state);
			case 0x25:
				return std::make_shared<key_event>(button::k, state);
			case 0x26:
				return std::make_shared<key_event>(button::l, state);
			case 0x32:
				return std::make_shared<key_event>(button::m, state);
			case 0x31:
				return std::make_shared<key_event>(button::n, state);
			case 0x18:
				return std::make_shared<key_event>(button::o, state);
			case 0x19:
				return std::make_shared<key_event>(button::p, state);
			case 0x10:
				return std::make_shared<key_event>(button::q, state);
			case 0x13:
				return std::make_shared<key_event>(button::r, state);
			case 0x1F:
				return std::make_shared<key_event>(button::s, state);
			case 0x14:
				return std::make_shared<key_event>(button::t, state);
			case 0x16:
				return std::make_shared<key_event>(button::u, state);
			case 0x2F:
				return std::make_shared<key_event>(button::v, state);
			case 0x11:
				return std::make_shared<key_event>(button::w, state);
			case 0x2D:
				return std::make_shared<key_event>(button::x, state);
			case 0x15:
				return std::make_shared<key_event>(button::y, state);
			case 0x2C:
				return std::make_shared<key_event>(button::z, state);
			case 0x02:
				return std::make_shared<key_event>(button::one, state);
			case 0x03:
				return std::make_shared<key_event>(button::two, state);
			case 0x04:
				return std::make_shared<key_event>(button::three, state);
			case 0x05:
				return std::make_shared<key_event>(button::four, state);
			case 0x06:
				return std::make_shared<key_event>(button::five, state);
			case 0x07:
				return std::make_shared<key_event>(button::six, state);
			case 0x08:
				return std::make_shared<key_event>(button::seven, state);
			case 0x09:
				return std::make_shared<key_event>(button::eight, state);
			case 0x0A:
				return std::make_shared<key_event>(button::nine, state);
			case 0x0B:
				return std::make_shared<key_event>(button::zero, state);
			case 0x1C:
				if(E0) {
					return std::make_shared<key_event>(button::numpad_enter, state);
				}
				return std::make_shared<key_event>(button::enter, state);
			case 0x01:
				return std::make_shared<key_event>(button::escape, state);
			case 0x0E:
				return std::make_shared<key_event>(button::backspace, state);
			case 0x0F:
				return std::make_shared<key_event>(button::tab, state);
			case 0x39:
				return std::make_shared<key_event>(button::space, state);
			case 0x0C:
				return std::make_shared<key_event>(button::hyphen, state);
			case 0x0D:
				return std::make_shared<key_event>(button::equals, state);
			case 0x1A:
				return std::make_shared<key_event>(button::left_brace, state);
			case 0x1B:
				return std::make_shared<key_event>(button::right_brace, state);
			case 0x2B:
				return std::make_shared<key_event>(button::backslash, state);
			case 0x27:
				return std::make_shared<key_event>(button::semicolon, state);
			case 0x28:
				return std::make_shared<key_event>(button::apostrophe, state);
			case 0x29:
				return std::make_shared<key_event>(button::backtick, state);
			case 0x33:
				return std::make_shared<key_event>(button::comma, state);
			case 0x34:
				return std::make_shared<key_event>(button::period, state);
			case 0x35:
				if(E0) {
					return std::make_shared<key_event>(button::numpad_divide, state);
				}
				return std::make_shared<key_event>(button::slash, state);
			case 0x3A:
				return std::make_shared<key_event>(button::caps_lock, state);
			case 0x3B:
				return std::make_shared<key_event>(button::f1, state);
			case 0x3C:
				return std::make_shared<key_event>(button::f2, state);
			case 0x3D:
				return std::make_shared<key_event>(button::f3, state);
			case 0x3E:
				return std::make_shared<key_event>(button::f4, state);
			case 0x3F:
				return std::make_shared<key_event>(button::f5, state);
			case 0x40:
				return std::make_shared<key_event>(button::f6, state);
			case 0x41:
				return std::make_shared<key_event>(button::f7, state);
			case 0x42:
				return std::make_shared<key_event>(button::f8, state);
			case 0x43:
				return std::make_shared<key_event>(button::f9, state);
			case 0x44:
				return std::make_shared<key_event>(button::f10, state);
			case 0x57:
				return std::make_shared<key_event>(button::f11, state);
			case 0x58:
				return std::make_shared<key_event>(button::f12, state);
			case 0x37:
				if(E0) {
					return std::make_shared<key_event>(button::print_screen, state);
				}
				return std::make_shared<key_event>(button::numpad_multiply, state);
			case 0x54:
				return std::make_shared<key_event>(button::print_screen, state);
			case 0x46:
				return std::make_shared<key_event>(button::scroll_lock, state);
			case 0x45:
				if(E1) { return std::make_shared<key_event>(button::pause, state); }
				return std::make_shared<key_event>(button::num_lock, state);
			case 0x52:
				if(E0) { return std::make_shared<key_event>(button::insert, state); }
				return std::make_shared<key_event>(button::numpad_zero, state);
			case 0x47:
				if(E0) { return std::make_shared<key_event>(button::home, state); }
				return std::make_shared<key_event>(button::numpad_seven, state);
			case 0x49:
				if(E0) { return std::make_shared<key_event>(button::page_up, state); }
				return std::make_shared<key_event>(button::numpad_nine, state);
			case 0x53:
				if(E0) { return std::make_shared<key_event>(button::del, state); }
				return std::make_shared<key_event>(button::numpad_decimal, state);
			case 0x4F:
				if(E0) { return std::make_shared<key_event>(button::end, state); }
				return std::make_shared<key_event>(button::numpad_one, state);
			case 0x51:
				if(E0) { return std::make_shared<key_event>(button::page_down, state); }
				return std::make_shared<key_event>(button::numpad_three, state);
			case 0x4D:
				if(E0) {
					return std::make_shared<key_event>(button::arrow_right, state);
				}
				return std::make_shared<key_event>(button::numpad_six, state);
			case 0x4B:
				if(E0) {
					return std::make_shared<key_event>(button::arrow_left, state);
				}
				return std::make_shared<key_event>(button::numpad_four, state);
			case 0x50:
				if(E0) {
					return std::make_shared<key_event>(button::arrow_down, state);
				}
				return std::make_shared<key_event>(button::numpad_two, state);
			case 0x48:
				if(E0) { return std::make_shared<key_event>(button::arrow_up, state); }
				return std::make_shared<key_event>(button::numpad_eight, state);
			case 0x4A:
				return std::make_shared<key_event>(button::numpad_minus, state);
			case 0x4E:
				return std::make_shared<key_event>(button::numpad_plus, state);
			case 0x4C:
				return std::make_shared<key_event>(button::numpad_five, state);
			case 0x5D:
				return std::make_shared<key_event>(button::menu, state);
			case 0x1D:
				if(E0) {
					return std::make_shared<key_event>(button::right_control, state);
				}
				return std::make_shared<key_event>(button::left_control, state);
			case 0x2A:
				return std::make_shared<key_event>(button::left_shift, state);
			case 0x38:
				if(E0) { return std::make_shared<key_event>(button::right_alt, state); }
				return std::make_shared<key_event>(button::left_alt, state);
			case 0x5B:
				return std::make_shared<key_event>(button::left_super, state);
			case 0x36:
				return std::make_shared<key_event>(button::right_shift, state);
			case 0x5C:
				return std::make_shared<key_event>(button::right_super, state);
			default:
				return std::make_shared<key_event>(button::unknown, button_state::up);
		}
	}

	// Reference: https://learn.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-rawmouse
	std::shared_ptr<mouse_event> translate_mouse_input(const RAWINPUT& input) {
		vec2<int> position;
		vec2<int> delta;
		if((input.data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) != 0) {
			position.x = input.data.mouse.lLastX;
			position.y = input.data.mouse.lLastY;
			delta.x    = position.x - s_last_mouse_position.x;
			delta.y    = position.y - s_last_mouse_position.y;
		} else {
			delta.x    = input.data.mouse.lLastX;
			delta.y    = input.data.mouse.lLastY;
			position.x = s_last_mouse_position.x + delta.x;
			position.y = s_last_mouse_position.y + delta.y;
		}
		s_last_mouse_position = position;

		// TODO: Add support for horizontal scrolling
		bool isHorizontalScroll =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_HWHEEL) == RI_MOUSE_HWHEEL;
		double scroll_delta =
		  !isHorizontalScroll ?
		    static_cast<double>(input.data.mouse.usButtonData) / WHEEL_DELTA :
		    0;

		button_state left_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) != 0 ?
		    button_state::down :
		    button_state::up;

		button_state right_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) != 0 ?
		    button_state::down :
		    button_state::up;

		button_state middle_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) != 0 ?
		    button_state::down :
		    button_state::up;

		button_state x1_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_4_DOWN) != 0 ?
		    button_state::down :
		    button_state::up;

		button_state x2_button_state =
		  (input.data.mouse.usButtonFlags & RI_MOUSE_BUTTON_5_DOWN) != 0 ?
		    button_state::down :
		    button_state::up;

		return std::make_shared<mouse_event>(position,
		                                     delta,
		                                     scroll_delta,
		                                     left_button_state,
		                                     right_button_state,
		                                     middle_button_state,
		                                     x1_button_state,
		                                     x2_button_state);
	}

	std::shared_ptr<event> translate_input(const RAWINPUT& input) {
		switch(input.header.dwType) {
			case RIM_TYPEKEYBOARD:
				return translate_keyboard_input(input);
			case RIM_TYPEMOUSE:
				return translate_mouse_input(input);
			case RIM_TYPEHID:
				// NOTE: Add support for other human input devices here
			default:
				// TODO: Log that an unknown input type was received
				return {};
		}
	}

	input_event_queue::input_event_queue() {
		register_raw_input_devices(nullptr);
	}

	input_event_queue::input_event_queue(const window* window) {
		window->with_platform_details([this](void* platform_window) {
			HWND hWnd = static_cast<HWND>(platform_window);
			register_raw_input_devices(hWnd);
		});
	}

	void input_event_queue::poll() {
		UINT buffer_size = 0;
		GetRawInputBuffer(nullptr, &buffer_size, sizeof(RAWINPUTHEADER));
		// Align buffer on pointer boundary
		buffer_size += sizeof(RAWINPUT) - buffer_size % sizeof(RAWINPUT);
		std::vector<RAWINPUT> buffer(buffer_size);
		if(GetRawInputBuffer(buffer.data(), &buffer_size, sizeof(RAWINPUTHEADER)) ==
		   -1U) {
			throw input_poll_failure(
			  std::format("polling for inputs failed with system error {}",
			              GetLastError(),
			              buffer_size));
		}
		for(size_t i = 0; i < buffer_size; ++i) {
			const RAWINPUT& input            = buffer[i];
			auto            translated_event = translate_input(input);
			m_event_queue.push(translated_event);
		}
	}

	void input_event_queue::dispatch_next_event() {
		if(empty()) {
			throw empty_queue_error("dispatch_next_event called on empty queue");
		}
		auto event = m_event_queue.front();
		auto range = m_callbacks.equal_range(m_event_queue.front());
		for(auto it = range.first; it != range.second; ++it) {
			auto callback = it->second;
			callback(event);
		}
		m_event_queue.pop();
	}

	std::shared_ptr<event> input_event_queue::peek_next_event() {
		if(empty()) {
			throw empty_queue_error("peek_next_event called on empty queue");
		}
		return m_event_queue.front();
	}

	void input_event_queue::skip_next_event() {
		if(empty()) {
			throw empty_queue_error("skip_next_event called on empty queue");
		}
		m_event_queue.pop();
	}

	input_event_queue::callback_receipt input_event_queue::register_callback(
	  std::shared_ptr<event>                             trigger_event,
	  const std::function<void(std::shared_ptr<event>)>& callback) {
		auto iterator = m_callbacks.emplace(trigger_event, callback);
		return input_event_queue::callback_receipt(iterator);
	}

	void input_event_queue::unregister_callback(
	  input_event_queue::callback_receipt& receipt) {
		if(receipt.m_iterator == m_callbacks.end()) { return; }
		m_callbacks.erase(receipt.m_iterator);
		receipt.m_iterator = m_callbacks.end();
	}

} // namespace sunkell

#endif // SUNKELL_PLATFORM_WIN32
