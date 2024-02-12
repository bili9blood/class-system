#include <qdatetime.h>

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
}
