#include "server.h"

#include <hv/hlog.h>

#include "logic.h"

Server::Server(unsigned short _port, int thread_num) {
  port = _port;

  unpack_setting_.body_offset         = 4;
  unpack_setting_.length_field_offset = 0;
  unpack_setting_.length_field_bytes  = 4;
  setUnpack(&unpack_setting_);

  setThreadNum(thread_num);

  onConnection = std::bind(
      &Server::OnConnection,
      this, std::placeholders::_1
  );
  onMessage = std::bind(
      &Server::OnMessage,
      this, std::placeholders::_1, std::placeholders::_2
  );
}

void Server::OnConnection(const hv::SocketChannelPtr& chn) const {
  LOGI("client %s %s", chn->peeraddr().c_str(), chn->isConnected() ? "connected" : "disconnected");
}

void Server::OnMessage(const hv::SocketChannelPtr& chn, hv::Buffer* buf) const {
  LOGI("recv a message from %s, len=%llu", chn->peeraddr().c_str(), buf->size() - unpack_setting_.body_offset);

  const auto resp = logic::HandleRequest(buf);
  chn->write(resp.get());
}
