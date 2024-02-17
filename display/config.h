#pragma once
#include <qapplication.h>

#include <toml.hpp>

namespace config {

namespace _D {
inline std::optional<toml::table> cfg;
}

inline QString GetPath() { return QApplication::applicationDirPath() + "/config.toml"; }

inline auto& Get() {
  if (!_D::cfg) {
    _D::cfg = toml::parse_file(GetPath().toStdString());

#define CONFIG_INSERT(name) \
  if (!_D::cfg->contains(#name)) _D::cfg->insert(#name, toml::table{})

    CONFIG_INSERT(DisplayWindow);
    CONFIG_INSERT(IconWindow);
    CONFIG_INSERT(ExtraWindow);

#undef CONFIG_INSERT
  }

  return *_D::cfg;
}

inline void Save() {
  if (!_D::cfg) return;
  std::ofstream cfg_ofs{GetPath().toStdString()};
  cfg_ofs << toml::toml_formatter{*_D::cfg};
}
}  // namespace config
