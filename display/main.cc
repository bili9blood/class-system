#include <qapplication.h>
#include <qfontdatabase.h>

#include <csignal>

#include "config.h"
#include "mainwindow.h"
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

  QFontDatabase::addApplicationFont(":/fonts/FiraMono-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/qweather-icons.ttf");

  MainWindow w;
  w.show();

  int code = QApplication::exec();
  config::Save();
  return code;
}
