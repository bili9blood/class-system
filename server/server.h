#pragma once

#include <hv/TcpServer.h>

class Server : public hv::TcpServer {
 public:
  Server(unsigned short port, int thread_num);

  static void Write(const hv::SocketChannelPtr& chn, const hv::BufferPtr& data);

 protected:
  static void OnConnection(const hv::SocketChannelPtr& chn);
  static void OnMessage(const hv::SocketChannelPtr& chn, hv::Buffer* buf);
};
