#pragma once

#include "hv/TcpClient.h"

class TcpClient : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject *parent = nullptr);
  ~TcpClient() override;

  /**
   * @brief start tcp client
   *
   * @return true succeeded
   * @return false failed
   */
  bool Start();

  /**
   * @brief write data into socket with length header
   *
   * @param data data to be sent
   * @return int length of data
   */
  int Write(const QByteArray &data);

  //! overload
  int Write(const hv::BufferPtr &data);

 signals:
  void MessageReceived(const QByteArray &msg);
  void Connected();
  void Disconnected();

 private:
  hv::TcpClient client_;
};
