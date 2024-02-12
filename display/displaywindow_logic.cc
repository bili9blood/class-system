#include <qdatetime.h>
#include <qrandom.h>
#include <qstyle.h>
#include <shared/constants.h>
#include <shared/util.h>

#include "constants.h"
#include "displaywindow.h"
#include "flowlayout.h"
#include "ui_displaywindow.h"

#define GET_WEEKDAY_TODAY(x, c, d)              \
  [c] {                                         \
    switch (QDate::currentDate().dayOfWeek()) { \
      case Qt::Monday:                          \
        return x(mon);                          \
      case Qt::Tuesday:                         \
        return x(tue);                          \
      case Qt::Wednesday:                       \
        return x(wed);                          \
      case Qt::Thursday:                        \
        return x(thu);                          \
      case Qt::Friday:                          \
        return x(fri);                          \
      default:                                  \
        d                                       \
    }                                           \
  }()

static void ClearLayout(QLayout *layout) {
  if (!layout->count()) return;
  while (QLayoutItem *item = layout->takeAt(0)) {
    if (QWidget *child = item->widget()) child->deleteLater();
    delete item;
  }
}

void DisplayWindow::InitSentences(const google::protobuf::RepeatedPtrField<class_system::Sentence> &sentences) {
  // simply make the first sentence different every time
  const auto idx = QRandomGenerator::global()->bounded(sentences.size());
  for (auto i{idx}; i < sentences.size(); ++i) sentences_.push(sentences[i]);
  for (auto i{0}; i < idx; ++i) sentences_.push(sentences[i]);
}

QList<DisplayWindow::DailyArrangement> DisplayWindow::GetDailyArrangement() {
  static const auto FromPartial =
      [](const class_system::ClassInfo::PartialArrangement &arr) -> DisplayWindow::DailyArrangement {
    const auto &opts             = arr.opts();
    const auto  start_date       = QDate::fromString(QString::fromStdString(opts.start_date()), constants::kProtobufDateFormat);
    const auto  days_since_start = (int)start_date.daysTo(QDate::currentDate());
    const auto  cur_idx =
        ((days_since_start / opts.days_one_step()) * opts.students_one_step() + opts.start_idx()) %
        arr.student_ids_size();
    QList<int> student_ids_today;
    for (auto i{0}; i < opts.students_one_step(); ++i)
      student_ids_today.push_back(arr.student_ids((cur_idx + i) % arr.student_ids_size()));
    return {QString::fromStdString(arr.job()), student_ids_today};
  };

  static const auto FromComplete =
      [this](const class_system::ClassInfo::CompleteArrangement &arr) -> DisplayWindow::DailyArrangement {
    class_system::ClassInfo::PartialArrangement partial;
    partial.CopyFrom(arr);
    for (const auto &s : class_info_.students()) partial.mutable_student_ids()->Add(s.id());
    return FromPartial(partial);
  };

  static const auto FromWeekday =
      [](const class_system::ClassInfo::WeekdayArrangement &arr) -> DisplayWindow::DailyArrangement {
#define _X_(w) arr.w##_student_ids()
    const auto student_ids_today = GET_WEEKDAY_TODAY(_X_, arr, return google::protobuf::RepeatedField<int>{};);
#undef _X_

    return {QString::fromStdString(arr.job()), {student_ids_today.cbegin(), student_ids_today.cend()}};
  };

  QList<DisplayWindow::DailyArrangement> res_list;
  for (const auto &arr : class_info_.partial_arrangements()) res_list << FromPartial(arr);
  for (const auto &arr : class_info_.complete_arrangements()) res_list << FromComplete(arr);
  for (const auto &arr : class_info_.weekday_arrangements()) res_list << FromWeekday(arr);
  return res_list;
}

void DisplayWindow::DisplayArrangement() {
  const auto daily_arrangement = GetDailyArrangement();

  ClearLayout(ui_->arrangement_layout);

  // add new arrangement labels & layouts
  for (const auto &arr : daily_arrangement) {
    auto *const title_label = new QLabel(arr.job, ui_->arrangement_widget);
    title_label->setProperty("class", "title");

    auto *flow_layout = new FlowLayout{};
    flow_layout->setContentsMargins(9, 9, 12, 9);
    for (const auto &student_id : arr.student_ids) {
      auto *const stu_label = new QLabel{
          QString{constants::kStudentNameFormat}
              .arg(student_id)
              .arg(QString::fromStdString(
                  util::GetStudentNameById(class_info_.students(), student_id)
              )),
          ui_->arrangement_widget
      };
      flow_layout->addWidget(stu_label);
    }
    ui_->arrangement_layout->addRow(title_label, flow_layout);
  }
}

