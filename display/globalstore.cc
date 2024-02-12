#include "globalstore.h"

GlobalStore::GlobalStore() : QObject(nullptr) {
}

GlobalStore::~GlobalStore() = default;

void GlobalStore::HandleResponse(const QByteArray &resp_buf) {
  auto resp = class_system::Response{};
  if (!resp.ParseFromArray(resp_buf.data(), resp_buf.size())) {
    Q_EMIT FailedHandleResp("解析错误");
    return;
  }
  if (!resp.error_msg().empty()) {
    Q_EMIT FailedHandleResp(QString::fromStdString(resp.error_msg()));
    return;
  }

  Q_EMIT SucceededHandleResp(resp);
}
