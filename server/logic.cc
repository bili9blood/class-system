#include "logic.h"

#include <proto/Request.pb.h>
#include <proto/Response.pb.h>

#include "storage.h"
#include "util.h"

/**
 * @brief Create a Response protobuf message from `msg`
 *
 * @param msg a string error message
 * @return class_system::Response the created protobuf message
 */
static class_system::Response CreateErrorResp(const std::string& msg) {
  class_system::Response resp;
  resp.set_error_msg(msg);
  return resp;
}

/**
 * @brief fetch ClassInfo from storage and return
 *
 * @param class_id class_id
 * @param daily_arrangement whether to calculate DailyArrangement
 * @return class_system::ClassInfo ClassInfo protobuf message
 */
static class_system::ClassInfo FetchClassInfo(const int& class_id, const bool& daily_arrangement) {
  auto class_info = class_system::ClassInfo{};

  // TODO: fetch class info from storage
  return class_info;
}

namespace logic {

hv::BufferPtr HandleRequest(hv::Buffer* req) {
  class_system::Request request;
  if (!request.ParseFromArray((char*)req->data() + 4, (int)req->size() - 4)) {
    return util::MessageToBuf(CreateErrorResp("parse request failed"));
  }

  const auto input_key = request.key();
  const auto keys      = storage::db.select(
      sqlite_orm::columns(&storage::type::Class::class_id, &storage::type::Class::key)
  );

  auto class_id = std::optional<int>{};

  for (const auto& [id, key] : keys) {
    if (key == input_key) {
      class_id = id;
      break;
    }
  }

  if (!class_id.has_value()) {
    return util::MessageToBuf(CreateErrorResp("invaild key"));
  }

  auto resp = class_system::Response{};

  if (request.request_class_info()) {
    resp.mutable_class_info()->CopyFrom(
        FetchClassInfo(class_id.value(), request.request_daily_arrangement())
    );
  }

  // TODO: sentences and daily weather

  return util::MessageToBuf(resp);
}

}  // namespace logic
