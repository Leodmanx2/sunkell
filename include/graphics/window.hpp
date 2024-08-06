// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <String_view>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>

namespace sunkell {

	enum class window_mode { windowed, fullscreen };

	// window provides an abstract interface to one of a variety of possible
	// operating system-specific windowing systems.
	class window {
		friend class window_builder;

		class platform_specific_details;
		std::unique_ptr<platform_specific_details> m_platform;

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
		// TODO: void icon(???);
		void mode(window_mode mode);

		int                width() const;
		int                height() const;
		const std::string& title() const;
		window_mode        mode() const;
	};

	class window_builder {
		int                   m_width;
		int                   m_height;
		std::string           m_title;
		window_mode           m_mode;
		std::filesystem::path m_icon_path;

		public:
		window_builder();
		window_builder(const window_builder&)                = default;
		window_builder& operator=(const window_builder&)     = default;
		window_builder(window_builder&&) noexcept            = default;
		window_builder& operator=(window_builder&&) noexcept = default;
		~window_builder();

		window_builder& width(int width);
		window_builder& height(int height);
		window_builder& title(std::string_view title);
		// TODO: window_builder& icon(???);
		window_builder& mode(window_mode mode);

		[[nodiscard]] window build();
	};

} // namespace sunkell
