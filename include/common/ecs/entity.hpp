// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "component.hpp"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace sunkell {

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

} // namespace sunkell
