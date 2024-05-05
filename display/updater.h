#pragma once

class QNetworkAccessManager;
class QNetworkReply;

class ProgressWindow;

class Updater : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static Updater &Get() {
    static Updater instance;
    return instance;
  }
  ~Updater() override;

  static void OverrideApp(const QString &app_path, const qint64 &pid);

  void CheckForUpdates();

 private:
  explicit Updater();

  std::unique_ptr<QNetworkAccessManager> nam_;
  QNetworkReply                         *reply_{};
  QFile                                  download_file_;

  std::unique_ptr<ProgressWindow> progress_window_;

 private slots:
  void HandleReplyFinished();
  void HandleReplyProgress(qint64 cur, qint64 total);
  void HandleReplyReadyRead();
};
