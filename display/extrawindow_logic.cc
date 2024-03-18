#include <qset.h>

#include "constants/constants.h"
#include "extrawindow.h"
#include "globalstore.h"
#include "qrandom.h"
#include "ui_extrawindow.h"

static QSet<int>            called_set;
static GlobalStore::Student rollcall_cur_tick_called;
static int                  rollcall_timer_tick_cnt{};
static bool                 rollcall_first{};  // 点名人数超过 1 时是否为第一轮抽选

/* ---------------------------------------------------------------- */
/*                             Roll Call                            */
/* ---------------------------------------------------------------- */

void ExtraWindow::RollCallOne() {
  int idx{};
  if (called_set.size() == GlobalStore::GetClassInfo().students.size()) HandleResetRollCall();
  do {
    idx = QRandomGenerator::global()->bounded(GlobalStore::GetClassInfo().students.size());
  } while (called_set.contains(GlobalStore::GetClassInfo().students[idx].id));

  rollcall_cur_tick_called = GlobalStore::GetClassInfo().students[idx];
}

void ExtraWindow::HandleSuccessfulResp() {
  ui_->tab_widget->setTabEnabled(0, !GlobalStore::GetClassInfo().students.empty());
  if (!GlobalStore::GetClassInfo().students.empty())
    HandleResetRollCall();
}

void ExtraWindow::HandleStartRollCall() {
  rollcall_first = true;
  ui_->rollcall_start_button->setDisabled(true);
  rollcall_timer_.start();
}

void ExtraWindow::HandleRollCallTick() {
  ++rollcall_timer_tick_cnt;

  RollCallOne();

  if (rollcall_first) {
    ui_->cur_called_label->setText(rollcall_cur_tick_called.GetDisplayStr());
  } else {
    // 如果不是第一轮抽人，则往目前抽到标签上增加显示名字
    const auto cur_called_text        = ui_->cur_called_label->text();
    const auto should_insert_new_line = cur_called_text.simplified().count(' ') % 2 == 1;
    ui_->cur_called_label->setText(
        cur_called_text +
        (should_insert_new_line ? '\n' : ' ') +
        rollcall_cur_tick_called.GetDisplayStr()
    );
  }

  ui_->uncalled_students_label->setText(
      QString{constants::kRollCallUncalledFormat}.arg(GlobalStore::GetClassInfo().students.size() - called_set.size())
  );

  // 更新已抽列表
  if (rollcall_timer_tick_cnt == 10 || !rollcall_first) {
    called_set += rollcall_cur_tick_called.id;
    ui_->called_list->addItem(ui_->cur_called_label->text().simplified().split(' ').back());
  }
  // 已经选出第一个学生了
  if (rollcall_timer_tick_cnt == 10) {
    rollcall_timer_.stop();
    rollcall_timer_tick_cnt = 0;

    // 如果要抽更多的学生，则一次性抽完
    const auto rollcall_count = ui_->rollcall_count_label->text().toUShort();
    if (rollcall_count > 1) rollcall_first = false;
    for (unsigned short i{}; i < rollcall_count - 1; ++i) {
      HandleRollCallTick();
    }

    ui_->rollcall_start_button->setEnabled(true);
  }
}

void ExtraWindow::HandleResetRollCall() {
  called_set.clear();
  ui_->called_list->clear();
  ui_->uncalled_students_label->setText(
      QString{constants::kRollCallUncalledFormat}.arg(GlobalStore::GetClassInfo().students.size())
  );
  // 如果不是正在抽选多人，则清空对于目前抽到的学生的显示
  if (rollcall_first) ui_->cur_called_label->clear();
}

void ExtraWindow::HandleChangeRollCallCount() {
  auto rollcall_count = ui_->rollcall_count_label->text().toUShort();
  if (rollcall_count < 10 && sender() == ui_->rollcall_increase_count_btn) ++rollcall_count;
  if (rollcall_count > 1 && sender() == ui_->rollcall_decrease_count_btn) --rollcall_count;
  ui_->rollcall_count_label->setText(QString::number(rollcall_count));
}
