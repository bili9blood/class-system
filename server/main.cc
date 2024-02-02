#include "server.h"

auto main() -> int {
  Server srv{8080, 4};

  srv.start();
  while (true) _sleep(1);
}
