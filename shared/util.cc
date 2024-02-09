#include "util.h"

#include <sstream>

#ifdef max
#undef max
#endif

namespace util {

hv::BufferPtr MessageToBuf(const google::protobuf::MessageLite& msg) {
  std::string str;
  msg.SerializeToString(&str);

  void* byte_arr{};  // will be freed by hv::Buffer
  if (str.empty()) {
    byte_arr = new char[1];
  } else {
    byte_arr = new char[str.size()];
    memcpy(byte_arr, str.c_str(), str.size());
  }

  return std::make_shared<hv::Buffer>(byte_arr, std::max(1ull, str.size()));
}

std::vector<int> SplitIdsFromStr(std::string_view str) {
  std::vector<int>  ids;
  std::stringstream ss{str.data()};
  std::string       item;
  while (std::getline(ss, item, ',')) {
    ids.push_back(std::stoi(item));
  }
  return ids;
}

}  // namespace util
