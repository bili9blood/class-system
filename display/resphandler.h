#pragma once

#include <proto/Response.pb.h>

class RespHandler : public QObject {
  Q_OBJECT
 public:
  explicit RespHandler(QObject *parent = nullptr);
  ~RespHandler() override;

 public slots:
  void HandleResponse(const QByteArray &resp);

 signals:
  void Succeeded(const class_system::Response &resp);
  void Failed(const QString &error_msg);
};
