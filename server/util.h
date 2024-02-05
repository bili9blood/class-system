#pragma once

#include <google/protobuf/message_lite.h>
#include <hv/Buffer.h>

namespace util {

hv::BufferPtr MessageToBuf(const google::protobuf::MessageLite& msg);

}
