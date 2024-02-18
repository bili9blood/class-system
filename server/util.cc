#include "util.h"

#include <ctime>
#include <iomanip>
#include <sstream>

#ifdef _WIN32
#include <direct.h>
#elif __APPLE__ || __linux__
#include <unistd.h>
#endif

namespace util {

std::string GetCurrentDate(std::string_view format) {
  const auto t = std::time(nullptr);
  // NOLINTNEXTLINE
  const auto tm = *localtime(&t);
  auto       ss = std::stringstream{};
  ss << std::put_time(&tm, format.data());
  return ss.str();
}

void SplitIdsFromStr(std::string_view str, google::protobuf::RepeatedField<int>* ids) {
  std::stringstream ss{str.data()};
  std::string       item;
  while (std::getline(ss, item, ',')) {
    ids->Add(std::stoi(item));
  }
}

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

  return std::make_shared<hv::Buffer>(byte_arr, std::max<size_t>(1, str.size()));
}

std::string GetBasePath() {
  // NOLINTNEXTLINE
  const auto* const home_path = getenv("HOME");
  if (home_path) return std::string{home_path};
  char cwd[1024];
  return std::string{getcwd(cwd, 1024) ? cwd : ""};
}

}  // namespace util
