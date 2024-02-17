#include "iconwindow.h"

#include <qapplication.h>
#include <qevent.h>
#include <qscreen.h>

#include "config.h"
#include "extrawindow.h"
#include "ui_iconwindow.h"

IconWindow::IconWindow(QWidget* parent)
    : QWidget{parent, Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool}, ui_{new Ui::IconWindow} {
  extra_window_ = std::make_unique<ExtraWindow>();
  ui_->setupUi(this);

  setAttribute(Qt::WA_TranslucentBackground);
  setFixedSize(QApplication::primaryScreen()->availableSize().width(), ui_->left_label->height());
  move(0, config::Get()["IconWindow"]["y"].value_or(0));

  ui_->left_label->installEventFilter(this);
  ui_->right_label->installEventFilter(this);

  connect(extra_window_.get(), &ExtraWindow::Hided, this, &IconWindow::show);
}

IconWindow::~IconWindow() = default;

bool IconWindow::eventFilter(QObject* object, QEvent* event) {
  auto out{false};

  if (object == ui_->left_label || object == ui_->right_label) {
    if (event->type() == QEvent::MouseButtonPress) {
      prev_y_                 = y();

      auto* const mouse_event = dynamic_cast<QMouseEvent*>(event);
      mouse_start_pos_        = mouse_event->pos();
      out                     = true;
    }

    if (event->type() == QEvent::MouseMove) {
      auto* const mouse_event = dynamic_cast<QMouseEvent*>(event);
      move(0, (mouse_event->globalPos() - mouse_start_pos_).y());
      out = true;
    }

    if (event->type() == QEvent::MouseButtonRelease) {
      move(0, qBound(0, y(), QApplication::primaryScreen()->availableGeometry().height() - height()));
      if (abs(y() - prev_y_) < 10) {
        extra_window_->show();
        hide();
      }
    }
  }

  return out || QWidget::eventFilter(object, event);
}

void IconWindow::moveEvent(QMoveEvent* event) {
  config::Get()["IconWindow"].as_table()->insert_or_assign("y", y());
}
