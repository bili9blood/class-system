#include "native.h"

#ifdef WIN32

static BOOL CALLBACK EnumFrontDesktopWindowCB(HWND hwnd, LPARAM l_param) {
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

static BOOL CALLBACK EnumBackDesktopWindowCB(HWND hwnd, LPARAM l_param) {
  auto *const def_view = ::FindWindowExA(hwnd, nullptr, "SHELLDLL_DefView", nullptr);
  if (!def_view) return TRUE;

  // NOLINTNEXTLINE
  auto *const result_hwnd = (HWND *)l_param;
  *result_hwnd            = ::FindWindowExA(nullptr, hwnd, "WorkerW", nullptr);
  return FALSE;
}

#endif

namespace native {

HWND GetFrontDesktopHwnd() {
#ifdef WIN32
  HWND hwnd{};
  ::EnumWindows(::EnumFrontDesktopWindowCB, (LPARAM)&hwnd);
  return hwnd;
#else
  return nullptr;
#endif
}

HWND GetBackDesktopHwnd() {
#ifdef WIN32
  PDWORD      result{};
  auto *const progman = ::FindWindowA("Progman", nullptr);
  ::SendMessageTimeoutA(progman, 0x052c, 0, 0, SMTO_NORMAL, 0x3e8, (PDWORD_PTR)&result);

  HWND workerw{};
  ::EnumWindows(::EnumBackDesktopWindowCB, (LPARAM)&workerw);

  ::ShowWindow(workerw, SW_HIDE);
  return progman;
#else
  return nullptr;
#endif
}

}  // namespace native
