#ifndef	__PACKAGE_MANAGER_HPP__
#define	__PACKAGE_MANAGER_HPP__

#include <vector>
#include <cstddef>

#include "isender.hpp"
#include "package_descriptor.hpp"
#include "package_receiver.hpp"
#include "package_sender.hpp"

namespace communication {
	/// @brief Composites instances of PackageReceiver and PackageSender and provides their resources managment and access functionality
	class PackageManager {
	public:
		/// @brief Ctor, creates a new instance of class. Creates receiver and sender instances.
		/// @param package_descriptor a const reference to PackageDescriptor instance describing the layout of receiving/sending data
		/// @param packed_data_sender a reference to ISender<std::vector<char>> instance implementing underlying sending protocol
		PackageManager(const PackageDescriptor& package_descriptor, ISender<std::vector<char>>& packed_data_sender);

		PackageManager(const PackageManager& other) = delete;
		PackageManager& operator=(const PackageManager& other) = delete;

		virtual ~PackageManager() noexcept = default;
		
		/// @brief Accesses receiver
		/// @return reference to receiver
		inline PackageReceiver& receiver();

		/// @brief Accesses sender
		/// @return reference to sender
		inline PackageSender& sender();
	private:
		PackageReceiver m_receiver;
		PackageSender m_sender;
	}; // PackageManager

	inline PackageReceiver& PackageManager::receiver() {
		return std::ref(m_receiver);
	}

	inline PackageSender& PackageManager::sender() {
		return std::ref(m_sender);
	}

} // namespace communication
#endif // __PACKAGE_MANAGER_HPP__