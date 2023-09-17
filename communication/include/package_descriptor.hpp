#ifndef	__PACKAGE_DESCRIPTOR_HPP__
#define	__PACKAGE_DESCRIPTOR_HPP__

#include <vector>
#include <cstddef>

namespace communication {
	class PackageDescriptor {
	public:
		typedef std::vector<char> Header;
		typedef std::vector<char> Payload;
		typedef std::vector<char> PackageData;
		
		PackageDescriptor(const Header& header, const std::size_t& payload_length_field_size);
		PackageDescriptor(const PackageDescriptor& other) = default;
		PackageDescriptor& operator=(const PackageDescriptor& other) = default;
		~PackageDescriptor() noexcept = default;

		PackageData pack(const Payload& payload) const;

		PackageData pack_payload_length(const std::size_t& payload_length) const;
		std::size_t unpack_payload_length(const PackageData& packed_payload_length) const;

		bool match_header(const Header& header) const;
	private:
		// Constants
		enum {
			MIN_PAYLOAD_LENGTH_FIELD_SIZE = 1,
			MAX_PAYLOAD_LENGTH_FIELD_SIZE = sizeof(std::size_t),
			MIN_HEADER_LENGTH = 4,
			BITS_IN_BYTE = 8, 
			BYTE_MASK = 0xFF
		};

		// Data members
		Header m_header;
		std::size_t m_payload_length_field_size;
	}; // PackageDescriptor
} // namespace communication
#endif // __PACKAGE_DESCRIPTOR_HPP__