// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_device.hpp"
#include "input_enums.hpp"

#include <functional>
#include <stdexcept>
#include <unordered_map>
#include <winrt/Windows.UI.Core.h>

namespace sunkell {

	class input_device : public input_device_interface<input_device> {
		using key_state         = std::pair<button, button_state>;
		using callback          = std::function<void()>;
		using callback_map      = std::unordered_multimap<key_state, callback>;
		using callback_iterator = callback_map::iterator;

		callback_map m_callbacks;

		winrt::Windows::UI::Core::CoreWindow m_target_window;

		constexpr button
		translate_key_code(const winrt::Windows::System::VirtualKey& key) {
			using namespace winrt::Windows::System;
			switch(key) {
				case VirtualKey::A:
					return button::a;
				case VirtualKey::Accept:
					return button::unknown;
				case VirtualKey::Add:
					return button::numpad_plus;
				case VirtualKey::Application:
					return button::unknown;
				case VirtualKey::B:
					return button::b;
				case VirtualKey::Back:
					return button::backspace;
				case VirtualKey::C:
					return button::c;
				case VirtualKey::Cancel:
					return button::unknown;
				case VirtualKey::CapitalLock:
					return button::caps_lock;
				case VirtualKey::Clear:
					return button::unknown;
				case VirtualKey::Control:
					return button::left_control;
				case VirtualKey::Convert:
					return button::unknown;
				case VirtualKey::D:
					return button::d;
				case VirtualKey::Decimal:
					return button::numpad_decimal;
				case VirtualKey::Delete:
					return button::del;
				case VirtualKey::Divide:
					return button::numpad_divide;
				case VirtualKey::Down:
					return button::arrow_down;
				case VirtualKey::E:
					return button::e;
				case VirtualKey::End:
					return button::end;
				case VirtualKey::Enter:
					return button::enter;
				case VirtualKey::Escape:
					return button::escape;
				case VirtualKey::Execute:
					return button::unknown;
				case VirtualKey::F:
					return button::f;
				case VirtualKey::F1:
					return button::f1;
				case VirtualKey::F10:
					return button::f10;
				case VirtualKey::F11:
					return button::f11;
				case VirtualKey::F12:
					return button::f12;
				case VirtualKey::F13:
					return button::unknown;
				case VirtualKey::F14:
					return button::unknown;
				case VirtualKey::F15:
					return button::unknown;
				case VirtualKey::F16:
					return button::unknown;
				case VirtualKey::F17:
					return button::unknown;
				case VirtualKey::F18:
					return button::unknown;
				case VirtualKey::F19:
					return button::unknown;
				case VirtualKey::F2:
					return button::f2;
				case VirtualKey::F20:
					return button::unknown;
				case VirtualKey::F21:
					return button::unknown;
				case VirtualKey::F22:
					return button::unknown;
				case VirtualKey::F23:
					return button::unknown;
				case VirtualKey::F24:
					return button::unknown;
				case VirtualKey::F3:
					return button::f3;
				case VirtualKey::F4:
					return button::f4;
				case VirtualKey::F5:
					return button::f5;
				case VirtualKey::F6:
					return button::f6;
				case VirtualKey::F7:
					return button::f7;
				case VirtualKey::F8:
					return button::f8;
				case VirtualKey::F9:
					return button::f9;
				case VirtualKey::Favorites:
					return button::unknown;
				case VirtualKey::Final:
					return button::unknown;
				case VirtualKey::G:
					return button::g;
				case VirtualKey::GamepadA:
					return button::controller_a;
				case VirtualKey::GamepadB:
					return button::controller_b;
				case VirtualKey::GamepadDPadDown:
					return button::controller_dpad_down;
				case VirtualKey::GamepadDPadLeft:
					return button::controller_dpad_left;
				case VirtualKey::GamepadDPadRight:
					return button::controller_dpad_right;
				case VirtualKey::GamepadDPadUp:
					return button::controller_dpad_up;
				case VirtualKey::GamepadLeftShoulder:
					return button::controller_left_shoulder;
				case VirtualKey::GamepadLeftThumbstickButton:
					return button::controller_left_thumbstick;
				case VirtualKey::GamepadLeftThumbstickDown:
					return button::controller_left_thumbstick_down;
				case VirtualKey::GamepadLeftThumbstickLeft:
					return button::controller_left_thumbstick_left;
				case VirtualKey::GamepadLeftThumbstickRight:
					return button::controller_left_thumbstick_right;
				case VirtualKey::GamepadLeftThumbstickUp:
					return button::controller_left_thumbstick_up;
				case VirtualKey::GamepadLeftTrigger:
					return button::controller_left_trigger;
				case VirtualKey::GamepadMenu:
					return button::controller_start;
				case VirtualKey::GamepadRightShoulder:
					return button::controller_right_shoulder;
				case VirtualKey::GamepadRightThumbstickButton:
					return button::controller_right_thumbstick;
				case VirtualKey::GamepadRightThumbstickDown:
					return button::controller_right_thumbstick_down;
				case VirtualKey::GamepadRightThumbstickLeft:
					return button::controller_right_thumbstick_left;
				case VirtualKey::GamepadRightThumbstickRight:
					return button::controller_right_thumbstick_right;
				case VirtualKey::GamepadRightThumbstickUp:
					return button::controller_right_thumbstick_up;
				case VirtualKey::GamepadRightTrigger:
					return button::controller_right_trigger;
				case VirtualKey::GamepadView:
					return button::controller_back;
				case VirtualKey::GamepadX:
					return button::controller_x;
				case VirtualKey::GamepadY:
					return button::controller_y;
				case VirtualKey::GoBack:
					return button::unknown;
				case VirtualKey::GoForward:
					return button::unknown;
				case VirtualKey::GoHome:
					return button::unknown;
				case VirtualKey::H:
					return button::h;
				case VirtualKey::Hangul: // also Kana
					return button::unknown;
				case VirtualKey::Hanja: // also Kanji
					return button::unknown;
				case VirtualKey::Help:
					return button::unknown;
				case VirtualKey::Home:
					return button::home;
				case VirtualKey::I:
					return button::i;
				case VirtualKey::ImeOff:
					return button::unknown;
				case VirtualKey::ImeOn:
					return button::unknown;
				case VirtualKey::Insert:
					return button::insert;
				case VirtualKey::J:
					return button::j;
				case VirtualKey::Junja:
					return button::unknown;
				case VirtualKey::K:
					return button::k;
				case VirtualKey::L:
					return button::l;
				case VirtualKey::Left:
					return button::arrow_left;
				case VirtualKey::LeftButton:
					return button::mouse_left;
				case VirtualKey::LeftControl:
					return button::left_control;
				case VirtualKey::LeftMenu:
					return button::left_alt;
				case VirtualKey::LeftShift:
					return button::left_shift;
				case VirtualKey::LeftWindows:
					return button::left_super;
				case VirtualKey::M:
					return button::m;
				case VirtualKey::Menu:
					return button::left_alt;
				case VirtualKey::MiddleButton:
					return button::mouse_middle;
				case VirtualKey::ModeChange:
					return button::unknown;
				case VirtualKey::Multiply:
					return button::numpad_multiply;
				case VirtualKey::N:
					return button::n;
				case VirtualKey::NavigationAccept:
					return button::unknown;
				case VirtualKey::NavigationCancel:
					return button::unknown;
				case VirtualKey::NavigationDown:
					return button::unknown;
				case VirtualKey::NavigationLeft:
					return button::unknown;
				case VirtualKey::NavigationMenu:
					return button::unknown;
				case VirtualKey::NavigationRight:
					return button::unknown;
				case VirtualKey::NavigationUp:
					return button::unknown;
				case VirtualKey::NavigationView:
					return button::unknown;
				case VirtualKey::NonConvert:
					return button::unknown;
				case VirtualKey::None:
					return button::unknown;
				case VirtualKey::Number0:
					return button::zero;
				case VirtualKey::Number1:
					return button::one;
				case VirtualKey::Number2:
					return button::two;
				case VirtualKey::Number3:
					return button::three;
				case VirtualKey::Number4:
					return button::four;
				case VirtualKey::Number5:
					return button::five;
				case VirtualKey::Number6:
					return button::six;
				case VirtualKey::Number7:
					return button::seven;
				case VirtualKey::Number8:
					return button::eight;
				case VirtualKey::Number9:
					return button::nine;
				case VirtualKey::NumberKeyLock:
					return button::num_lock;
				case VirtualKey::NumberPad0:
					return button::numpad_zero;
				case VirtualKey::NumberPad1:
					return button::numpad_one;
				case VirtualKey::NumberPad2:
					return button::numpad_two;
				case VirtualKey::NumberPad3:
					return button::numpad_three;
				case VirtualKey::NumberPad4:
					return button::numpad_four;
				case VirtualKey::NumberPad5:
					return button::numpad_five;
				case VirtualKey::NumberPad6:
					return button::numpad_six;
				case VirtualKey::NumberPad7:
					return button::numpad_seven;
				case VirtualKey::NumberPad8:
					return button::numpad_eight;
				case VirtualKey::NumberPad9:
					return button::numpad_nine;
				case VirtualKey::O:
					return button::o;
				case VirtualKey::P:
					return button::p;
				case VirtualKey::PageDown:
					return button::page_down;
				case VirtualKey::PageUp:
					return button::page_up;
				case VirtualKey::Pause:
					return button::pause;
				case VirtualKey::Print:
					return button::unknown;
				case VirtualKey::Q:
					return button::q;
				case VirtualKey::R:
					return button::r;
				case VirtualKey::Refresh:
					return button::unknown;
				case VirtualKey::Right:
					return button::arrow_right;
				case VirtualKey::RightButton:
					return button::mouse_right;
				case VirtualKey::RightControl:
					return button::right_control;
				case VirtualKey::RightMenu:
					return button::right_alt;
				case VirtualKey::RightShift:
					return button::right_shift;
				case VirtualKey::RightWindows:
					return button::right_super;
				case VirtualKey::S:
					return button::s;
				case VirtualKey::Scroll:
					return button::scroll_lock;
				case VirtualKey::Search:
					return button::unknown;
				case VirtualKey::Select:
					return button::unknown;
				case VirtualKey::Separator:
					return button::unknown;
				case VirtualKey::Shift:
					return button::left_shift;
				case VirtualKey::Sleep:
					return button::unknown;
				case VirtualKey::Snapshot:
					return button::print_screen;
				case VirtualKey::Space:
					return button::space;
				case VirtualKey::Stop:
					return button::unknown;
				case VirtualKey::Subtract:
					return button::numpad_minus;
				case VirtualKey::T:
					return button::t;
				case VirtualKey::Tab:
					return button::tab;
				case VirtualKey::U:
					return button::u;
				case VirtualKey::Up:
					return button::arrow_up;
				case VirtualKey::V:
					return button::v;
				case VirtualKey::W:
					return button::w;
				case VirtualKey::X:
					return button::x;
				case VirtualKey::XButton1:
					return button::mouse_x1;
				case VirtualKey::XButton2:
					return button::mouse_x2;
				case VirtualKey::Y:
					return button::y;
				case VirtualKey::Z:
					return button::z;
				default:
					return button::unknown;
			}
		}

