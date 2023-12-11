#ifndef	__PACKAGE_DESCRIPTOR_HPP__
#define	__PACKAGE_DESCRIPTOR_HPP__

#include <vector>
#include <cstddef>

namespace communication {
	class PackageDescriptor {
	public:
		typedef typename std::vector<char> Data;
		typedef typename std::size_t DataSize;
		
		PackageDescriptor(const Data& signature);
		PackageDescriptor(const PackageDescriptor& other) = default;
		PackageDescriptor& operator=(const PackageDescriptor& other) = default;
		~PackageDescriptor() noexcept = default;

		bool validate(const Data& desc_data) const;
		DataSize data_size(const Data& desc_data) const;
		inline DataSize desc_size() const;
		Data pack(const Data& raw_data) const;
	private:
		enum { BITS_IN_BYTE = 8 };
		Data m_signature;
		static Data pack_data_size(const DataSize& data_size);
	}; // PackageDescriptor

	inline PackageDescriptor::DataSize PackageDescriptor::desc_size() const {
		return m_signature.size() + sizeof(DataSize);
	}
} // namespace communication
#endif // __PACKAGE_DESCRIPTOR_HPP__