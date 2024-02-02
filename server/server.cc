#include "server.h"

Server::Server(unsigned short _port, int thread_num) {
  port = _port;

  unpack_setting_t unpack_setting;
  unpack_setting.body_offset = 1,
  unpack_setting.length_field_offset = 0,
  unpack_setting.length_field_bytes = 1,
  unpack_setting.length_field_coding = ENCODE_BY_VARINT;
  setUnpack(&unpack_setting);

  onMessage = [](const hv::SocketChannelPtr& channel, hv::Buffer* buf) {
    printf("< %.*s\n", (int)buf->size(), (char*)buf->data());
    channel->write(buf);
  };

  setThreadNum(thread_num);
}
