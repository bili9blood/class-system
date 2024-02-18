#pragma once

class QTcpSocket;

class TcpClient final : public QObject {
  Q_OBJECT
 public:
  explicit TcpClient(QObject *parent = nullptr);
  ~TcpClient() final;

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
   */
  void Write(const QByteArray &data);

 signals:
  void MessageReceived(const QByteArray &msg);
  void Connected();
  void Disconnected();

 private:
  std::unique_ptr<QTcpSocket> socket_;

 private slots:
  void HandleReadyRead();
};
