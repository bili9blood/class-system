#include <qdatetime.h>
#include <shared/constants.h>

#include "constants.h"
#include "displaywindow.h"
#include "ui_displaywindow.h"

void DisplayWindow::HandleSucceesfulResp(const class_system::Response &resp) {
  class_info_ = resp.class_info();
  for (const auto &s : resp.sentences()) sentences_.push(s);

  HandleSwitchSentences();
  HandleSwitchNotices();
  sentences_notices_switch_timer_.start();

  show();
}

void DisplayWindow::HandleClockTick() {
  ui_->time_label->setText(QTime::currentTime().toString(constants::kTimeFormat));
  ui_->date_weekday_label->setText(QDate::currentDate().toString(constants::kDateWeekdayFormat));
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