#ifndef	__IFEATURE_HPP__
#define	__IFEATURE_HPP__

namespace common {
	class IFeature {
	public:
		virtual ~IFeature() noexcept = 0;
		virtual void enable() = 0;
		virtual void disable() = 0;
		virtual bool is_enabled() const = 0;
	}; // IFeature
} // namespace common

#endif // __IFEATURE_HPP__