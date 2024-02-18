#include "extrawindow.h"

#include <qevent.h>

#include "config.h"
#include "ui_extrawindow.h"

static auto initilized{false};

ExtraWindow::ExtraWindow(QWidget *parent) : QWidget{parent, Qt::WindowStaysOnTopHint}, ui_{new Ui::ExtraWindow} {
  ui_->setupUi(this);

  QFile ss_file{":/styles/material-light-blue.qss"};
  ss_file.open(QFile::ReadOnly);
  setStyleSheet(ss_file.readAll());
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
