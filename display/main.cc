#include <qapplication.h>

#include <csignal>

#include "tcpclient.h"

void HandleSignal(int) {
  QApplication::quit();
}

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, HandleSignal);

  QApplication app{argc, argv};

  TcpClient    tcp_client;
  if (!tcp_client.Start()) {
    QMessageBox::critical(nullptr, "错误", "无法创建套接字！");
    return 1;
  }

  return QApplication::exec();
}
