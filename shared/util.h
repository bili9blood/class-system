#pragma once

#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <hv/Buffer.h>

namespace util {

bool IsLittleEndian();

template <typename _T>
_T ToBigEndian(const _T& val) {
  if (IsLittleEndian()) return val;

  using T = std::decay_t<_T>;

  if constexpr (std::is_same_v<T, unsigned short>)
    return htons(val);
  else if constexpr (std::is_same_v<T, int>)
    return htond(val);
  else if constexpr (std::is_same_v<T, unsigned long>)
    return htonl(val);
  else if constexpr (std::is_same_v<T, unsigned long long>)
    return htonll(val);
  else if constexpr (std::is_same_v<T, float>)
    return htonf(val);
  else
    return val;
}

/**
 * @brief Convert protobuf message to hv::BufferPtr (aka std::shared_ptr<hv::Buffer>)
 *
 * @param msg the protobuf message
 * @return hv::BufferPtr the buffer after converting, never return an empty buffer ptr!
 */
hv::BufferPtr MessageToBuf(const google::protobuf::MessageLite& msg);

void          SplitIdsFromStr(std::string_view str, google::protobuf::RepeatedField<int>* ids);
}
