#include <qapplication.h>
#include <qfontdatabase.h>

#include <csignal>

#include "config.h"
#include "displaywindow.h"
#include "globalstore.h"
#include "iconwindow.h"

void InitFonts() {
  QFont font;
  font.setStyleStrategy(QFont::PreferAntialias);
  font.setHintingPreference(QFont::PreferFullHinting);
  QApplication::setFont(font);

  QFontDatabase::addApplicationFont(":/fonts/FiraMono-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/JiangxiZhuoKai-min.ttf");
  QFontDatabase::addApplicationFont(":/fonts/qweather-icons.ttf");
  QFontDatabase::addApplicationFont(":/fonts/SymbolsNerdFont-Regular.ttf");
}

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, [](int) { QApplication::quit(); });

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication app{argc, argv};

  InitFonts();

  DisplayWindow display_window;
  IconWindow    icon_window;
  icon_window.show();

  GlobalStore::Get()->Start();

  QObject::connect(GlobalStore::Get(), &GlobalStore::FailedHandleResp, [](const QString &error_msg) {
    QMessageBox::critical(nullptr, "错误", "服务器数据响应错误：" + error_msg);
    QApplication::quit();
  });

  int code = QApplication::exec();
  config::Save();
  return code;
}
