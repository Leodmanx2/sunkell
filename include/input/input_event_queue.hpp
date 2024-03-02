// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#pragma once

#include "common/event.hpp"
#include "input/input_events.hpp"

#include <functional>
#include <queue>
#include <stdexcept>

namespace sunkell {

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

	class input_event_queue {
		using callback_map =
		  std::unordered_multimap<event, std::function<void(event)>>;
		callback_map m_callbacks;

		std::queue<event> m_event_queue;

		struct platform_specific;
		std::unique_ptr<platform_specific> m_platform;

		// callback_receipt hides the implementation details of the callback map
		class callback_receipt final {
			friend class input_event_queue;

			callback_map::iterator m_iterator;

			explicit callback_receipt(callback_map::iterator iterator)
			  : m_iterator(iterator) {}
		};

		public:
		input_event_queue();

		void
		poll(); // TODO: Make the other functions poll if the queue is looking empty
		void  dispatch_next_event();
		event peek_next_event();
		void  skip_next_event();

		callback_receipt
		     register_callback(event                                     event,
		                       const std::function<void(sunkell::event)> callback);
		void unregister_callback(callback_receipt receipt);
	};

} // namespace sunkell
