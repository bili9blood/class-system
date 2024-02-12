#include "displaywindow.h"

#include <qevent.h>
#include <qpainter.h>
#include <qscreen.h>

#include "constants.h"
#include "native.h"
#include "ui_displaywindow.h"

DisplayWindow::DisplayWindow(QWidget *parent) : QMainWindow{parent}, ui_{new Ui::DisplayWindow} {
  ui_->setupUi(this);
  centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);

  setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
  setAttribute(Qt::WA_TranslucentBackground);

  // NOLINTNEXTLINE
  ::SetParent((HWND)winId(), native::GetFrontDesktopHwnd());

  clock_timer_.setInterval(constants::kClockTimerIntervalMs);
  connect(&clock_timer_, &QTimer::timeout, this, &DisplayWindow::HandleClockTick);
  clock_timer_.start();

  sentences_notices_switch_timer_.setInterval(constants::kSentencesNoticesSwitchTimerIntervalMs);
  connect(&sentences_notices_switch_timer_, &QTimer::timeout, this, &DisplayWindow::HandleSwitchSentencesAndNotices);
  sentences_notices_switch_timer_.start();
}

DisplayWindow::~DisplayWindow() = default;

void DisplayWindow::mousePressEvent(QMouseEvent *event) {
  mouse_start_pos_ = event->pos();
}

void DisplayWindow::mouseMoveEvent(QMouseEvent *event) {
  move(event->globalPos() - mouse_start_pos_);
}

void DisplayWindow::mouseReleaseEvent(QMouseEvent *event) {
  move(
      qBound(0, x(), QApplication::primaryScreen()->availableGeometry().width() - width()),
      qBound(0, y(), QApplication::primaryScreen()->availableGeometry().height() - height())
  );
}

void DisplayWindow::paintEvent(QPaintEvent *event) {
  QPainter        painter{this};

  QLinearGradient ling{{0, 0}, rect().bottomRight()};
  constexpr unsigned short kAlpha{154};
  ling.setColorAt(0, QColor{0, 12, 64, kAlpha});
  ling.setColorAt(1, QColor{96, 125, 139, kAlpha});

  painter.setPen(Qt::NoPen);
  painter.setBrush(ling);

  constexpr qreal kRadius{20.0};
  painter.drawRoundedRect(rect(), kRadius, kRadius);
}

void DisplayWindow::closeEvent(QCloseEvent *event) { QApplication::quit(); }
