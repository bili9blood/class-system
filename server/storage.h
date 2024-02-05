#include <sqlite_orm/sqlite_orm.h>

namespace storage {

namespace _D {
using namespace sqlite_orm;
}  // namespace _D

namespace type {

struct Student {
  int         student_id;
  int         class_id;
  std::string name;
};

struct Class {
  int         class_id;
  std::string name;
  std::string key;
};

struct WeeklyLesson {
  int         lesson_id;
  int         class_id;
  int         lesson_number;  // 每天的第几节课
  std::string mon;
  std::string tue;
  std::string wed;
  std::string thu;
  std::string fri;
};

struct Notice {
  int         notice_id;
  int         class_id;
  std::string title;
  std::string text;
  std::string date;
};

struct Event {
  int         event_id;
  int         class_id;
  std::string title;
  std::string date;
  bool        important;
};

struct PartialArrangement {
  int         partialarr_id;
  int         class_id;

  std::string job;

  int         start_idx;
  std::string start_date;
  int         days_one_step;
  int         students_one_step;

  std::string student_ids;  // 逗号分隔
};

struct CompleteArrangement {
  int         completearr_id;
  int         class_id;

  std::string job;

  int         start_idx;
  std::string start_date;
  int         days_one_step;
  int         students_one_step;
};

struct WeekdayArrangement {
  int         weekdayarr_id;
  int         class_id;

  std::string job;

  std::string mon_students_id;  // 逗号分隔
  std::string tue_students_id;  // 逗号分隔
  std::string wed_students_id;  // 逗号分隔
  std::string thu_students_id;  // 逗号分隔
  std::string fri_students_id;  // 逗号分隔
};

}  // namespace type

// NOLINTNEXTLINE
inline auto storage = sqlite_orm::make_storage(
    "class_system-server.db",

    _D::make_index("idx_student_class_id", &type::Student::class_id),
    _D::make_index("idx_lesson_class_id", &type::WeeklyLesson::class_id),
    _D::make_index("idx_notice_class_id", &type::Notice::class_id),
    _D::make_index("idx_event_class_id", &type::Event::class_id),
    _D::make_index("idx_partialarr_class_id", &type::PartialArrangement::class_id),
    _D::make_index("idx_completearr_class_id", &type::CompleteArrangement::class_id),
    _D::make_index("idx_weekdayarr_class_id", &type::WeekdayArrangement::class_id),

    _D::make_table(
        "students",
        _D::make_column("student_id", &type::Student::student_id),
        _D::make_column("class_id", &type::Student::class_id),
        _D::make_column("name", &type::Student::name, _D::primary_key())
    ),
    _D::make_table(
        "classes",
        _D::make_column(
            "class_id", &type::Class::class_id,
            _D::primary_key().autoincrement()
        ),
        _D::make_column("name", &type::Class::name, sqlite_orm::unique()),
        _D::make_column("key", &type::Class::key, sqlite_orm::unique())
    ),
    _D::make_table(
        "weekly_lesson",
        _D::make_column("lesson_id", &type::WeeklyLesson::lesson_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::WeeklyLesson::class_id),
        _D::make_column("mon", &type::WeeklyLesson::mon),
        _D::make_column("tue", &type::WeeklyLesson::tue),
        _D::make_column("wed", &type::WeeklyLesson::wed),
        _D::make_column("thu", &type::WeeklyLesson::thu),
        _D::make_column("fri", &type::WeeklyLesson::fri)
    ),
    _D::make_table(
        "notice",
        _D::make_column("notice_id", &type::Notice::notice_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::Notice::class_id),
        _D::make_column("title", &type::Notice::title),
        _D::make_column("text", &type::Notice::text),
        _D::make_column("date", &type::Notice::date)
    ),
    _D::make_table(
        "event",
        _D::make_column("event_id", &type::Event::event_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::Event::class_id),
        _D::make_column("title", &type::Event::title),
        _D::make_column("date", &type::Event::date),
        _D::make_column("important", &type::Event::important)
    ),
    _D::make_table(
        "partialarr",
        _D::make_column("partialarr_id", &type::PartialArrangement::partialarr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::PartialArrangement::class_id),
        _D::make_column("job", &type::PartialArrangement::job),
        _D::make_column("start_idx", &type::PartialArrangement::start_idx),
        _D::make_column("start_date", &type::PartialArrangement::start_date),
        _D::make_column("days_one_step", &type::PartialArrangement::days_one_step),
        _D::make_column("students_one_step", &type::PartialArrangement::students_one_step),
        _D::make_column("student_ids", &type::PartialArrangement::student_ids)
    ),
    _D::make_table(
        "completearr",
        _D::make_column("completearr_id", &type::CompleteArrangement::completearr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::CompleteArrangement::class_id),
        _D::make_column("job", &type::CompleteArrangement::job),
        _D::make_column("start_idx", &type::CompleteArrangement::start_idx),
        _D::make_column("start_date", &type::CompleteArrangement::start_date),
        _D::make_column("days_one_step", &type::CompleteArrangement::days_one_step),
        _D::make_column("students_one_step", &type::CompleteArrangement::students_one_step)
    ),
    _D::make_table(
        "weekdayarr",
        _D::make_column("weekdayarr_id", &type::WeekdayArrangement::weekdayarr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::WeekdayArrangement::class_id),
        _D::make_column("job", &type::WeekdayArrangement::job),
        _D::make_column("mon_students_id", &type::WeekdayArrangement::mon_students_id),
        _D::make_column("tue_students_id", &type::WeekdayArrangement::tue_students_id),
        _D::make_column("wed_students_id", &type::WeekdayArrangement::wed_students_id),
        _D::make_column("thu_students_id", &type::WeekdayArrangement::thu_students_id),
        _D::make_column("fri_students_id", &type::WeekdayArrangement::fri_students_id)
    )
);

namespace _D {

class _Storage_RAII {
 public:
  _Storage_RAII() {
    storage.sync_schema();
  }
  // NOLINTNEXTLINE
} static __storage_raii;

}  // namespace _D

}  // namespace storage
