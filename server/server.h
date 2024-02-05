#pragma once

#include <hv/TcpServer.h>

class Server : public hv::TcpServer {
 public:
  Server(unsigned short port, int thread_num);

 private:
  unpack_setting_t unpack_setting_;

 protected:
  void OnConnection(const hv::SocketChannelPtr& chn) const;
  void OnMessage(const hv::SocketChannelPtr& chn, hv::Buffer* buf) const;
};
