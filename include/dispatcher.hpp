#ifndef	__DISPATCHER_HPP__
#define	__DISPATCHER_HPP__

#include <stdexcept>
#include <algorithm>
#include <vector>
#include "ilistener.hpp"

namespace common {
	template <class Event>
	class Dispatcher {
	public:
		Dispatcher() = default;
		Dispatcher(const Dispatcher<Event>& other) = default;
		Dispatcher& operator=(const Dispatcher<Event>& other) = default;
		virtual ~Dispatcher() noexcept = default;

		inline void subscribe(IListener<Event> *listener_ptr);
		inline void unsubscribe(IListener<Event> *listener_ptr);
		inline bool is_subscribed(IListener<Event> *listener_ptr) const;
		inline void dispatch(const Event& event);
	private:
		std::vector<IListener<Event> *> m_listeners;
		static inline void throw_if_null(IListener<Event> *listener_ptr);
	};

	template <class Event>
	inline void Dispatcher<Event>::subscribe(IListener<Event> *listener_ptr) {
		throw_if_null(listener_ptr);
		if (is_subscribed(listener_ptr)) {
			throw std::invalid_argument("received listener is already subscribed");
		}
		m_listeners.push_back(listener_ptr);
	}

	template <class Event>
	inline void Dispatcher<Event>::unsubscribe(IListener<Event> *listener_ptr) {
		throw_if_null(listener_ptr);
		auto iter = std::find(m_listeners.begin(), m_listeners.end(), listener_ptr);
		if (m_listeners.end() == iter) {
			throw std::invalid_argument("received listener was not subscribed");
		}
		m_listeners.erase(iter);
	}

	template <class Event>
	inline bool Dispatcher<Event>::is_subscribed(IListener<Event> *listener_ptr) const {
		throw_if_null(listener_ptr);
		auto iter = std::find(m_listeners.begin(), m_listeners.end(), listener_ptr);
		return m_listeners.end() != iter;
	}

	template <class Event>
	inline void Dispatcher<Event>::dispatch(const Event& event) {
		std::for_each(m_listeners.begin(), m_listeners.end(),
			[&](auto listener_ptr) {
				listener_ptr->on_event(event);
			}
		);
	}

	template <class Event>
	inline void Dispatcher<Event>::throw_if_null(IListener<Event> *listener_ptr) {
		if (nullptr == listener_ptr) {
			throw std::invalid_argument("invalid event listener ptr received");
		}
	}
}

#endif // __DISPATCHER_HPP__