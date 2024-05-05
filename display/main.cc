#include <qapplication.h>
#include <qdatastream.h>
#include <qfile.h>
#include <qfontdatabase.h>
#include <qlockfile.h>
#include <qprocess.h>

#include <csignal>

#include "displaywindow.h"
#include "globalstore.h"
#include "iconwindow.h"
#include "updater.h"

void InitFonts() {
  QFont font;
  font.setStyleStrategy(QFont::PreferAntialias);
  font.setHintingPreference(QFont::PreferFullHinting);
  QApplication::setFont(font);

  QFontDatabase::addApplicationFont(":/fonts/FiraMono-Bold.ttf");
  QFontDatabase::addApplicationFont(":/fonts/ZiHunBianTaoTi-min.ttf");
  QFontDatabase::addApplicationFont(":/fonts/qweather-icons.ttf");
  QFontDatabase::addApplicationFont(":/fonts/SymbolsNerdFont-Regular.ttf");
}

bool CheckState() {
  static QLockFile lock_file{QDir::temp().absoluteFilePath("class-system-display.lock")};
  QFile            state_file{QDir::temp().absoluteFilePath("class-system-display.state")};

  if (!lock_file.tryLock(100)) {
    if (!state_file.open(QFile::ReadOnly)) return false;
    QDataStream in{&state_file};
    QString     app_path;
    qint64      pid{};
    in >> app_path >> pid;

    if (app_path.isEmpty() || app_path == QApplication::applicationFilePath()) return false;

    Updater::OverrideApp(app_path, pid);
    state_file.remove();
    QProcess::startDetached(app_path, {});

    return false;
  } else {
    if (!state_file.open(QFile::WriteOnly | QFile::Truncate)) return false;
    QDataStream out{&state_file};
    /*app path*/ out << QApplication::applicationFilePath();
    /*pid*/ out << QApplication::applicationPid();
  }
  return true;
}

auto main(int argc, char **argv) -> int {
  (void)signal(SIGINT, [](int) { QApplication::quit(); });

  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);

  QApplication app{argc, argv};

  InitFonts();
  if (!CheckState()) return 1;

  DisplayWindow display_window;
  IconWindow    icon_window;
  icon_window.show();

  GlobalStore::Get().Start();

  QObject::connect(&GlobalStore::Get(), &GlobalStore::FailedHandleResp, [](const QString &error_msg) {
    QMessageBox::critical(nullptr, "错误", "服务器数据响应错误：" + error_msg);
    QApplication::quit();
  });

  return QApplication::exec();
}
