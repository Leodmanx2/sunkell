// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "input_enums.hpp"

namespace sunkell {

	// input_translator is an interface for utilities that map platform-specific
	// input codes to sunkell's internal representations.
	class input_translator {
		public:
		virtual ~input_translator() = default;

		virtual button translate(int key) = 0;
	};

} // namespace sunkell
