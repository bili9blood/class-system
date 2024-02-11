#include "resphandler.h"

RespHandler::RespHandler(QObject *parent) : QObject(parent) {}

RespHandler::~RespHandler() = default;

void RespHandler::HandleResponse(const QByteArray &resp_buf) {
  auto resp = class_system::Response{};
  if (!resp.ParseFromArray(resp_buf.data(), resp_buf.size())) {
    Q_EMIT Failed("解析错误");
    return;
  }
  if (!resp.error_msg().empty()) {
    Q_EMIT Failed(QString::fromStdString(resp.error_msg()));
    return;
  }

  Q_EMIT Succeeded(resp);
}
