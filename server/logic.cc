#include "logic.h"

#include <hv/hlog.h>
#include <proto/Request.pb.h>
#include <proto/Response.pb.h>
#include <shared/util.h>

#include "storage.h"

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
static class_system::ClassInfo* FetchClassInfo(const int& class_id, const bool& daily_arrangement) {
  using namespace sqlite_orm;
  using namespace storage::type;

  auto* class_info = new class_system::ClassInfo{};
  try {
    /* ---------------------------------------------------------------- */
    /*                            Fetch Name                            */
    /* ---------------------------------------------------------------- */

    {
      auto       name    = std::string{};
      const auto fetched = storage::db.select(
          columns(&Class::name),
          where(c(&Class::class_id) == class_id)
      );
      if (!fetched.empty()) name = std::get<0>(fetched[0]);
      class_info->set_name(name);
    }

    /* ---------------------------------------------------------------- */
    /*                          Fetch Students                          */
    /* ---------------------------------------------------------------- */

    {
      auto       students = google::protobuf::RepeatedPtrField<class_system::ClassInfo::Student>{};
      const auto fetched = storage::db.select(
          columns(&Student::student_id, &Student::name),
          where(c(&Student::class_id) == class_id),
          order_by(&Student::student_id)
      );
      for (const auto& [id, name] : fetched) {
        auto* const it = students.Add();
        it->set_id(id);
        it->set_name(name);
      }
    class_info->mutable_students()->Swap(&students);
    }

    /* ---------------------------------------------------------------- */
    /*                           Fetch Lessons                          */
    /* ---------------------------------------------------------------- */

    {
      auto       lessons = google::protobuf::RepeatedPtrField<class_system::ClassInfo::WeeklyLessons>{};
      const auto fetched = storage::db.select(
          columns(
              &WeeklyLesson::mon, &WeeklyLesson::tue, &WeeklyLesson::wed, &WeeklyLesson::thu, &WeeklyLesson::fri,
              &WeeklyLesson::start_tm, &WeeklyLesson::end_tm
          ),
          where(c(&WeeklyLesson::class_id) == class_id),
          order_by(&WeeklyLesson::lesson_number)
      );
      for (const auto& l : fetched) {
        auto* const it = lessons.Add();
        it->set_mon(std::get<0>(l));
        it->set_tue(std::get<1>(l));
        it->set_wed(std::get<2>(l));
        it->set_thu(std::get<3>(l));
        it->set_fri(std::get<4>(l));
        it->set_start_tm(std::get<5>(l));
        it->set_end_tm(std::get<6>(l));
      }
    class_info->mutable_lessons()->Swap(&lessons);
    }

    // TODO: Fetch WeekdayArrangement

    // TODO: Fetch PartialArrangemant

    // TODO: Fetch CompleteArrangement

    // TODO: Fetch Notices

    // TODO: Fetch Events

    // TODO: Calc DailyArrangement

  } catch (const std::exception& e) {
    LOGE("Failed to fetch class info: %s", e.what());
    return {};
  }
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
    auto* const fetched = FetchClassInfo(class_id.value(), request.request_daily_arrangement());
    if (fetched)
      resp.mutable_class_info()->Swap(fetched);
    else
      return util::MessageToBuf(CreateErrorResp("fetch class info failed"));
  }

  // TODO: sentences and daily weather

  return util::MessageToBuf(resp);
}

}  // namespace logic
