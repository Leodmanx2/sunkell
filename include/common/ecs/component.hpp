// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

namespace sunkell {

	// Components are data that can be added to an entity. Each component is
	// typically relevant to a specific system. For example, a collision_geometry
	// component provides data for a collision_detector system. Components
	// are "dumb" data structures, holding only data without logic. Systems
	// handle the logic and operate on component data.
	class component {
		protected:
		component() = default;

		public:
		virtual ~component() = default;
	};

} // namespace sunkell
