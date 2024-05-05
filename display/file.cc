#include "file.h"

namespace file {

void ForeachDir(const QDir &dir, const std::function<void(const QFileInfo &)> &func) {
  for (const QFileInfo &info : dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot)) {
    if (info.isDir())
      ForeachDir(QDir(info.absoluteFilePath()), func);
    func(info);
  }
}

QString RelativePath(const QFileInfo &info, const QDir &base_dir) {
  const auto abs_path = base_dir.absolutePath();
  auto       abs_file = info.absoluteFilePath();
  if (abs_file.startsWith(abs_path))
    return abs_file.mid(abs_path.length() + 1);
  else
    return abs_file;
}

}  // namespace file
