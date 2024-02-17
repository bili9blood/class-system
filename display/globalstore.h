#pragma once

#include <proto/Response.pb.h>

class GlobalStore final : public QObject {
  Q_OBJECT
 public:
  static GlobalStore *Get() {
    static GlobalStore store;
    return &store;
  }
  ~GlobalStore() final;

 public slots:
  void HandleResponse(const QByteArray &resp);

 signals:
  void SucceededHandleResp(const class_system::Response &resp);
  void FailedHandleResp(const QString &error_msg);

 private:
  explicit GlobalStore();
};
