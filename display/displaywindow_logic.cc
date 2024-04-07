#include <qdatetime.h>
#include <qlayoutitem.h>
#include <qrandom.h>
#include <qstyle.h>

#include <nlohmann/json.hpp>

#include "config.h"
#include "constants/constants.h"
#include "displaywindow.h"
#include "eventnodewidget.h"
#include "flowlayout.h"
#include "httpclient.h"
#include "ui_displaywindow.h"
#include "weatherwidget.h"

#ifdef min
#undef min
#endif

static void ClearLayout(QLayout *layout) {
  while (layout->count()) {
    auto *item = layout->takeAt(0);
    if (!item) break;

    if (auto *child = item->widget()) {
      child->setParent(nullptr);
      child->deleteLater();
    }
    if (auto *child = item->layout()) {
      ClearLayout(child);
      child->deleteLater();
    }

    delete item;
  }
}

void DisplayWindow::InitSentences(const QList<GlobalStore::Sentence> &sentences) {
  if (sentences.empty()) return;

  // simply make the first sentence different every time
  const auto idx = QRandomGenerator::global()->bounded(sentences.size());
  for (auto i{idx}; i < sentences.size(); ++i) sentences_.push(sentences[i]);
  for (auto i{0}; i < idx; ++i) sentences_.push(sentences[i]);
}

QList<DisplayWindow::DailyArrangement> DisplayWindow::GetDailyArrangement() {
  static const auto FromPartial =
      [](const GlobalStore::PartialArrangement &arr) -> DisplayWindow::DailyArrangement {
    const auto days_since_start = (int)arr.start_date.daysTo(QDate::currentDate());
    const auto cur_idx =
        ((days_since_start / arr.days_one_step) * arr.students_one_step + arr.start_idx) %
        arr.students.size();
    QList<GlobalStore::Student> students_today;
    for (auto i{0}; i < arr.students_one_step; ++i)
      students_today.push_back(arr.students[(cur_idx + i) % arr.students.size()]);
    return {arr.job, students_today};
  };

  static const auto FromComplete =
      [this](const GlobalStore::CompleteArrangement &arr) -> DisplayWindow::DailyArrangement {
    GlobalStore::PartialArrangement partial;
    partial.job               = arr.job;
    partial.start_date        = arr.start_date;
    partial.start_idx         = arr.start_idx;
    partial.students_one_step = arr.students_one_step;
    partial.days_one_step     = arr.days_one_step;
    partial.students          = GlobalStore::GetClassInfo().students;
    return FromPartial(partial);
  };

  static const auto FromWeekday =
      [](const GlobalStore::WeekdayArrangement &arr) -> DisplayWindow::DailyArrangement {
    return {arr.job, arr.students[(QDate::currentDate().dayOfWeek() - 1) % 5]};
  };

  QList<DisplayWindow::DailyArrangement> res_list;
  for (const auto &arr : GlobalStore::GetClassInfo().partial_arr) res_list << FromPartial(arr);
  for (const auto &arr : GlobalStore::GetClassInfo().complete_arr) res_list << FromComplete(arr);
  for (const auto &arr : GlobalStore::GetClassInfo().weekday_arr) res_list << FromWeekday(arr);
  return res_list;
}

void DisplayWindow::DisplayEvents() {
  ClearLayout(ui_->events_widget->layout());
  for (auto i{0}; i < std::min(4, GlobalStore::GetClassInfo().events.size()); ++i) {
    auto *const event_widget = new EventNodeWidget{GlobalStore::GetClassInfo().events[i], ui_->events_widget};
    ui_->events_widget->layout()->addWidget(event_widget);
  }
}

void DisplayWindow::DisplayArrangement() {
  ClearLayout(ui_->arrangement_layout);

  const auto daily_arrangement = GetDailyArrangement();

  // add new arrangement labels & layouts
  for (const auto &arr : daily_arrangement) {
    auto *const title_label = new QLabel(arr.job, ui_->arrangement_widget);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setProperty("class", "title");

    auto *flow_layout = new FlowLayout{};
    for (const auto &student : arr.students) {
      auto *const stu_label = new QLabel{student.GetDisplayStr(), ui_->arrangement_widget};
      stu_label->setAlignment(Qt::AlignCenter);
      flow_layout->addWidget(stu_label);
    }
    ui_->arrangement_layout->addRow(title_label, flow_layout);
    auto *const spacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    ui_->arrangement_layout->addItem(spacer);
  }
}

void DisplayWindow::DisplayLessons() {
  ClearLayout(ui_->lessons_layout);

  // add new lesson labels
  for (const auto &l : GlobalStore::GetClassInfo().lessons) {
    const auto lesson_today = l.lessons[(QDate::currentDate().dayOfWeek() - 1) % 5];

    auto *const lbl = new QLabel{
        QString{constants::kLessonFormat}
            .arg(lesson_today)
            .arg(l.start_tm.toString("HH:mm"))
            .arg(l.end_tm.toString("HH:mm")),
        ui_->lessons_widget
    };
    ui_->lessons_layout->addWidget(lbl);
  }
}

