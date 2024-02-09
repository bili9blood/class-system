#include "server.h"

#include <hv/hlog.h>
#include <shared/constants.h>

#include "logic.h"

Server::Server(unsigned short _port, int thread_num) {
  port = _port;

  setUnpack(&const_cast<unpack_setting_t&>(constants::kUnpackSetting));
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

// NOLINTNEXTLINE
void Server::OnConnection(const hv::SocketChannelPtr& chn) const {
  LOGI("client %s %s", chn->peeraddr().c_str(), chn->isConnected() ? "connected" : "disconnected");
}

// NOLINTNEXTLINE
void Server::OnMessage(const hv::SocketChannelPtr& chn, hv::Buffer* buf) const {
  LOGI(
      "recv a message from %s, len=%llu",
      chn->peeraddr().c_str(), buf->size() - constants::kUnpackSetting.body_offset
  );

  const auto resp = logic::HandleRequest(buf);
  chn->write(resp.get());
}
