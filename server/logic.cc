#include "logic.h"

#include <hv/hlog.h>
#include <hv/hstring.h>
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

static void FetchClassInfo(const int& class_id, class_system::ClassInfo* class_info) {
  using namespace sqlite_orm;
  using namespace storage::type;

  try {
    /* ---------------------------------------------------------------- */
    /*                            Fetch Name                            */
    /* ---------------------------------------------------------------- */
    {
      auto* const name    = class_info->mutable_name();
      const auto fetched = storage::db.select(
          columns(&Class::name),
          where(c(&Class::class_id) == class_id)
      );
      if (!fetched.empty()) *name = std::get<0>(fetched[0]);
    }

    /* ---------------------------------------------------------------- */
    /*                          Fetch Students                          */
    /* ---------------------------------------------------------------- */
    {
      auto* const students = class_info->mutable_students();
      const auto fetched = storage::db.select(
          columns(&Student::student_id, &Student::name),
          where(c(&Student::class_id) == class_id),
          order_by(&Student::student_id)
      );
      for (const auto& [id, name] : fetched) {
        auto* const it = students->Add();
        it->set_id(id);
        it->set_name(name);
      }
    }

    /* ---------------------------------------------------------------- */
    /*                           Fetch Lessons                          */
    /* ---------------------------------------------------------------- */
    {
      auto* const lessons = class_info->mutable_lessons();
      const auto fetched = storage::db.select(
          columns(
              &WeeklyLesson::mon, &WeeklyLesson::tue, &WeeklyLesson::wed, &WeeklyLesson::thu, &WeeklyLesson::fri,
              &WeeklyLesson::start_tm, &WeeklyLesson::end_tm
          ),
          where(c(&WeeklyLesson::class_id) == class_id),
          order_by(&WeeklyLesson::lesson_number)
      );
      for (const auto& l : fetched) {
        auto* const it = lessons->Add();
        it->set_mon(std::get<0>(l));
        it->set_tue(std::get<1>(l));
        it->set_wed(std::get<2>(l));
        it->set_thu(std::get<3>(l));
        it->set_fri(std::get<4>(l));
        it->set_start_tm(std::get<5>(l));
        it->set_end_tm(std::get<6>(l));
      }
    }

    /* ---------------------------------------------------------------- */
    /*                     Fetch WeekdayArrangement                     */
    /* ---------------------------------------------------------------- */
    auto* const weekday_arrangements = class_info->mutable_weekday_arrangements();
    {
      const auto fetched = storage::db.select(
          columns(
              &WeekdayArrangement::mon_student_ids, &WeekdayArrangement::tue_student_ids,
              &WeekdayArrangement::wed_student_ids, &WeekdayArrangement::thu_student_ids,
              &WeekdayArrangement::fri_student_ids, &WeekdayArrangement::job
          ),
          where(c(&WeekdayArrangement::class_id) == class_id)
      );
      for (const auto& a : fetched) {
        auto* const it = weekday_arrangements->Add();
        util::SplitIdsFromStr(std::get<0>(a), it->mutable_mon_student_ids());
        util::SplitIdsFromStr(std::get<1>(a), it->mutable_tue_student_ids());
        util::SplitIdsFromStr(std::get<2>(a), it->mutable_wed_student_ids());
        util::SplitIdsFromStr(std::get<3>(a), it->mutable_thu_student_ids());
        util::SplitIdsFromStr(std::get<4>(a), it->mutable_fri_student_ids());
        it->set_job(std::get<5>(a));
      }
    }

    /* ---------------------------------------------------------------- */
    /*                     Fetch PartialArrangemant                     */
    /* ---------------------------------------------------------------- */
    auto* const partial_arrangements = class_info->mutable_partial_arrangements();
    {
      const auto fetched = storage::db.select(
          columns(
              &PartialArrangement::job, &PartialArrangement::student_ids,
              &PartialArrangement::start_idx, &PartialArrangement::start_date,
              &PartialArrangement::days_one_step, &PartialArrangement::students_one_step
          ),
          where(c(&PartialArrangement::class_id) == class_id)
      );
      for (const auto& a : fetched) {
        auto* const it = partial_arrangements->Add();
        it->set_job(std::get<0>(a));
        util::SplitIdsFromStr(std::get<1>(a), it->mutable_student_ids());
        it->mutable_opts()->set_start_idx(std::get<2>(a));
        it->mutable_opts()->set_start_date(std::get<3>(a));
        it->mutable_opts()->set_days_one_step(std::get<4>(a));
        it->mutable_opts()->set_students_one_step(std::get<5>(a));
      }
    }

    /* ---------------------------------------------------------------- */
    /*                     Fetch CompleteArrangement                    */
    /* ---------------------------------------------------------------- */
    auto* const complete_arrangements = class_info->mutable_complete_arrangements();
    {
      const auto fetched = storage::db.select(
          columns(
              &CompleteArrangement::job,
              &CompleteArrangement::start_idx, &CompleteArrangement::start_date,
              &CompleteArrangement::days_one_step, &CompleteArrangement::students_one_step
          ),
          where(c(&CompleteArrangement::class_id) == class_id)
      );
      for (const auto& a : fetched) {
        auto* const it = complete_arrangements->Add();
        it->set_job(std::get<0>(a));
        it->mutable_opts()->set_start_idx(std::get<1>(a));
        it->mutable_opts()->set_start_date(std::get<2>(a));
        it->mutable_opts()->set_days_one_step(std::get<3>(a));
        it->mutable_opts()->set_students_one_step(std::get<4>(a));
      }
    }

    /* ---------------------------------------------------------------- */
    /*                           Fetch Notices                          */
    /* ---------------------------------------------------------------- */
    {
      auto* const notices = class_info->mutable_notices();
      const auto  fetched = storage::db.select(
          columns(&Notice::title, &Notice::date, &Notice::text),
          where(c(&Notice::class_id) == class_id)
      );
      for (const auto& n : fetched) {
        auto* const it = notices->Add();
        it->set_title(std::get<0>(n));
        it->set_date(std::get<1>(n));
        it->set_text(std::get<2>(n));
      }
    }

    /* ---------------------------------------------------------------- */
    /*                           Fetch Events                           */
    /* ---------------------------------------------------------------- */
    {
      auto* const events  = class_info->mutable_events();
      const auto  fetched = storage::db.select(
          columns(&Event::title, &Event::date, &Event::important),
          where(c(&Event::class_id) == class_id)
      );
      for (const auto& e : fetched) {
        auto* const it = events->Add();
        it->set_title(std::get<0>(e));
        it->set_date(std::get<1>(e));
        it->set_important(std::get<2>(e));
      }
    }
  } catch (const std::exception& e) {
    LOGE("Failed to fetch class info: %s", e.what());
    throw e;
  }
}