		public:
		input_device()
		  : m_target_window(
		      winrt::Windows::UI::Core::CoreWindow::GetForCurrentThread()) {
			if(!m_target_window) {
				throw device_registration_error("Failed to register input device.");
			}

			m_target_window.KeyDown([this](
			                          const winrt::Windows::UI::Core::CoreWindow&
			                            window,
			                          const winrt::Windows::UI::Core::KeyEventArgs&
			                            args) {
				// Translate the key code to our own enum
				button key = translate_key_code(args.VirtualKey());

				// Call every matching callback
				std::pair range = m_callbacks.equal_range({key, button_state::pressed});
				for(auto& callback = range.first; callback != range.second;
				    ++callback) {
					callback->second();
				}
			});

			m_target_window.KeyUp(
			  [this](const winrt::Windows::UI::Core::CoreWindow&   window,
			         const winrt::Windows::UI::Core::KeyEventArgs& args) {
				  // Translate the key code to our own enum
				  button key = translate_key_code(args.VirtualKey());

				  // Call every matching callback
				  std::pair range =
				    m_callbacks.equal_range({key, button_state::released});
				  for(auto& callback = range.first; callback != range.second;
				      ++callback) {
					  callback->second();
				  }
			  });
		}

		~input_device() {
			m_target_window.KeyDown(nullptr);
			m_target_window.KeyUp(nullptr);
		}

		inline callback_iterator register_callback(button          button,
		                                           button_state    state,
		                                           const callback& callback) {
			return m_callbacks.emplace(key_state{button, state}, callback);
		}

		inline void unregister_callback(callback_iterator iterator) {
			m_callbacks.erase(iterator);
		}

		// Pause processing of device inputs so the game's data isn't updated mid-render or subsystem update.
		inline void pause_processing() {
			m_target_window.Dispatcher().StopProcessEvents();
		}

		inline void resume_processing() {
			m_target_window.Dispatcher().ProcessEvents(
			  winrt::Windows::UI::Core::CoreProcessEventsOption::ProcessUntilQuit);
		}
	};

} // namespace sunkell
