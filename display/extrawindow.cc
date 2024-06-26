#include "extrawindow.h"

#include <qevent.h>
#include <qscreen.h>

#include "config.h"
#include "constants/constants.h"
#include "globalstore.h"
#include "ui_extrawindow.h"

static auto initilized{false};

ExtraWindow::ExtraWindow(QWidget *parent) : QWidget{parent, Qt::WindowStaysOnTopHint}, ui_{new Ui::ExtraWindow} {
  setWindowFlag(Qt::WindowMinMaxButtonsHint, false);

  ui_->setupUi(this);

  QFile ss_file{":/styles/material-light-blue.qss"};
  ss_file.open(QFile::ReadOnly);
  setStyleSheet(ss_file.readAll());

  rollcall_timer_.setInterval(constants::kRollCallTimerIntervalMs);
  rollcall_timer_.setTimerType(Qt::PreciseTimer);

  connect(&GlobalStore::Get(), &GlobalStore::SucceededHandleResp, this, &ExtraWindow::HandleSuccessfulResp);
  connect(&rollcall_timer_, &QTimer::timeout, this, &ExtraWindow::HandleRollCallTick);
}

ExtraWindow::~ExtraWindow() = default;

void ExtraWindow::paintEvent(QPaintEvent *event) {
  if (!initilized) {
    initilized = true;
    move(
        config::Get()["ExtraWindow"]["x"].value_or(x()),
        config::Get()["ExtraWindow"]["y"].value_or(y())
    );
    resize(
        config::Get()["ExtraWindow"]["w"].value_or(width()),
        config::Get()["ExtraWindow"]["h"].value_or(height())
    );
  }
}

void ExtraWindow::moveEvent(QMoveEvent *event) {
  if (initilized) {
    config::Get()["ExtraWindow"].as_table()->insert_or_assign("x", x());
    config::Get()["ExtraWindow"].as_table()->insert_or_assign("y", y());
  }

  static std::unique_ptr<QTimer> move_back_timer;  // for debounce
  if (!move_back_timer) {
    move_back_timer = std::make_unique<QTimer>();
    move_back_timer->setInterval(100);
    move_back_timer->setSingleShot(true);
    connect(move_back_timer.get(), &QTimer::timeout, [this] {
      move(
          qBound(0, x(), QApplication::primaryScreen()->availableSize().width() - width()),
          qBound(0, y(), QApplication::primaryScreen()->availableSize().height() - height())
      );
    });
  }

  move_back_timer->start();
}

void ExtraWindow::resizeEvent(QResizeEvent *event) {
  if (initilized) {
    config::Get()["ExtraWindow"].as_table()->insert_or_assign("w", width());
    config::Get()["ExtraWindow"].as_table()->insert_or_assign("h", height());
  }
}

void ExtraWindow::closeEvent(QCloseEvent *event) {
  Q_EMIT Hided();
  hide();
  event->ignore();
}