void DisplayWindow::DisplayWeather() {
  ClearLayout(ui_->weather_layout);

  const auto *const key      = config::Get()["QWeather"]["key"].value_or("");
  const auto *const location = config::Get()["QWeather"]["location"].value_or("");

  QString    res;
  QEventLoop loop;

  HttpClient cli{QString{constants::kQweatherApiUrl}.arg(key).arg(location)};
  cli.success([&](const auto &_res) {
    res = _res;
    loop.quit();
  });
  cli.get();

  loop.exec();

  const auto res_json = nlohmann::json::parse(res.toUtf8().data());

  try {
    for (auto i{0}; i < (int)res_json["daily"].size(); ++i) {
      auto *const wgt = new WeatherWidget{
          std::stoi((std::string)res_json["daily"][i]["iconDay"]),
          std::stoi((std::string)res_json["daily"][i]["tempMin"]),
          std::stoi((std::string)res_json["daily"][i]["tempMax"]),

          QDate::currentDate().addDays(i),
          centralWidget()
      };
      ui_->weather_layout->addWidget(wgt);
    }
  } catch (const nlohmann::json::exception &e) {
    return;
  }
}

void DisplayWindow::UpdateLessonsStatus() {
  auto lbls = ui_->lessons_widget->findChildren<QLabel *>();
  if (lbls.size() != GlobalStore::GetClassInfo().lessons.size()) return;
  const auto lessons_cnt = lbls.size();
  const auto cur_time    = QTime::currentTime();

  for (auto i{0}; i < lessons_cnt; ++i) {
    auto &lbl = lbls[i];
    if (
        (i > 0 && cur_time >= GlobalStore::GetClassInfo().lessons[i - 1].end_tm &&
         cur_time < GlobalStore::GetClassInfo().lessons[i].end_tm) ||
        (i == 0 && cur_time < GlobalStore::GetClassInfo().lessons[i].end_tm)
    )
      lbl->setProperty("class", "current");
    else if (cur_time > GlobalStore::GetClassInfo().lessons[i].start_tm)
      lbl->setProperty("class", "past");
    else
      lbl->setProperty("class", "");
    lbl->style()->unpolish(lbl);
    lbl->style()->polish(lbl);
  }
}

void DisplayWindow::UpdateWindowStatus() {
  static QPoint old_pos;

  const auto during_lesson = std::any_of(
      GlobalStore::GetClassInfo().lessons.cbegin(), GlobalStore::GetClassInfo().lessons.cend(),
      [](const auto &l) {
        const auto cur_time = QTime::currentTime();
        return cur_time >= l.start_tm && cur_time < l.end_tm;
      }
  );
  if (is_layer_front_ && during_lesson) {
    old_pos = pos();
    MoveCenter();
    setWindowOpacity(0.85);
    is_layer_front_ = false;
  } else if (!is_layer_front_ && !during_lesson) {
    move(old_pos);
    setWindowOpacity(1.0);
    is_layer_front_ = true;
  }
}

void DisplayWindow::HandleClassInfo() {
  InitSentences(GlobalStore::GetClassInfo().sentences);
  DisplayEvents();
  DisplayArrangement();

  HandleSwitchSentences();
  HandleSwitchNotices();
  sentences_notices_switch_timer_.start();

  DisplayLessons();

  is_layer_front_ = true;
  show();
}

void DisplayWindow::HandleClockTick() {
  ui_->time_label->setText(QTime::currentTime().toString(constants::kTimeFormat));
  ui_->date_weekday_label->setText(QDate::currentDate().toString(constants::kDateWeekdayFormat));

  UpdateLessonsStatus();
  UpdateWindowStatus();
}

void DisplayWindow::HandleSwitchSentences() {
  if (sentences_.empty()) return;

  const auto cur_sentence = sentences_.front();
  sentences_.pop();

  ui_->sentence_text_label->setText(cur_sentence.text);
  ui_->sentence_author_label->setText(
      QString{constants::kSentenceAuthorFormat}
          .arg(cur_sentence.author)
  );

  sentences_.push(cur_sentence);
}

void DisplayWindow::HandleSwitchNotices() {
  if (GlobalStore::GetClassInfo().notices.empty()) {
    ui_->notices_data_title_label->setText("无公告");
    ui_->notices_date_label->setText("");
    ui_->notices_text_browser->setText("");
    return;
  }

  static int cur_notice_index{};
  if (cur_notice_index >= GlobalStore::GetClassInfo().notices.size()) cur_notice_index = 0;
  const auto cur_notice = GlobalStore::GetClassInfo().notices[cur_notice_index];
  ui_->notices_data_title_label->setText(cur_notice.title);
  ui_->notices_text_browser->setText(cur_notice.text);
  const auto date_str = cur_notice.last_forever ? "" : cur_notice.date.toString(constants::kNoticeDateFormat);
  ui_->notices_date_label->setText(date_str);

  ++cur_notice_index;
}
