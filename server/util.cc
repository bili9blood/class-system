#include "util.h"

namespace util {

hv::BufferPtr MessageToBuf(const google::protobuf::MessageLite& msg) {
  std::string str;
  msg.SerializeToString(&str);

  auto* byte_arr = new char[str.size()];  // will be freed by hv::Buffer
  memcpy(byte_arr, str.c_str(), str.size());

  return std::make_shared<hv::Buffer>(byte_arr, str.size());
}

}  // namespace util
