#ifndef	__PACKAGE_SENDER_HPP__
#define	__PACKAGE_SENDER_HPP__

#include <vector>
#include <cstddef>

#include "isender.hpp"
#include "package_descriptor.hpp"

namespace communication {
	/// @brief Responsible to pack unpacked data and send it through underlying protocol
	class PackageSender: public ISender<std::vector<char>> {
	public:
		typedef std::vector<char> Payload;

		/// @brief Ctor, creates a new instance of class. The layout of sending messages is configured and maintained by received PackageDescriptor instance
		/// @param package_descriptor a const reference to PackageDescriptor instance describing the layout of sending data
		/// @param packed_data_sender a reference to ISender<std::vector<char>> instance implementing underlying sending protocol
		PackageSender(const PackageDescriptor& package_descriptor, ISender<std::vector<char>>& packed_data_sender);
		PackageSender(const PackageSender& other) = delete;
		PackageSender& operator=(const PackageSender& other) = delete;
		
		/// @brief Packs recieved data and sends it through the underlying sending protocol
		/// @param data unpacked data
		virtual void send(const Payload& data) override;
	private:
		PackageDescriptor m_package_descriptor;
		ISender<std::vector<char>>& m_packed_data_sender;
	}; // PackageSender
} // namespace communication
#endif // __PACKAGE_SENDER_HPP__