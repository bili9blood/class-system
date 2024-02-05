#include <sqlite_orm/sqlite_orm.h>
using  //
    sqlite_orm::make_table,
    sqlite_orm::make_column,
    sqlite_orm::make_index,
    sqlite_orm::primary_key;

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

// NOLINTNEXTLINE
inline auto storage = sqlite_orm::make_storage(
    "class_system.db",

    make_index("idx_student_class_id", &Student::class_id),
    make_index("idx_lesson_class_id", &WeeklyLesson::class_id),
    make_index("idx_notice_class_id", &Notice::class_id),
    make_index("idx_event_class_id", &Event::class_id),
    make_index("idx_partialarr_class_id", &PartialArrangement::class_id),
    make_index("idx_completearr_class_id", &CompleteArrangement::class_id),
    make_index("idx_weekdayarr_class_id", &WeekdayArrangement::class_id),

    make_table(
        "students",
        make_column("student_id", &Student::student_id),
        make_column("class_id", &Student::class_id),
        make_column("name", &Student::name, primary_key())
    ),
    make_table(
        "classes",
        make_column(
            "class_id", &Class::class_id,
            primary_key().autoincrement()
        ),
        make_column("name", &Class::name, sqlite_orm::unique()),
        make_column("key", &Class::key, sqlite_orm::unique())
    ),
    make_table(
        "weekly_lesson",
        make_column("lesson_id", &WeeklyLesson::lesson_id, primary_key().autoincrement()),
        make_column("class_id", &WeeklyLesson::class_id),
        make_column("mon", &WeeklyLesson::mon),
        make_column("tue", &WeeklyLesson::tue),
        make_column("wed", &WeeklyLesson::wed),
        make_column("thu", &WeeklyLesson::thu),
        make_column("fri", &WeeklyLesson::fri)
    ),
    make_table(
        "notice",
        make_column("notice_id", &Notice::notice_id, primary_key().autoincrement()),
        make_column("class_id", &Notice::class_id),
        make_column("title", &Notice::title),
        make_column("text", &Notice::text),
        make_column("date", &Notice::date)
    ),
    make_table(
        "event",
        make_column("event_id", &Event::event_id, primary_key().autoincrement()),
        make_column("class_id", &Event::class_id),
        make_column("title", &Event::title),
        make_column("date", &Event::date),
        make_column("important", &Event::important)
    ),
    make_table(
        "partialarr",
        make_column("partialarr_id", &PartialArrangement::partialarr_id, primary_key().autoincrement()),
        make_column("class_id", &PartialArrangement::class_id),
        make_column("job", &PartialArrangement::job),
        make_column("start_idx", &PartialArrangement::start_idx),
        make_column("start_date", &PartialArrangement::start_date),
        make_column("days_one_step", &PartialArrangement::days_one_step),
        make_column("students_one_step", &PartialArrangement::students_one_step),
        make_column("student_ids", &PartialArrangement::student_ids)
    ),
    make_table(
        "completearr",
        make_column("completearr_id", &CompleteArrangement::completearr_id, primary_key().autoincrement()),
        make_column("class_id", &CompleteArrangement::class_id),
        make_column("job", &CompleteArrangement::job),
        make_column("start_idx", &CompleteArrangement::start_idx),
        make_column("start_date", &CompleteArrangement::start_date),
        make_column("days_one_step", &CompleteArrangement::days_one_step),
        make_column("students_one_step", &CompleteArrangement::students_one_step)
    ),
    make_table(
        "weekdayarr",
        make_column("weekdayarr_id", &WeekdayArrangement::weekdayarr_id, primary_key().autoincrement()),
        make_column("class_id", &WeekdayArrangement::class_id),
        make_column("job", &WeekdayArrangement::job),
        make_column("mon_students_id", &WeekdayArrangement::mon_students_id),
        make_column("tue_students_id", &WeekdayArrangement::tue_students_id),
        make_column("wed_students_id", &WeekdayArrangement::wed_students_id),
        make_column("thu_students_id", &WeekdayArrangement::thu_students_id),
        make_column("fri_students_id", &WeekdayArrangement::fri_students_id)
    )
);

class _Storage_RAII {
 public:
  _Storage_RAII() {
    storage.sync_schema();
  }
  // NOLINTNEXTLINE
} static __storage_raii;