static void FetchSentences(const int& class_id, google::protobuf::RepeatedPtrField<class_system::Sentence>* sentences) {
  try {
    const auto fetched = storage::db.select(
        sqlite_orm::columns(&storage::type::Sentence::text, &storage::type::Sentence::author)
    );
    for (const auto& s : fetched) {
      auto* const it = sentences->Add();
      it->set_text(std::get<0>(s));
      it->set_author(std::get<1>(s));
    }
  } catch (std::exception& e) {
    LOGE("Failed to fetch sentences: %s", e.what());
    throw e;
  }
}

static void CalcDailyArrangement(const int& class_id, class_system::ClassInfo* class_info) {
  // TODO: calc daily arrangement
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
    try {
      FetchClassInfo(class_id.value(), resp.mutable_class_info());
    } catch (const std::exception& e) {
      return util::MessageToBuf(CreateErrorResp(hv::asprintf("fetch class info failed: %s", e.what())));
    }
  }

  if (request.request_sentences()) {
    try {
      FetchSentences(class_id.value(), resp.mutable_sentences());
    } catch (const std::exception& e) {
      return util::MessageToBuf(CreateErrorResp(hv::asprintf("fetch sentences failed: %s", e.what())));
    }
  }

  if (request.request_daily_arrangement()) {
    CalcDailyArrangement(class_id.value(), resp.mutable_class_info());
  }

  return util::MessageToBuf(resp);
}

}  // namespace logic
