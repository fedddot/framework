#ifndef	__ICREATOR_HPP__
#define	__ICREATOR_HPP__

namespace generics {
	template <class Tprod, class Tconf>
	class ICreator {
	public:
		virtual Tprod create(const Tconf& config_data) = 0;
		virtual ~ICreator() noexcept = 0;
	};

	template <class Tprod, class Tconf>
	ICreator<Tprod, Tconf>::~ICreator() noexcept {

	}
} // namespace generics
#endif // __ICREATOR_HPP__