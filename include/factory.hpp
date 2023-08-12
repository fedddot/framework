#ifndef	__FACTORY_HPP__
#define	__FACTORY_HPP__

#include <map>
#include <memory>
#include <stdexcept>

#include "icreator.hpp"

namespace common {
	template <class Tkey, class Tprod, class Tconf>
	class Factory {
	public:
		~Factory() noexcept = default;
		Tprod create(const Tkey& key, const Tconf& conf);
		void register_creator(const Tkey& key, const std::shared_ptr<ICreator<Tprod, Tconf>>& creator);
	private:
		std::map<Tkey, std::shared_ptr<ICreator<Tprod, Tconf>>> m_creators;
	}; // Factory

	template <class Tkey, class Tprod, class Tconf>
	Tprod Factory<Tkey, Tprod, Tconf>::create(const Tkey& key, const Tconf& conf) {
		auto iter = m_creators.find(key);
		if (m_creators.end() == iter) {
			throw std::invalid_argument("creator for received key was not registered");
		}
		return iter->second->create(conf);
	}

	template <class Tkey, class Tprod, class Tconf>
	void Factory<Tkey, Tprod, Tconf>::register_creator(const Tkey& key, const std::shared_ptr<ICreator<Tprod, Tconf>>& creator) {
		if (nullptr == creator) {
			throw std::invalid_argument("creator can not be a nullptr");
		}
		m_creators[key] = creator;
	}
} // namespace common
#endif // __FACTORY_HPP__