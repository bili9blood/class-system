#include "config.h"

#include <qapplication.h>

#include <fstream>
#include <optional>

static std::optional<class_system::DisplayConfig> cfg{};

namespace config {
class_system::DisplayConfig &Get() {
  if (cfg) return cfg.value();

  cfg = class_system::DisplayConfig{};
  std::ifstream cfg_file_ifs{QApplication::applicationFilePath().toStdString() + "/config.dat"};
  cfg->ParseFromIstream(&cfg_file_ifs);
  return cfg.value();
}

void Save() {
  if (!cfg) return;
  std::ofstream cfg_file_ofs{QApplication::applicationFilePath().toStdString() + "/config.dat"};
  cfg->SerializeToOstream(&cfg_file_ofs);
}
}  // namespace config
