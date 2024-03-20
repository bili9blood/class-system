#pragma once
#include <toml.hpp>

namespace config {

class AutoSaveConfig {
 public:
  ~AutoSaveConfig();
  toml::table&                operator->();
  toml::node_view<toml::node> operator[](const char* k);
};

class AutoSaveConfig Get();
void                 Save();
QString              GetPath();

}  // namespace config
