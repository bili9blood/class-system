#pragma once

#include <proto/DisplayConfig.pb.h>

namespace config {
class_system::DisplayConfig& Get();
void                         Save();
}  // namespace config
