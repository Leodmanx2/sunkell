// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>

namespace sunkell {

	class window_creation_error : public std::runtime_error {
		public:
		explicit window_creation_error(const std::string& message)
		  : std::runtime_error(message) {}
	};

	enum class window_mode : std::uint8_t { windowed, fullscreen };

	// Tags are used to help identify platform-specific details
	struct WindowTag {};
	struct IconTag {};

	// window provides an abstract interface to one of a variety of possible
	// operating system-specific windowing systems.
	class window {
		friend class window_builder;

		class platform_specific_details;
		std::unique_ptr<platform_specific_details> m_platform;

		protected:
		window();
		window(const window&)            = delete;
		window& operator=(const window&) = delete;
		window(window&&) noexcept;
		window& operator=(window&&) noexcept;

		public:
		~window();
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

		template <typename T, typename Tag>
		T& platform_detail();

		template <typename T, typename Tag>
		const T& platform_detail() const;
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
		~window_builder()                                    = default;

		window_builder& width(int width);
		window_builder& height(int height);
		window_builder& title(std::string_view title);
		// TODO: window_builder& icon(???);
		window_builder& mode(window_mode mode);

		[[nodiscard]] window build();
	};

} // namespace sunkell
