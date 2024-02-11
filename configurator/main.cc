#include <qapplication.h>

int main(int argc, char **argv) {
  QApplication app{argc, argv};

  if (argc != 2) {
    QMessageBox::critical(nullptr, "错误", "程序使用方式错误，请参考使用文档！");
    return 1;
  }

  return QApplication::exec();
}
