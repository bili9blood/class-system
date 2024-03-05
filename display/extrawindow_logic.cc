#include <qset.h>

#include "constants/constants.h"
#include "extrawindow.h"
#include "globalstore.h"
#include "qrandom.h"
#include "ui_extrawindow.h"

static QSet<int>            called_set;
static GlobalStore::Student rollcall_cur_tick_called;
static int                  rollcall_timer_tick_cnt{};

void                        ExtraWindow::HandleSuccessfulResp() {
  ui_->tab_widget->setTabEnabled(0, !GlobalStore::GetClassInfo().students.empty());
  if (!GlobalStore::GetClassInfo().students.empty())
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
    idx = QRandomGenerator::global()->bounded(GlobalStore::GetClassInfo().students.size());
  } while (called_set.contains(GlobalStore::GetClassInfo().students[idx].id));

  rollcall_cur_tick_called = GlobalStore::GetClassInfo().students[idx];

  ui_->cur_called_label->setText(rollcall_cur_tick_called.GetDisplayStr());

  ui_->uncalled_students_label->setText(
      QString{constants::kRollCallUncalledFormat}.arg(GlobalStore::GetClassInfo().students.size() - called_set.size())
  );

  if (rollcall_timer_tick_cnt == 10 || called_set.size() == GlobalStore::GetClassInfo().students.size()) {
    rollcall_timer_.stop();
    called_set += rollcall_cur_tick_called.id;
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
      QString{constants::kRollCallUncalledFormat}.arg(GlobalStore::GetClassInfo().students.size())
  );
  ui_->cur_called_label->clear();
}
