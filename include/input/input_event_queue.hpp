// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "common/event.hpp"

#include <functional>
#include <queue>
#include <stdexcept>

#ifdef SUNKELL_PLATFORM_WIN32
#include <Windows.h>
#endif

namespace sunkell {

	// Forward declarations
	class window;

	class device_registration_error : public std::runtime_error {
		public:
		explicit device_registration_error(const std::string& message)
		  : std::runtime_error(message) {}
	};

	class input_poll_failure : public std::runtime_error {
		public:
		explicit input_poll_failure(const std::string& message)
		  : std::runtime_error(message) {}
	};

	class empty_queue_error : public std::runtime_error {
		public:
		explicit empty_queue_error(const std::string& message)
		  : std::runtime_error(message) {}
	};

	class input_event_queue {
		using callback_map =
		  std::unordered_multimap<std::shared_ptr<event>,
		                          std::function<void(std::shared_ptr<event>)>>;
		callback_map m_callbacks;

		std::queue<std::shared_ptr<event>> m_event_queue;

		// callback_receipt hides the implementation details of the callback map
		class callback_receipt final {
			friend class input_event_queue;

			callback_map::iterator m_iterator;

			explicit callback_receipt(callback_map::iterator iterator)
			  : m_iterator(iterator) {}
		};

		public:
		input_event_queue();
		explicit input_event_queue(const window* window);
#ifdef SUNKELL_PLATFORM_WIN32
		// TODO: Remove this constructor once the window class is implemented
		explicit input_event_queue(HWND window);
#endif

		[[nodiscard]] constexpr bool empty() const { return m_event_queue.empty(); }
		void                         poll();
		void                         dispatch_next_event();
		std::shared_ptr<event>       peek_next_event();
		void                         skip_next_event();

		callback_receipt register_callback(
		  std::shared_ptr<event>                             trigger_event,
		  const std::function<void(std::shared_ptr<event>)>& callback);
		void unregister_callback(callback_receipt& receipt);
	};

} // namespace sunkell
