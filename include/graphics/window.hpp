// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <String_view>
#include <filesystem>
#include <string>
#include <string_view>

namespace sunkell {

	enum class window_mode { windowed, borderless, fullscreen };

	// window provides an abstract interface to one of a variety of possible
	// operating system-specific windowing systems.
	class window {
		int         m_width;
		int         m_height;
		std::string m_title;
		window_mode m_mode;

		protected:
		window();

		public:
		window(const window&)                = default;
		window& operator=(const window&)     = default;
		window(window&&) noexcept            = default;
		window& operator=(window&&) noexcept = default;
		virtual ~window();

		void show();
		void hide();
		void minimize();
		void maximize();
		void restore();
		void close();
		void focus();

		void resize(int width, int height);
		void width(int width);
		void height(int height);
		void title(std::string_view title);
		void icon(const std::filesystem::path& icon_path);
		void mode(window_mode mode);

		int                width() const { return m_width; }
		int                height() const { return m_height; }
		const std::string& title() const { return m_title; }
		window_mode        mode() const { return m_mode; }
	};

	class window_builder {
		int         m_width;
		int         m_height;
		std::string m_title;
		window_mode m_mode;

		public:
		window_builder();
		window_builder(const window_builder&)                = default;
		window_builder& operator=(const window_builder&)     = default;
		window_builder(window_builder&&) noexcept            = default;
		window_builder& operator=(window_builder&&) noexcept = default;
		~window_builder();

		window_builder& width(int width);
		window_builder& height(int height);
		window_builder& title(const std::string& title);
		window_builder& icon(const std::string& icon);
		window_builder& mode(window_mode mode);

		window build();
	};

} // namespace sunkell
