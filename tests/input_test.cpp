// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "input.hpp"

#include <doctest/doctest.h>

#ifdef SUNKELL_PLATFORM_WIN32
#include <windows.h>

// TODO: This is a VERY rough test written to check that the input queue
//       works. Once the window class is implemented, this test should be
//       rewritten to use it.
TEST_CASE("input queue receives events") {
	WNDCLASSEX wx    = {};
	wx.cbSize        = sizeof(WNDCLASSEX);
	wx.lpfnWndProc   = DefWindowProc;
	wx.hInstance     = GetModuleHandle(NULL);
	wx.lpszClassName = TEXT("MyRawInputWndClass");

	REQUIRE(RegisterClassEx(&wx) != 0);

	// Create a window in the same thread as the queue
	const DWORD  extended_window_style = WS_EX_OVERLAPPEDWINDOW;
	const LPCSTR class_name            = wx.lpszClassName;
	const LPCSTR window_name           = "Raw Input Test";
	const DWORD  window_style          = WS_OVERLAPPEDWINDOW;
	const int    x                     = CW_USEDEFAULT;
	const int    y                     = CW_USEDEFAULT;
	const int    width                 = CW_USEDEFAULT;
	const int    height                = CW_USEDEFAULT;
	const HWND parent_window = HWND_DESKTOP; // Doing this creates a message-only
	                                         // window, which is not visible
	const HMENU     menu     = NULL;
	const HINSTANCE instance = wx.hInstance;
	const LPVOID    param    = NULL;

	HWND hWnd = CreateWindowEx(extended_window_style,
	                           class_name,
	                           window_name,
	                           window_style,
	                           x,
	                           y,
	                           width,
	                           height,
	                           parent_window,
	                           menu,
	                           instance,
	                           param);

	REQUIRE(hWnd != NULL);

	// Show the window
	ShowWindow(hWnd, SW_SHOW);

	// Ensure the window is in keyboard focus
	SetFocus(hWnd);

	// Initialize the queue
	sunkell::input_event_queue queue;

	// Send a simulated 'a' button press to the window
	INPUT input          = {};
	input.type           = INPUT_KEYBOARD;
	input.ki.wVk         = 0x41;
	input.ki.dwFlags     = 0;
	input.ki.time        = 0;
	input.ki.dwExtraInfo = 0;
	input.ki.wScan       = MapVirtualKey(0x41, MAPVK_VK_TO_VSC);
	SendInput(1, &input, sizeof(INPUT));

	queue.poll();

	// Ensure the queue has received the event
	// There may be other events in the queue, so we need to look for the one we sent
	bool found = false;
	while(!queue.empty()) {
		auto event     = queue.peek_next_event();
		auto key_event = std::dynamic_pointer_cast<sunkell::key_event>(event);
		if(key_event && key_event->button() == sunkell::button::a) {
			found = true;
			break;
		}
		queue.skip_next_event();
	}
	REQUIRE(found);
}

#endif // SUNKELL_PLATFORM_WIN32

using namespace sunkell;
