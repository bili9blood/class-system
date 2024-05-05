#include "updater.h"

#include <qapplication.h>

#include "file.h"
#include "native.h"

Updater::Updater() = default;

Updater::~Updater() = default;

void Updater::OverrideApp(const QString &app_path, const qint64 &pid) {
  if (!native::KillProcesss(pid)) return;

  const QDir target_dir{app_path.left(app_path.lastIndexOf('/'))};
  const QDir src_dir{QApplication::applicationDirPath()};

  file::ForeachDir(src_dir, [&](const QFileInfo &info) {
    const auto abs_dir_path       = info.isFile() ? info.absolutePath() : info.absoluteFilePath();
    const auto file_base_dir_path = file::RelativePath(QFileInfo{abs_dir_path}, src_dir);
    if (!file_base_dir_path.isEmpty() && !target_dir.exists(file_base_dir_path)) target_dir.mkpath(file_base_dir_path);

    if (info.isDir()) return;
    const auto target_file_path = target_dir.absoluteFilePath(file::RelativePath(info, src_dir));
    if (QFile::exists(target_file_path)) QFile::remove(target_file_path);
    QFile::copy(info.absoluteFilePath(), target_file_path);
  });

  const auto target_exe_path = target_dir.filePath(QFileInfo{app_path}.fileName());
  if (QFile::exists(target_exe_path)) QFile::remove(target_exe_path);
  QFile::rename(
      target_dir.filePath(QFileInfo{QApplication::applicationFilePath()}.fileName()),
      target_exe_path
  );
}
