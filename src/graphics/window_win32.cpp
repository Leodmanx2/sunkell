// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <format>
#include <windef.h>
#ifdef SUNKELL_PLATFORM_WIN32

#include "graphics/window.hpp"

#include <windows.h>

namespace sunkell {

	// --------------------------------------------------------------------------
	// Forward declarations
	// --------------------------------------------------------------------------

	class window::platform_specific_details final {
		friend class window;
		HWND  hWnd;
		HICON hIcon;

		platform_specific_details() : hWnd(nullptr), hIcon(nullptr) {}
	};

	// --------------------------------------------------------------------------

	window::~window()                            = default;
	window::window(window&&) noexcept            = default;
	window& window::operator=(window&&) noexcept = default;

	window::window() : m_platform(new platform_specific_details()) {
		WNDCLASSEX window_class = {};
		window_class.cbSize     = sizeof(WNDCLASSEX);
		window_class.lpfnWndProc =
		  DefWindowProc; // Use the default, OS-supplied window procedure to process messages
		window_class.hInstance     = GetModuleHandle(nullptr);
		window_class.lpszClassName = "sunkell_window";

		if(RegisterClassEx(&window_class) == 0) {
			throw window_creation_error(
			  std::format("registering window class failed with system error {}",
			              GetLastError()));
		}

		const DWORD     extended_window_style = WS_EX_OVERLAPPEDWINDOW;
		const LPCSTR    class_name            = window_class.lpszClassName;
		const LPCSTR    window_name           = nullptr;
		const DWORD     window_style          = WS_OVERLAPPEDWINDOW;
		const int       x                     = CW_USEDEFAULT;
		const int       y                     = CW_USEDEFAULT;
		const int       width                 = CW_USEDEFAULT;
		const int       height                = CW_USEDEFAULT;
		const HWND      parent_window         = HWND_DESKTOP;
		const HMENU     menu                  = nullptr;
		const HINSTANCE instance              = window_class.hInstance;
		const LPVOID    param                 = nullptr;

		m_platform->hWnd = CreateWindowEx(extended_window_style,
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
	}

	void window::show() { ShowWindow(m_platform->hWnd, SW_NORMAL); }

	void window::hide() { ShowWindow(m_platform->hWnd, SW_HIDE); }

	void window::minimize() { ShowWindow(m_platform->hWnd, SW_MINIMIZE); }

	void window::maximize() { ShowWindow(m_platform->hWnd, SW_MAXIMIZE); }

	void window::restore() { ShowWindow(m_platform->hWnd, SW_RESTORE); }

	void window::close() { DestroyWindow(m_platform->hWnd); }

	void window::focus() { SetFocus(m_platform->hWnd); }

	void window::resize(int width, int height) {
		RECT rect;
		GetWindowRect(m_platform->hWnd, &rect);
		MoveWindow(m_platform->hWnd, rect.left, rect.top, width, height, TRUE);
	}

	void window::width(int width) {
		RECT rect;
		GetWindowRect(m_platform->hWnd, &rect);
		MoveWindow(m_platform->hWnd,
		           rect.left,
		           rect.top,
		           width,
		           rect.bottom - rect.top,
		           TRUE);
	}

	void window::height(int height) {
		RECT rect;
		GetWindowRect(m_platform->hWnd, &rect);
		MoveWindow(m_platform->hWnd,
		           rect.left,
		           rect.top,
		           rect.right - rect.left,
		           height,
		           TRUE);
	}

	void window::title(std::string_view title) {
		std::string null_terminated_title(title);
		SetWindowText(m_platform->hWnd, null_terminated_title.c_str());
	}

	void window::mode(window_mode mode) {
		switch(mode) {
			case window_mode::windowed:
				SetWindowLongPtr(m_platform->hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				restore();
				return;
			case window_mode::fullscreen:
				SetWindowLongPtr(m_platform->hWnd, GWL_STYLE, WS_POPUP);
				maximize();
				return;
		}
	}

	int window::width() const {
		LPRECT lpRect = nullptr;
		GetWindowRect(m_platform->hWnd, lpRect);
		return lpRect->right - lpRect->left;
	}

	int window::height() const {
		LPRECT lpRect = nullptr;
		GetWindowRect(m_platform->hWnd, lpRect);
		return lpRect->bottom - lpRect->top;
	}

	const std::string& window::title() const {
		static std::string title;
		title.resize(GetWindowTextLength(m_platform->hWnd));
		GetWindowText(m_platform->hWnd, title.data(), title.size());
		return title;
	}

	window_mode window::mode() const {
		HMONITOR hMonitor =
		  MonitorFromWindow(m_platform->hWnd, MONITOR_DEFAULTTONEAREST);
		// Get monitor resolution
		MONITORINFOEX monitorInfo;
		monitorInfo.cbSize = sizeof(MONITORINFOEX);
		GetMonitorInfo(hMonitor, &monitorInfo);
		// Get window rect
		RECT windowRect;
		GetWindowRect(m_platform->hWnd, &windowRect);
		// Check if window is fullscreen
		if(windowRect.left == monitorInfo.rcMonitor.left &&
		   windowRect.top == monitorInfo.rcMonitor.top &&
		   windowRect.right == monitorInfo.rcMonitor.right &&
		   windowRect.bottom == monitorInfo.rcMonitor.bottom &&
		   GetWindowLongPtr(m_platform->hWnd, GWL_STYLE) == WS_POPUP) {
			return window_mode::fullscreen;
		}
		return window_mode::windowed;
	}

}; // namespace sunkell

#endif // SUNKELL_PLATFORM_WIN32
