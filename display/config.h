#pragma once
#include <qapplication.h>
#include <qsavefile.h>

#include <sstream>
#include <toml.hpp>

namespace config {

void Save();

namespace _D {
inline std::optional<toml::table> cfg;

class AutoSaveConfig {
 public:
  ~AutoSaveConfig() {
    if (qApp) config::Save();
  }
  toml::table& operator->() { return *cfg; }
  auto         operator[](const char* k) { return (*cfg)[k]; }
} inline auto_save_cfg;

}  // namespace _D

inline QString            GetPath() { return QApplication::applicationDirPath() + "/config.toml"; }

inline _D::AutoSaveConfig Get() {
  if (!_D::cfg) {
    _D::cfg = toml::parse_file(GetPath().toStdString());

#define CONFIG_INSERT(name) \
  if (!_D::cfg->contains(#name)) _D::cfg->insert(#name, toml::table{})

    CONFIG_INSERT(DisplayWindow);
    CONFIG_INSERT(IconWindow);
    CONFIG_INSERT(ExtraWindow);

#undef CONFIG_INSERT
  }

  return {_D::auto_save_cfg};
}

inline void Save() {
  if (!_D::cfg) return;

  QSaveFile file{GetPath()};
  file.open(QIODevice::WriteOnly);

  std::stringstream ss;
  ss << toml::toml_formatter{*_D::cfg};

  file.write(ss.str().c_str());
  file.commit();
}
}  // namespace config
