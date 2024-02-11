#include <qapplication.h>
#include <qfile.h>
#include <qfileinfo.h>

#include "configwindow.h"

void HandleUsageError() {
  QMessageBox::critical(nullptr, "错误", "程序使用方式错误，请参考使用文档！");
  // NOLINTNEXTLINE
  exit(1);
}

int main(int argc, char **argv) {
  QApplication app{argc, argv};

  if (argc != 2) HandleUsageError();

  QWidget   *w{};

  const auto base_name = QFileInfo{QApplication::arguments()[1]}.baseName();
  if (base_name == "class-system-display") {
    w = new ConfigWindow{ConfigApp::CLASS_SYSTEM_DISPLAY};
  } else if (base_name == "class-system-manage") {
    w = new ConfigWindow{ConfigApp::CLASS_SYSTEM_MANAGE};
  } else
    HandleUsageError();

  if (!QFile::exists("config.dat")) HandleUsageError();

  w->show();
  return QApplication::exec();
}
