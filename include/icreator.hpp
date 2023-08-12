#ifndef	__ICREATOR_HPP__
#define	__ICREATOR_HPP__

namespace common {
	template <class Tprod, class Tconf>
	class ICreator {
	public:
		virtual Tprod create(Tconf config_data) = 0;
		virtual ~ICreator() noexcept = 0;
	};

	template <class Tprod, class Tconf>
	ICreator<Tprod, Tconf>::~ICreator() noexcept {

	}
} // namespace common
#endif // __ICREATOR_HPP__