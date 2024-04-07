#pragma once
#include "config.h"

#include <qapplication.h>
#include <qsavefile.h>

#include <sstream>

static std::optional<toml::table> cfg;
static config::AutoSaveConfig     auto_save_cfg;

namespace config {

AutoSaveConfig::~AutoSaveConfig() {
  if (qApp) Save();
}
toml::table&                AutoSaveConfig::operator->() { return *cfg; }
toml::node_view<toml::node> AutoSaveConfig::operator[](const char* k) { return (*cfg)[k]; }

AutoSaveConfig Get() {
  if (!cfg) {
    cfg = toml::parse_file(GetPath().toStdString());

#define CONFIG_INSERT(name) \
  if (!cfg->contains(#name)) cfg->insert(#name, toml::table{})

    CONFIG_INSERT(DisplayWindow);
    CONFIG_INSERT(IconWindow);
    CONFIG_INSERT(ExtraWindow);

#undef CONFIG_INSERT
  }

  return {auto_save_cfg};
}

void Save() {
  if (!cfg) return;

  QSaveFile file{GetPath()};
  file.open(QIODevice::WriteOnly);

  std::stringstream ss;
  ss << toml::toml_formatter{*cfg};

  file.write(QString{ss.str().c_str()}.replace("\n", "\r\n").toLocal8Bit());
  file.commit();
}

QString GetPath() { return QApplication::applicationDirPath() + "/config.toml"; }

}  // namespace config
