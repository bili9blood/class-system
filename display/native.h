#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

namespace native {

HWND GetFrontDesktopHwnd();
HWND GetBackDesktopHwnd();

}  // namespace native
