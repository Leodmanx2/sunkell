// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "graphics/window.hpp"

namespace sunkell {

	const int DEFAULT_HEIGHT = 576;
	const int DEFAULT_WIDTH  = 1024;

	window_builder::window_builder()
	  : m_width(DEFAULT_WIDTH)
	  , m_height(DEFAULT_HEIGHT)
	  , m_title("untitled sunkell window")
	  , m_mode(window_mode::windowed) {}

	window_builder& window_builder::width(int width) {
		if(width > 0) { m_width = width; }
		return *this;
	}

	window_builder& window_builder::height(int height) {
		if(height > 0) { m_height = height; }
		return *this;
	}

	window_builder& window_builder::title(std::string_view title) {
		m_title = title;
		return *this;
	}

	// TODO: Re-implement icon functionality
	/*window_builder& window_builder::icon(const std::filesystem::path& icon_path) {
		// Validation is deferred to build time
		m_icon_path = icon_path;
		return *this;
	}*/

	window_builder& window_builder::mode(window_mode mode) {
		m_mode = mode;
		return *this;
	}

	window window_builder::build() {
		window new_window;

		new_window.height(m_height);
		new_window.width(m_width);
		new_window.title(m_title);
		new_window.mode(window_mode::windowed);

		if(!m_icon_path.empty()) { new_window.icon(m_icon_path); }

		return new_window;
	}

}; // namespace sunkell
