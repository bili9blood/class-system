#include <sqlite_orm/sqlite_orm.h>

#include "util.h"

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
  std::string start_tm;
  std::string end_tm;
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

  std::string mon_student_ids;  // 逗号分隔
  std::string tue_student_ids;  // 逗号分隔
  std::string wed_student_ids;  // 逗号分隔
  std::string thu_student_ids;  // 逗号分隔
  std::string fri_student_ids;  // 逗号分隔
};

struct Sentence {
  int         sentence_id;
  std::string text;
  std::string author;
};

}  // namespace type

// NOLINTNEXTLINE
inline auto db = sqlite_orm::make_storage(
    util::GetBasePath() + "/class-system-server.db",

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
        _D::make_column("name", &type::Student::name, _D::primary_key()),
        _D::foreign_key(&type::Student::class_id).references(&type::Class::class_id)
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
        "weekly_lessons",
        _D::make_column("lesson_id", &type::WeeklyLesson::lesson_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::WeeklyLesson::class_id),
        _D::make_column("lesson_number", &type::WeeklyLesson::lesson_number),
        _D::make_column("mon", &type::WeeklyLesson::mon),
        _D::make_column("tue", &type::WeeklyLesson::tue),
        _D::make_column("wed", &type::WeeklyLesson::wed),
        _D::make_column("thu", &type::WeeklyLesson::thu),
        _D::make_column("fri", &type::WeeklyLesson::fri),
        _D::make_column("start_tm", &type::WeeklyLesson::start_tm),
        _D::make_column("end_tm", &type::WeeklyLesson::end_tm),
        _D::foreign_key(&type::WeeklyLesson::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "notices",
        _D::make_column("notice_id", &type::Notice::notice_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::Notice::class_id),
        _D::make_column("title", &type::Notice::title),
        _D::make_column("text", &type::Notice::text),
        _D::make_column("date", &type::Notice::date),
        _D::foreign_key(&type::Notice::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "events",
        _D::make_column("event_id", &type::Event::event_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::Event::class_id),
        _D::make_column("title", &type::Event::title),
        _D::make_column("date", &type::Event::date),
        _D::make_column("important", &type::Event::important),
        _D::foreign_key(&type::Event::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "partialarrs",
        _D::make_column("partialarr_id", &type::PartialArrangement::partialarr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::PartialArrangement::class_id),
        _D::make_column("job", &type::PartialArrangement::job),
        _D::make_column("start_idx", &type::PartialArrangement::start_idx),
        _D::make_column("start_date", &type::PartialArrangement::start_date),
        _D::make_column("days_one_step", &type::PartialArrangement::days_one_step),
        _D::make_column("students_one_step", &type::PartialArrangement::students_one_step),
        _D::make_column("student_ids", &type::PartialArrangement::student_ids),
        _D::foreign_key(&type::PartialArrangement::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "completearrs",
        _D::make_column("completearr_id", &type::CompleteArrangement::completearr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::CompleteArrangement::class_id),
        _D::make_column("job", &type::CompleteArrangement::job),
        _D::make_column("start_idx", &type::CompleteArrangement::start_idx),
        _D::make_column("start_date", &type::CompleteArrangement::start_date),
        _D::make_column("days_one_step", &type::CompleteArrangement::days_one_step),
        _D::make_column("students_one_step", &type::CompleteArrangement::students_one_step),
        _D::foreign_key(&type::CompleteArrangement::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "weekdayarrs",
        _D::make_column("weekdayarr_id", &type::WeekdayArrangement::weekdayarr_id, _D::primary_key().autoincrement()),
        _D::make_column("class_id", &type::WeekdayArrangement::class_id),
        _D::make_column("job", &type::WeekdayArrangement::job),
        _D::make_column("mon_student_ids", &type::WeekdayArrangement::mon_student_ids),
        _D::make_column("tue_student_ids", &type::WeekdayArrangement::tue_student_ids),
        _D::make_column("wed_student_ids", &type::WeekdayArrangement::wed_student_ids),
        _D::make_column("thu_student_ids", &type::WeekdayArrangement::thu_student_ids),
        _D::make_column("fri_student_ids", &type::WeekdayArrangement::fri_student_ids),
        _D::foreign_key(&type::WeekdayArrangement::class_id).references(&type::Class::class_id)
    ),
    _D::make_table(
        "sentences",
        _D::make_column("sentence_id", &type::Sentence::sentence_id, _D::primary_key().autoincrement()),
        _D::make_column("text", &type::Sentence::text, _D::unique()),
        _D::make_column("author", &type::Sentence::author)
    )
);

namespace _D {

class _Storage_RAII {
 public:
  _Storage_RAII() {
    db.sync_schema();
  }
  // NOLINTNEXTLINE
} static __storage_raii;

}  // namespace _D

}  // namespace storage
