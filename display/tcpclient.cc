#include "tcpclient.h"

#include <qendian.h>
#include <qtcpsocket.h>
#include <qurl.h>

#include "config.h"
TcpClient::TcpClient(QObject *parent) : QObject{parent} {
  socket_ = std::make_unique<QTcpSocket>();

  connect(socket_.get(), &QTcpSocket::connected, this, &TcpClient::Connected);
  connect(socket_.get(), &QTcpSocket::disconnected, this, &TcpClient::Disconnected);
  connect(socket_.get(), &QTcpSocket::readyRead, this, &TcpClient::HandleReadyRead);
}

TcpClient::~TcpClient() = default;

bool TcpClient::Start() {
  QUrl url{config::Get()["Server"]["url"].value_or("")};
  if (url.isEmpty() || url.scheme() != "tcp") return false;

  socket_->connectToHost(url.host(), url.port(7989));
  return true;
}

void TcpClient::Write(const QByteArray &data) {
  QByteArray arr;
  arr.resize(sizeof(int));
  *(int *)(arr.data()) = qToBigEndian(data.size());
  arr.append(data);

  socket_->write(arr);
}

void TcpClient::HandleReadyRead() {
  while (socket_->bytesAvailable() >= sizeof(int)) {
    int size{};
    socket_->read((char *)&size, sizeof(int));
    size = qFromBigEndian(size);
    if (socket_->bytesAvailable() < size) return;

    QByteArray data;
    data.resize(size);
    socket_->read(data.data(), size);

    Q_EMIT MessageReceived(data);
  }
}
