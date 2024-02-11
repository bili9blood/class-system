#pragma once

#include <string>

#ifdef _WIN32
#include <direct.h>
#elif __APPLE__ || __linux__
#include <unistd.h>
#endif

namespace constants {

// NOLINTNEXTLINE
inline const std::string kBasePath = [] {
  // NOLINTNEXTLINE
  const auto *const home_path = getenv("HOME");
  if (home_path) return std::string{home_path};
  char cwd[1024];
  return std::string{getcwd(cwd, 1024) ? cwd : ""};
}();

}  // namespace constants
