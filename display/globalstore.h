#pragma once

class HttpClient;

class GlobalStore final : public QObject {
  Q_OBJECT

 public:
  struct Student {
    QString name;
    int     id{};

    [[nodiscard]] auto GetDisplayStr() const {
      return QString::asprintf("%02d%s", id, name.toStdString().c_str());
    }
  };

  struct Event {
    QString title;
    QDate   date;
    bool    important{};
  };

  struct Notice {
    QString title;
    QDate   date;
    QString text;
    bool    last_forever{};
  };

  struct Lesson {
    QString lessons[5];
    QTime   start_tm;
    QTime   end_tm;
  };

  struct BasicArrangement {
    QString job;
  };

  struct RolledArrangement : BasicArrangement {
    int   start_idx{};
    QDate start_date;
    int   days_one_step{};
    int   students_one_step{};
  };

  struct CompleteArrangement : RolledArrangement {};

  struct PartialArrangement : RolledArrangement {
    QList<Student> students;
  };

  struct WeekdayArrangement : BasicArrangement {
    QList<Student> students[5];
  };

  struct Sentence {
    QString text;
    QString author;
  };

  struct ClassInfo {
    QString class_name;

    QList<Student> students;
    QList<Event>   events;
    QList<Notice>  notices;
    QList<Lesson>  lessons;

    QList<CompleteArrangement> complete_arr;
    QList<PartialArrangement>  partial_arr;
    QList<WeekdayArrangement>  weekday_arr;

    QList<Sentence> sentences;
  };

  static GlobalStore *Get() {
    static GlobalStore store;
    return &store;
  }

  [[nodiscard]] static auto GetClassInfo() { return Get()->class_info_; }

  ~GlobalStore() final;

 public slots:
  void Start();

 signals:
  void SucceededHandleResp();
  void FailedHandleResp(const QString &error_msg);

 private:
  explicit GlobalStore();

  std::unique_ptr<HttpClient> cli_;
  int                         class_id_;
  ClassInfo                   class_info_;

 private slots:
  void HandleResponse(const QString &resp);
};
