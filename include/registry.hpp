#ifndef	__REGISTRY_HPP__
#define	__REGISTRY_HPP__

#include <map>
#include <stdexcept>

namespace common {
	template <class Tkey, class Tmember>
	class Registry {
	public:
		virtual ~Registry() noexcept = default;
		void register_member(const Tkey& key, const Tmember& member);
		void unregister_member(const Tkey& key);
		Tmember& access_member(const Tkey& key);
		bool is_registered(const Tkey& key) const;
	private:
		std::map<Tkey, Tmember> m_members;
	}; // Registry

	template <class Tkey, class Tmember>
	void Registry<Tkey, Tmember>::register_member(const Tkey& key, const Tmember& member) {
		if (m_members.end() != m_members.find(key)) {
			throw std::invalid_argument("received key is already registered");
		}
		m_members.insert(std::pair(key, member));
	}

	template <class Tkey, class Tmember>
	void Registry<Tkey, Tmember>::unregister_member(const Tkey& key) {
		auto iter = m_members.find(key);
		if (m_members.end() == iter) {
			throw std::invalid_argument("received key was not registered");
		}
		m_members.erase(iter);
	}

	template <class Tkey, class Tmember>
	Tmember& Registry<Tkey, Tmember>::access_member(const Tkey& key) {
		auto iter = m_members.find(key);
		if (m_members.end() == iter) {
			throw std::invalid_argument("received key was not registered");
		}
		return std::ref(iter->second);
	}

	template <class Tkey, class Tmember>
	bool Registry<Tkey, Tmember>::is_registered(const Tkey& key) const {
		return m_members.end() != m_members.find(key);
	}
} // namespace common
#endif // __REGISTRY_HPP__