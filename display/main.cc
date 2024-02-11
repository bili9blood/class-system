#include <qapplication.h>
#include <qfontdatabase.h>

#include <csignal>

#include "config.h"
#include "displaywindow.h"
#include "tcpclient.h"

void HandleSignal(int) {
  QApplication::quit();
}

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, HandleSignal);

  QApplication app{argc, argv};

  QFontDatabase::addApplicationFont(":/fonts/FiraMono-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/qweather-icons.ttf");

  TcpClient    tcp_client;
  if (!tcp_client.Start()) {
    QMessageBox::critical(nullptr, "错误", "无法创建套接字！");
    return 1;
  }
  QFont().defaultFamily();  // load fonts

  DisplayWindow w;

  int code = QApplication::exec();
  config::Save();
  return code;
}
