#include "server.h"

#include <hv/hendian.h>
#include <hv/hlog.h>
#include <shared/constants.h>

#include "logic.h"

Server::Server(unsigned short _port, int thread_num) {
  port = _port;

  setUnpack(&const_cast<unpack_setting_t&>(constants::kUnpackSetting));
  setThreadNum(thread_num);

  onConnection = std::bind(
      &Server::OnConnection,
      std::placeholders::_1
  );
  onMessage = std::bind(
      &Server::OnMessage,
      std::placeholders::_1, std::placeholders::_2
  );
}

void Server::Write(const hv::SocketChannelPtr& chn, const hv::BufferPtr& data) {
  if (data->size() == 0) return;

  auto* buf            = new hv::Buffer(data->size() + constants::kUnpackSetting.body_offset);
  *(int*)(buf->data()) = htobe32(buf->size());
  memcpy((char*)buf->data() + constants::kUnpackSetting.body_offset, data->data(), data->size());
  chn->write(buf);
}

void Server::OnConnection(const hv::SocketChannelPtr& chn) {
  LOGI("client %s %s", chn->peeraddr().c_str(), chn->isConnected() ? "connected" : "disconnected");
}

void Server::OnMessage(const hv::SocketChannelPtr& chn, hv::Buffer* buf) {
  LOGI(
      "recv a message from %s, len=%llu",
      chn->peeraddr().c_str(), buf->size() - constants::kUnpackSetting.body_offset
  );

  const auto resp = logic::HandleRequest(buf);
  Server::Write(chn, resp);
}
