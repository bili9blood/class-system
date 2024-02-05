#include "logic.h"

#include <proto/Request.pb.h>
#include <proto/Response.pb.h>

#include "util.h"

static class_system::Response CreateErrorResp(const std::string& msg) {
  class_system::Response resp;
  resp.set_error_msg(msg);
  return resp;
}

namespace logic {

hv::BufferPtr HandleRequest(hv::Buffer* req) {
  class_system::Request request;
  if (!request.ParseFromArray((char*)req->data() + 4, (int)req->size() - 4)) {
    return util::MessageToBuf(CreateErrorResp("parse request failed"));
  }

  // TODO: logic
  return util::MessageToBuf(class_system::Response());
}

}  // namespace logic
