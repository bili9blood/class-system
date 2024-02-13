#pragma once
#include <qapplication.h>

#include <toml.hpp>

namespace config {

namespace _D {
inline std::optional<toml::table> cfg;
}

inline auto& Get() {
  if (!_D::cfg) _D::cfg = toml::parse_file(QApplication::applicationDirPath().toStdString() + "/config.toml");
  return *_D::cfg;
}

inline void Save() {
  if (!_D::cfg) return;
  std::ofstream cfg_ofs{QApplication::applicationDirPath().toStdString() + "/config.toml"};
  cfg_ofs << toml::toml_formatter{*_D::cfg};
}
}  // namespace config
