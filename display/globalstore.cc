#include "globalstore.h"

#include <nlohmann/json.hpp>

#include "config.h"
#include "constants/constants.h"
#include "httpclient.h"

static QDate Str2Date(std::string_view str) {
  return QDate::fromString(str.data(), constants::kTransferDateFormat);
}

static QTime Str2Time(std::string_view str) {
  return QTime::fromString(str.data(), constants::kTransferTimeFormat);
}

static GlobalStore::ClassInfo ParseFromJson(const QString &json_str) {
  auto json = nlohmann::json::parse(json_str.toStdString());
  if (json["code"] != 200) throw std::exception{"Code isn't 200!"};
  json = json["data"];
  GlobalStore::ClassInfo class_info;

  for (const auto &s : json["students"]) {
    class_info.students.push_back({
        s["name"].get<std::string>().c_str(),
        s["inclass_id"].get<int>(),
    });
  }

  for (const auto &e : json["events"]) {
    class_info.events.push_back({
        e["title"].get<std::string>().c_str(),
        Str2Date(e["date"].get<std::string>()),
        e["important"].get<bool>(),
    });
  }

  for (const auto &n : json["notice"]) {
    const auto last_forever{n["last_forever"].get<bool>()};
    const auto date = last_forever
                          ? QDate{}
                          : Str2Date(n["date"].get<std::string>());

    class_info.notices.push_back({
        n["title"].get<std::string>().c_str(),
        date,
        n["text"].get<std::string>().c_str(),
        last_forever,
    });
  }

  for (const auto &l : json["lessons"]) {
    GlobalStore::Lesson le;
    for (int i{}; i < 5; ++i)
      le.lessons[i] = l["lessons"][i].get<std::string>().c_str();
    le.start_tm = Str2Time(l["startTm"].get<std::string>());
    le.end_tm   = Str2Time(l["endTm"].get<std::string>());
    class_info.lessons.push_back(le);
  }

  for (const auto &a : json["complete_arr"]) {
    class_info.complete_arr.push_back({
        a["job"].get<std::string>().c_str(),
        a["start_idx"].get<int>(),
        Str2Date(a["start_date"].get<std::string>()),
        a["days_one_step"].get<int>(),
        a["students_one_step"].get<int>(),
    });
  }

  for (const auto &a : json["partial_arr"]) {
    QList<GlobalStore::Student> students;
    for (const auto &s : a["student_ids"])
      students.push_back(
          *std::find_if(class_info.students.begin(), class_info.students.end(), [&s](const auto &_s) { return _s.id == s; })
      );

    class_info.partial_arr.push_back({
        a["job"].get<std::string>().c_str(),
        a["start_idx"].get<int>(),
        Str2Date(a["start_date"].get<std::string>()),
        a["days_one_step"].get<int>(),
        a["students_one_step"].get<int>(),
        students,
    });
  }

  for (const auto &a : json["weekday_arr"]) {
    QList<GlobalStore::Student> students[5];
    for (int i{}; i < 5; ++i)
      for (const auto &s : a["student_ids"][i])
        students[i].push_back(
            *std::find_if(class_info.students.begin(), class_info.students.end(), [&s](const auto &_s) { return _s.id == s; })
        );

    class_info.weekday_arr.push_back({
        a["job"].get<std::string>().c_str(),
        students[0],
        students[1],
        students[2],
        students[3],
        students[4],
    });
  }

  for (const auto &s : json["sentences"]) {
    class_info.sentences.push_back({
        s["text"].get<std::string>().c_str(),
        s["author"].get<std::string>().c_str(),
    });
  }

  return class_info;
}

GlobalStore::GlobalStore() : QObject(nullptr) {}

GlobalStore::~GlobalStore() = default;

void GlobalStore::Start() {
  const QString        base_url{config::Get()["Server"]["url"].as_string()->get().c_str()};
  const auto           class_id{config::Get()["Server"]["class_id"].as_integer()->get()};
  const nlohmann::json body = {
      {"class_id", class_id},
      {"long", false}
  };

  HttpClient c{base_url + "/api/info/get"};
  c.json(body.dump().c_str())
      .success(std::bind(&GlobalStore::HandleResponse, this, std::placeholders::_1))
      .fail([](const auto &msg, const auto status) { qDebug() << msg << status; })
      .post();
}

void GlobalStore::HandleResponse(const QString &resp) {
  try {
    class_info_ = ParseFromJson(resp);
  } catch (const std::exception &e) {
    Q_EMIT FailedHandleResp(e.what());
    return;
  }
  Q_EMIT SucceededHandleResp();
}
