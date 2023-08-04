#ifndef	__IDATA_SERIALIZER_HPP__
#define	__IDATA_SERIALIZER_HPP__

#include <memory>
#include <string>
#include "idata.hpp"

namespace data {
	class IDataSerializer {
	public:
		virtual std::string serialize(const IData& data) = 0;
		virtual ~IDataSerializer() noexcept = 0;
	}; // IDataSerializer
} // namespace data

#endif // __IDATA_SERIALIZER_HPP__