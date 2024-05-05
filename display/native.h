#pragma once

#ifdef WIN32
#include <Windows.h>
#endif

namespace native {

HWND GetDesktopViewHwnd();

bool KillProcesss(qint64 pid);

}  // namespace native
