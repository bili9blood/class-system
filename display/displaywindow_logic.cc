#include <qdatetime.h>
#include <qrandom.h>
#include <qstyle.h>
#include <shared/constants.h>

#include "constants.h"
#include "displaywindow.h"
#include "ui_displaywindow.h"

static QString GetLessonToday(const class_system::ClassInfo::WeeklyLessons &lessons) {
  switch (QDate::currentDate().dayOfWeek()) {
    case Qt::Monday:
      return QString::fromStdString(lessons.mon());
    case Qt::Tuesday:
      return QString::fromStdString(lessons.tue());
    case Qt::Wednesday:
      return QString::fromStdString(lessons.wed());
    case Qt::Thursday:
      return QString::fromStdString(lessons.thu());
    case Qt::Friday:
      return QString::fromStdString(lessons.fri());
    default:
      return {};
  }
}

void DisplayWindow::UpdateLessonsClass() {
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
  // simply make the first sentence different every time
  {
    const auto idx = QRandomGenerator::global()->bounded(resp.sentences_size());
    for (auto i{idx}; i < (int)resp.sentences_size(); ++i) sentences_.push(resp.sentences(i));
    for (auto i{0}; i < idx; ++i) sentences_.push(resp.sentences(i));
  }

  HandleSwitchSentences();
  HandleSwitchNotices();
  sentences_notices_switch_timer_.start();

  // remove old lesson labels
  auto old_lesson_labels = ui_->lessons_widget->findChildren<QLabel *>();
  for (const auto &l : old_lesson_labels) l->deleteLater();

  // add new lesson labels
  for (const auto &l : class_info_.lessons()) {
    auto *const lbl = new QLabel{
        QString{constants::kLessonFormat}
            .arg(GetLessonToday(l))
            .arg(QTime::fromString(QString::fromStdString(l.start_tm()), constants::kProtobufTimeFormat).toString("HH:mm"))
            .arg(QTime::fromString(QString::fromStdString(l.end_tm()), constants::kProtobufTimeFormat).toString("HH:mm")),
        ui_->lessons_widget
    };
    ui_->lessons_layout->addWidget(lbl);
  }

  show();
}

void DisplayWindow::HandleClockTick() {
  ui_->time_label->setText(QTime::currentTime().toString(constants::kTimeFormat));
  ui_->date_weekday_label->setText(QDate::currentDate().toString(constants::kDateWeekdayFormat));

  UpdateLessonsClass();
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
