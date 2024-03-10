#include "native.h"

#ifdef WIN32

static BOOL CALLBACK EnumDesktopViewWindowCB(HWND hwnd, LPARAM l_param) {
  const auto wflags = ::GetWindowLongA(hwnd, GWL_STYLE);
  if (!(wflags & WS_VISIBLE)) return TRUE;

  auto *const def_view{::FindWindowExA(hwnd, nullptr, "SHELLDLL_DefView", nullptr)};
  if (!def_view) return TRUE;

  auto *const tgt_window{::FindWindowExA(def_view, nullptr, "SysListView32", "FolderView")};
  if (!tgt_window) return TRUE;

  // NOLINTNEXTLINE
  auto *const result_hwnd = (HWND *)l_param;
  *result_hwnd            = tgt_window;
  return FALSE;
}

#endif

namespace native {

HWND GetDesktopViewHwnd() {
#ifdef WIN32
  HWND hwnd{};
  ::EnumWindows(::EnumDesktopViewWindowCB, (LPARAM)&hwnd);
  return hwnd;
#else
  return nullptr;
#endif
}

}  // namespace native
