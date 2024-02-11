#include "tcpclient.h"

#include <shared/constants.h>
#include <shared/util.h>

TcpClient::TcpClient(QObject *parent) : QObject(parent) {
  client_.setUnpack(&const_cast<unpack_setting_t &>(constants::kUnpackSetting));

  client_.onMessage = [this](const hv::SocketChannelPtr &, hv::Buffer *buf) {
    const auto arr = QByteArray{(char *)buf->data(), (int)buf->size()};
    Q_EMIT MessageReceived(arr);
  };

  client_.onConnection = [this](const hv::SocketChannelPtr &chn) {
    if (chn->isConnected())
      Q_EMIT Connected();
    else
      Q_EMIT Disconnected();
  };
}

TcpClient::~TcpClient() = default;

bool TcpClient::Start() {
  if (client_.createsocket(7989, "localhost") < 0) return false;
  client_.start();
  return true;
}

int TcpClient::Write(const QByteArray &data) {
  if (data.isEmpty())
    return 0;

  QByteArray arr;
  arr.resize(sizeof(int));
  *(int *)(arr.data()) = util::ToBigEndian(data.size());
  arr.append(data);

  client_.send(new hv::Buffer{arr.data(), (size_t)arr.size()});
  return data.size();
}
