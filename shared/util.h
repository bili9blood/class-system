#pragma once

#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>
#include <hv/Buffer.h>

namespace util {

/**
 * @brief Convert protobuf message to hv::BufferPtr (aka std::shared_ptr<hv::Buffer>)
 *
 * @param msg the protobuf message
 * @return hv::BufferPtr the buffer after converting, never return an empty buffer ptr!
 */
hv::BufferPtr MessageToBuf(const google::protobuf::MessageLite& msg);

std::vector<int> SplitIdsFromStr(std::string_view str);

template <class T, class U = google::protobuf::RepeatedField<T>>
inline U VectorToRepeatedField(const std::vector<T>& vec) {
  return {vec.begin(), vec.end()};
}
}
