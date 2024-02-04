#include "server.h"

#include <proto/Request.pb.h>

Server::Server(unsigned short _port, int thread_num) {
  port = _port;

  unpack_setting_t unpack_setting;
  unpack_setting.body_offset         = 4;
  unpack_setting.length_field_offset = 0;
  unpack_setting.length_field_bytes  = 4;
  setUnpack(&unpack_setting);

  onMessage = [](const hv::SocketChannelPtr& channel, hv::Buffer* buf) {
    class_system::Request req{};
    // NOLINTNEXTLINE
    if (req.ParseFromArray((char*)buf->data() + 4, (int)buf->size() - 4))
      req.PrintDebugString();
    else
      printf("error\n");
  };

  setThreadNum(thread_num);
}
