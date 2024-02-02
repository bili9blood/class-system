#pragma once

#include <hv/TcpServer.h>

class Server : public hv::TcpServer {
 public:
  Server(unsigned short port, int thread_num);

  void start();

 private:
};
