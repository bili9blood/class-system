#include "updater.h"

#include <qapplication.h>
#include <qprocess.h>

#include <nlohmann/json.hpp>

#include "config.h"
#include "file.h"
#include "httpclient.h"
#include "native.h"
#include "progresswindow.h"
#include "version.h"

Updater::Updater() {
  nam_ = std::make_unique<QNetworkAccessManager>();
}

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

void Updater::CheckForUpdates() {
  auto const *base_url{config::Get()["Server"]["url"].as_string()->get().c_str()};

  QEventLoop     loop;
  nlohmann::json latest_json;

  HttpClient{QString{base_url}.replace(QRegExp{"/+$"}, "") + "/api/version/latest"}
      .success([&](const auto &resp) {
        latest_json = nlohmann::json::parse(resp.toUtf8().data());
        loop.quit();
      })
      .get();
  loop.exec();

  if (latest_json["code"] != 200) {
    QMessageBox::critical(
        nullptr,
        "错误", QString::asprintf("无法获取最新版本：%s", latest_json["message"].get<std::string>().c_str())
    );
    return;
  }

  latest_json               = latest_json["data"];
  const auto latest_version = latest_json["version"].get<std::string>();
  if (latest_version == std::string{kVersion}) return;

  progress_window_ = std::make_unique<ProgressWindow>();
  progress_window_->setWindowTitle("下载进度");
  progress_window_->SetLabelText("正在下载更新包，请稍候...");
  progress_window_->show();

  download_file_.setFileName(
      QDir::temp().absoluteFilePath(
          QString::asprintf("class-system-display_%s.zip", latest_version.c_str())
      )
  );

  download_file_.open(QIODevice::WriteOnly | QIODevice::Truncate);

  QNetworkRequest req{QUrl{latest_json["url"].get<std::string>().c_str()}};
  reply_ = nam_->get(req);
  connect(reply_, &QNetworkReply::finished, this, &Updater::HandleReplyFinished);
  connect(reply_, &QNetworkReply::downloadProgress, this, &Updater::HandleReplyProgress);
  connect(reply_, &QNetworkReply::readyRead, this, &Updater::HandleReplyReadyRead);
}

void Updater::HandleReplyFinished() {
  progress_window_->close();
  download_file_.close();

  if (reply_->error() != QNetworkReply::NoError) {
    QMessageBox::critical(
        nullptr,
        "错误", QString::asprintf("无法下载更新：%s", reply_->errorString().toUtf8().data())
    );
    return;
  }

  reply_->deleteLater();

  QDir extract_dir{QDir::temp().absoluteFilePath("class-system-display__update__cache")};
  if (extract_dir.exists()) extract_dir.removeRecursively();
  extract_dir.mkpath(extract_dir.absolutePath());

  QProcess extract_proc;
  extract_proc.setProgram("powershell.exe");
  extract_proc.setArguments({"-Command", "-"});
  extract_proc.start();
  extract_proc.waitForStarted();

  const auto extract_cmd = QString::asprintf(
      "Expand-Archive -LiteralPath '%s' -DestinationPath %s",
      download_file_.fileName().replace('/', '\\').toLocal8Bit().data(),
      extract_dir.absolutePath().replace('/', '\\').toLocal8Bit().data()
  );

  extract_proc.write(extract_cmd.toLocal8Bit());
  extract_proc.closeWriteChannel();
  extract_proc.waitForFinished();

  download_file_.remove();
  QProcess::startDetached(extract_dir.absoluteFilePath("class-system-display.exe"), {});
}

void Updater::HandleReplyProgress(qint64 cur, qint64 total) {
  progress_window_->SetRange(0, (int)total);
  progress_window_->SetValue((int)cur);
}

void Updater::HandleReplyReadyRead() {
  download_file_.write(reply_->readAll());
}
