#include "database.h"
#include "server.h"

auto main() -> int {
  Server srv{8979, 4};

  srv.start();
  while (true) hv_msleep(200);
}
