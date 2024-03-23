// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

namespace sunkell {

	class event {
		public:
		event() noexcept                        = default;
		event(const event&) noexcept            = default;
		event(event&&) noexcept                 = default;
		virtual ~event() noexcept               = default;
		event& operator=(const event&) noexcept = default;
		event& operator=(event&&) noexcept      = default;
	};

} // namespace sunkell
