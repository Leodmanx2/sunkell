// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "entity.hpp"

#include <chrono>

namespace sunkell {

	// Systems wrap logic and perform operations on entities with specific sets of
	// components. For example, a collision_detector system operates on entities
	// that have a collision_geometry component. Systems contain only the state
	// they need to perform their operations and do not contain any data that is
	// specific to a particular entity.
	class system {
		protected:
		system() = default;

		public:
		virtual ~system() = default;

		// Process once-per-frame changes to an entity. The delta parameter
		// is the time since the last frame in femtoseconds.
		virtual void update(entity&                                   entity,
		                    std::chrono::duration<double, std::femto> delta) = 0;
	};

} // namespace sunkell
