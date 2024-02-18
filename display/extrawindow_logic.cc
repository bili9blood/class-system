#include <proto/Response.pb.h>
#include <qset.h>

#include "constants.h"
#include "extrawindow.h"
#include "qrandom.h"
#include "ui_extrawindow.h"
#include "util.h"

static QSet<int> called_set;
static int       rollcall_cur_tick_called{};
static int       rollcall_timer_tick_cnt{};

void             ExtraWindow::HandleSuccessfulResp(const class_system::Response& resp) {
  class_info_ = resp.class_info();

  ui_->tab_widget->setTabEnabled(0, class_info_.students_size());
  if (class_info_.students_size())
    HandleResetRollCall();
}

void ExtraWindow::HandleStartRollCall() {
  ui_->rollcall_start_button->setDisabled(true);
  rollcall_timer_.start();
}

void ExtraWindow::HandleRollCallTick() {
  ++rollcall_timer_tick_cnt;

  int idx{};
  do {
    idx = QRandomGenerator::global()->bounded(class_info_.students_size());
  } while (called_set.contains(class_info_.students(idx).id()));

  rollcall_cur_tick_called = class_info_.students(idx).id();

  ui_->cur_called_label->setText(
      QString{constants::kStudentNameFormat}
          .arg(rollcall_cur_tick_called)
          .arg(util::GetStudentNameById(class_info_.students(), rollcall_cur_tick_called).c_str())
  );

  ui_->uncalled_students_label->setText(
      QString{constants::kRollCallUncalledFormat}.arg(class_info_.students_size() - called_set.size())
  );

  if (rollcall_timer_tick_cnt == 10 || called_set.size() == class_info_.students_size()) {
    rollcall_timer_.stop();
    called_set += rollcall_cur_tick_called;
    ui_->called_list->addItem(ui_->cur_called_label->text());
    rollcall_timer_tick_cnt = 0;
    ui_->rollcall_start_button->setEnabled(true);
    return;
  }
}

void ExtraWindow::HandleResetRollCall() {
  called_set.clear();
  ui_->called_list->clear();
  ui_->uncalled_students_label->setText(
      QString{constants::kRollCallUncalledFormat}.arg(class_info_.students_size())
  );
  ui_->cur_called_label->clear();
}
