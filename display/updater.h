#pragma once

class Updater : public QObject {
  Q_OBJECT

 public:
  [[nodiscard]] static Updater &Get() {
    static Updater instance;
    return instance;
  }
  ~Updater() override;

  static void OverrideApp(const QString &app_path, const qint64 &pid);

 private:
  explicit Updater();
};
