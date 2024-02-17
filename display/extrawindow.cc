#include "extrawindow.h"

#include <qevent.h>

#include "ui_extrawindow.h"

ExtraWindow::ExtraWindow(QWidget *parent) : QWidget{parent}, ui_{new Ui::ExtraWindow} {
  ui_->setupUi(this);
}

ExtraWindow::~ExtraWindow() = default;

void ExtraWindow::closeEvent(QCloseEvent *event) {
  Q_EMIT Hided();
  hide();
  event->ignore();
}
