// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

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

	// An entity is a container for components, allowing only one component of
	// each type. Components can be added, removed, and accessed by their type
	// at runtime.
	class entity final {
		std::unordered_map<std::type_index, std::shared_ptr<component>>
		  m_components;

		public:
		// Add a component to the entity. If a component of the same type is
		// already present, it is replaced.
		template <typename T>
		constexpr void add_component(std::shared_ptr<T> component) {
			m_components[std::type_index(typeid(T))] = component;
		}

		// Remove a component from the entity. If no component of the given
		// type is present, this function does nothing.
		template <typename T>
		constexpr void remove_component() {
			m_components.erase(std::type_index(typeid(T)));
		}

		// Get a component from the entity. If no component of the given type
		// is present, this function returns nullptr.
		template <typename T>
		constexpr std::shared_ptr<T> get_component() const {
			const auto& it = m_components.find(std::type_index(typeid(T)));
			if(it == m_components.end()) { return nullptr; }
			return std::static_pointer_cast<T>(it->second);
		}
	};

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
