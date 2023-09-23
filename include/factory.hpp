#ifndef	__FACTORY_HPP__
#define	__FACTORY_HPP__

#include <stdexcept>
#include <memory>

#include "registry.hpp"
#include "icreator.hpp"

namespace common {
	template <class Tkey, class Tprod, class Tconf>
	class Factory {
	public:
		Factory() = default;
		Factory(const Factory& other) = default;
		Factory& operator=(const Factory& other) = default;
		~Factory() noexcept = default;

		Tprod create(const Tkey& key, const Tconf& conf);
		void register_creator(const Tkey& key, const std::shared_ptr<ICreator<Tprod, Tconf>>& creator);
		void unregister_creator(const Tkey& key);
		ICreator<Tprod, Tconf>& access_creator(const Tkey& key);
		bool is_registered(const Tkey& key) const;
	private:
		Registry<Tkey, std::shared_ptr<ICreator<Tprod, Tconf>>> m_creators_registry;
	}; // Factory

	template <class Tkey, class Tprod, class Tconf>
	Tprod Factory<Tkey, Tprod, Tconf>::create(const Tkey& key, const Tconf& conf) {
		return access_creator(key).create(conf);
	}

	template <class Tkey, class Tprod, class Tconf>
	void Factory<Tkey, Tprod, Tconf>::register_creator(const Tkey& key, const std::shared_ptr<ICreator<Tprod, Tconf>>& creator) {
		m_creators_registry.register_member(key, creator);
	}

	template <class Tkey, class Tprod, class Tconf>
	void Factory<Tkey, Tprod, Tconf>::unregister_creator(const Tkey& key) {
		m_creators_registry.unregister_member(key);
	}

	template <class Tkey, class Tprod, class Tconf>
	ICreator<Tprod, Tconf>& Factory<Tkey, Tprod, Tconf>::access_creator(const Tkey& key) {
		std::shared_ptr<ICreator<Tprod, Tconf>> creator_ptr = m_creators_registry.access_member(key);
		if (nullptr == creator_ptr) {
			throw std::runtime_error("attempt to access a nullptr creator_ptr");
		}
		return *creator_ptr;		
	}

	template <class Tkey, class Tprod, class Tconf>
	bool Factory<Tkey, Tprod, Tconf>::is_registered(const Tkey& key) const {
		return m_creators_registry.is_registered(key);
	}
} // namespace common
#endif // __FACTORY_HPP__