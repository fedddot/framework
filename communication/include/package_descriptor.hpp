#ifndef	__PACKAGE_DESCRIPTOR_HPP__
#define	__PACKAGE_DESCRIPTOR_HPP__

#include <vector>
#include <cstddef>

namespace communication {
	/// @brief Provides functionality allowing to compose and decompose a serial data package containing header, payload length field and payload serial data
	class PackageDescriptor {
	public:
		typedef std::vector<char> Header;
		typedef std::vector<char> Payload;
		typedef std::vector<char> PackageData;
		
		/// @brief Ctor
		/// @param header a sequence of characters to be located at the start of a package. Must be at least MIN_HEADER_LENGTH characters long
		/// @param payload_length_field_size length of a sequence of characters encoding payload length. Must be at least MIN_PAYLOAD_LENGTH_FIELD_SIZE and at most MAX_PAYLOAD_LENGTH_FIELD_SIZE
		PackageDescriptor(const Header& header, const std::size_t& payload_length_field_size);
		PackageDescriptor(const PackageDescriptor& other) = default;
		PackageDescriptor& operator=(const PackageDescriptor& other) = default;
		~PackageDescriptor() noexcept = default;

		/// @brief Wraps received payload into serial data packet having the following format: [header (const length)][payload length field (const length)][payload (size corresponds to payload length)]
		/// @param payload data to wrap
		/// @return wrapped data
		PackageData pack(const Payload& payload) const;

		/// @brief Encodes received numerical payload_length into serial data packet of size payload_length_field_size
		/// @param payload_length numeric payload length
		/// @return encoded data
		PackageData pack_payload_length(const std::size_t& payload_length) const;

		/// @brief Decodes numerical payload_length from the received package data
		/// @param packed_payload_length encoded payload length
		/// @return numeric payload length
		std::size_t unpack_payload_length(const PackageData& packed_payload_length) const;

		/// @brief Compares received header with one the instance was initialized with
		/// @param header header to match
		/// @return true if the header matches, false otherwise
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