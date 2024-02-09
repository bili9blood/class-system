#include <hv/hloop.h>

namespace constants {

// NOLINTNEXTLINE
inline const auto kUnpackSetting = [] {
  unpack_setting_t setting;
  setting.body_offset         = 4;
  setting.length_field_offset = 0;
  setting.length_field_bytes  = 4;
  return setting;
}();

}  // namespace constants
