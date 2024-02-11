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

void          SplitIdsFromStr(std::string_view str, google::protobuf::RepeatedField<int>* ids);
}
