#ifndef	__ISENDER_HPP__
#define	__ISENDER_HPP__

namespace communication {
	template <class T>
	class ISender {
	public:
		virtual ~ISender() noexcept = 0;
		virtual void send(const T& data) = 0;
	}; // ISender

	template <class T>
	ISender<T>::~ISender() noexcept {
		
	}
} // namespace communication
#endif // __ISENDER_HPP__