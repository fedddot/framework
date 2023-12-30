#ifndef	TEST_LISTENER_HPP
#define	TEST_LISTENER_HPP

#include "ilistener.hpp"
#include <functional>

namespace generics_tests {
	template <class Tevent>
	class TestListener: public generics::IListener<Tevent> {
	public:
		inline TestListener(const std::function<void(const Tevent&)>& on_event_cb);
		virtual inline void on_event(const Tevent& event) override;
	private:
		std::function<void(const Tevent&)> m_on_event_cb;
	};

	template <class Tevent>
	inline TestListener<Tevent>::TestListener(const std::function<void(const Tevent&)>& on_event_cb): m_on_event_cb(on_event_cb) {

	}

	template <class Tevent>
	inline void TestListener<Tevent>::on_event(const Tevent& event) {
		m_on_event_cb(event);
	}
}
#endif // TEST_LISTENER_HPP