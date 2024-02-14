#include "util.h"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace util {

std::string GetCurrentDate(std::string_view format) {
  const auto t = std::time(nullptr);
  // NOLINTNEXTLINE
  const auto tm = *localtime(&t);
  auto       ss = std::stringstream{};
  ss << std::put_time(&tm, format.data());
  return ss.str();
}

}  // namespace util