void DisplayWindow::DisplayLessons() {
  ClearLayout(ui_->lessons_layout);

  // add new lesson labels
  for (const auto &l : class_info_.lessons()) {
#define _X_(w) QString::fromStdString(l.w())
    const auto lesson_today = GET_WEEKDAY_TODAY(_X_, l, return QString{};);
#undef _X_

    auto *const lbl = new QLabel{
        QString{constants::kLessonFormat}
            .arg(lesson_today)
            .arg(QTime::fromString(QString::fromStdString(l.start_tm()), constants::kProtobufTimeFormat).toString("HH:mm"))
            .arg(QTime::fromString(QString::fromStdString(l.end_tm()), constants::kProtobufTimeFormat).toString("HH:mm")),
        ui_->lessons_widget
    };
    ui_->lessons_layout->addWidget(lbl);
  }
}

void DisplayWindow::UpdateLessonsStatus() {
  auto lbls = ui_->lessons_widget->findChildren<QLabel *>();
  if (lbls.size() != class_info_.lessons().size()) return;
  const auto lessons_cnt  = lbls.size();
  const auto cur_time_str = QTime::currentTime().toString(constants::kProtobufTimeFormat).toStdString();

  for (auto i{0}; i < lessons_cnt; ++i) {
    auto &lbl = lbls[i];
    if (
        (i > 0 && cur_time_str >= class_info_.lessons(i - 1).end_tm() && cur_time_str < class_info_.lessons(i).end_tm()) ||
        (i == 0 && cur_time_str < class_info_.lessons(i).end_tm())
    )
      lbl->setProperty("class", "current");
    else if (cur_time_str > class_info_.lessons(i).start_tm())
      lbl->setProperty("class", "past");
    else
      lbl->setProperty("class", "");
    lbl->style()->unpolish(lbl);
    lbl->style()->polish(lbl);
  }
}

void DisplayWindow::HandleSucceesfulResp(const class_system::Response &resp) {
  class_info_ = resp.class_info();

  InitSentences(resp.sentences());
  DisplayArrangement();

  HandleSwitchSentences();
  HandleSwitchNotices();
  sentences_notices_switch_timer_.start();

  DisplayLessons();

  show();
}

void DisplayWindow::HandleClockTick() {
  ui_->time_label->setText(QTime::currentTime().toString(constants::kTimeFormat));
  ui_->date_weekday_label->setText(QDate::currentDate().toString(constants::kDateWeekdayFormat));

  UpdateLessonsStatus();
}

void DisplayWindow::HandleSwitchSentences() {
  if (sentences_.empty()) return;

  const auto cur_sentence = sentences_.front();
  sentences_.pop();

  ui_->sentence_text_label->setText(QString::fromStdString(cur_sentence.text()));
  ui_->sentence_author_label->setText(
      QString{constants::kSentenceAuthorFormat}
          .arg(QString::fromStdString(cur_sentence.author()))
  );

  sentences_.push(cur_sentence);
}

void DisplayWindow::HandleSwitchNotices() {
  if (class_info_.notices().empty()) {
    ui_->notices_data_title_label->setText("无公告");
    ui_->notices_date_label->setText("");
    ui_->notices_text_browser->setText("");
    return;
  }

  static int cur_notice_index{};
  if (cur_notice_index >= class_info_.notices_size()) cur_notice_index = 0;
  const auto &cur_notice = class_info_.notices(cur_notice_index);
  ui_->notices_data_title_label->setText(QString::fromStdString(cur_notice.title()));
  ui_->notices_text_browser->setText(QString::fromStdString(cur_notice.text()));
  const auto date_str = cur_notice.date() == "FOREVER"
                            ? ""
                            : QDate::fromString(
                                  QString::fromStdString(cur_notice.date()), constants::kProtobufDateFormat
                              )
                                  .toString(constants::kNoticeDateFormat);
  ui_->notices_date_label->setText(date_str);

  ++cur_notice_index;
}
