#include "tcpclient.h"

#include <qendian.h>
#include <qurl.h>
#include <shared/constants.h>

#include "config.h"

TcpClient::TcpClient(QObject *parent) : QObject(parent) {
  client_.setUnpack(&const_cast<unpack_setting_t &>(constants::kUnpackSetting));

  client_.onMessage = [this](const hv::SocketChannelPtr &, hv::Buffer *buf) {
    const auto arr = QByteArray{(char *)buf->data() + 4, (int)buf->size() - 4};
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
  const auto cfg        = config::Get();
  const auto server_url = QUrl{QString::fromStdString(cfg.server_url())};
  if (!server_url.isValid() || server_url.scheme() != "tcp") return false;
  if (client_.createsocket(server_url.port(7989), server_url.host().toUtf8()) < 0) return false;
  client_.start();
  return true;
}

int TcpClient::Write(const QByteArray &data) {
  if (data.isEmpty())
    return 0;

  QByteArray arr;
  arr.resize(sizeof(int));
  *(int *)(arr.data()) = qToBigEndian(data.size());
  arr.append(data);

  client_.send(new hv::Buffer{arr.data(), (size_t)arr.size()});
  return data.size();
}

int TcpClient::Write(const hv::BufferPtr &data) {
  return Write(QByteArray{(char *)data->data(), (int)data->size()});
}
