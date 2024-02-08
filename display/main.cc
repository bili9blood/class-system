#include <qapplication.h>

#include <csignal>

#include "tcpclient.h"

void HandleSignal(int) {
  QApplication::quit();
}

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, HandleSignal);

  QApplication a{argc, argv};

  TcpClient    c;
  c.Start();

  QObject::connect(&c, &TcpClient::Disconnected, &a, &QApplication::quit);

  return QApplication::exec();
}
