#include <proto/Request.pb.h>
#include <qapplication.h>
#include <qfontdatabase.h>
#include <shared/util.h>

#include <csignal>

#include "config.h"
#include "displaywindow.h"
#include "globalstore.h"
#include "tcpclient.h"

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, [](int) { QApplication::quit(); });

  QApplication app{argc, argv};

  QFontDatabase::addApplicationFont(":/fonts/FiraMono-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/qweather-icons.ttf");
  QFontDatabase::addApplicationFont(":/fonts/SymbolsNerdFont-Regular.ttf");

  TcpClient tcp_client;
  if (!tcp_client.Start()) {
    QMessageBox::critical(nullptr, "错误", "无法创建套接字！");
    return 1;
  }

  DisplayWindow display_window;

  QObject::connect(&tcp_client, &TcpClient::MessageReceived, GlobalStore::Get(), &GlobalStore::HandleResponse);
  QObject::connect(GlobalStore::Get(), &GlobalStore::FailedHandleResp, [](const QString &error_msg) {
    QMessageBox::critical(nullptr, "错误", "服务器数据响应错误：" + error_msg);
    QApplication::quit();
  });

  auto &cfg = config::Get();
  auto  req = class_system::Request{};
  req.set_key(cfg.key());
  req.set_request_class_info(true);
  req.set_request_sentences(true);
  tcp_client.Write(util::MessageToBuf(req));

  int code = QApplication::exec();
  config::Save();
  return code;
}
