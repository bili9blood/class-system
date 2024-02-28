#include "displaywindow.h"

#include <qevent.h>
#include <qpainter.h>
#include <qscreen.h>
#include <windowsx.h>

#include "config.h"
#include "constants.h"
#include "flowlayout.h"
#include "globalstore.h"
#include "native.h"
#include "ui_displaywindow.h"

static auto initilized = false;

DisplayWindow::DisplayWindow(QWidget *parent) : QMainWindow{parent}, ui_{new Ui::DisplayWindow} {
  ui_->setupUi(this);
  centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
  ui_->events_widget->setLayout(new FlowLayout{});

  setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
  setAttribute(Qt::WA_TranslucentBackground);

  clock_timer_.setInterval(constants::kClockTimerIntervalMs);
  connect(&clock_timer_, &QTimer::timeout, this, &DisplayWindow::HandleClockTick);
  clock_timer_.start();

  sentences_notices_switch_timer_.setInterval(constants::kSentencesNoticesSwitchTimerIntervalMs);
  connect(&sentences_notices_switch_timer_, &QTimer::timeout, this, &DisplayWindow::HandleSwitchSentences);
  connect(&sentences_notices_switch_timer_, &QTimer::timeout, this, &DisplayWindow::HandleSwitchNotices);
  sentences_notices_switch_timer_.start();

  DisplayWeather();

  connect(GlobalStore::Get(), &GlobalStore::SucceededHandleResp, this, &DisplayWindow::HandleSucceesfulResp);
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

bool DisplayWindow::nativeEvent(const QByteArray &event_type, void *message, long *result) {
#ifdef WIN32
  const auto *msg = static_cast<MSG *>(message);
  if (msg->message == WM_NCHITTEST) {
    *result                = 0l;
    constexpr int kPadding = 14;
    const auto    x        = GET_X_LPARAM(msg->lParam);
    const auto    y        = GET_Y_LPARAM(msg->lParam);
    RECT          rect     = {};

    // NOLINTNEXTLINE
    ::GetWindowRect((HWND)winId(), &rect);

    // clang-format off
    if (y < rect.top + kPadding && x < rect.left + kPadding) *result = HTTOPLEFT;
    else if (y < rect.top + kPadding && x > rect.right - kPadding) *result = HTTOPRIGHT;
    else if (y > rect.bottom - kPadding && x < rect.left + kPadding) *result = HTBOTTOMLEFT;
    else if (y > rect.bottom - kPadding && x > rect.right - kPadding) *result = HTBOTTOMRIGHT;
    else if (y < rect.top + kPadding) *result = HTTOP;
    else if (y > rect.bottom - kPadding) *result = HTBOTTOM;
    else if (x < rect.left + kPadding) *result = HTLEFT;
    else if (x > rect.right - kPadding) *result = HTRIGHT;
    else return false;
    // clang-format on
    return true;
  }
#endif
  return QMainWindow::nativeEvent(event_type, message, result);
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

  if (!initilized) {
    initilized = true;

    move(config::Get()["DisplayWindow"]["x"].value_or(x()), config::Get()["DisplayWindow"]["y"].value_or(y()));
    resize(config::Get()["DisplayWindow"]["w"].value_or(width()), config::Get()["DisplayWindow"]["h"].value_or(height()));
  }
}

void DisplayWindow::moveEvent(QMoveEvent *event) {
  if (initilized) {
    config::Get()["DisplayWindow"].as_table()->insert_or_assign("x", x());
    config::Get()["DisplayWindow"].as_table()->insert_or_assign("y", y());
  }
}

void DisplayWindow::resizeEvent(QResizeEvent *event) {
  if (initilized) {
    config::Get()["DisplayWindow"].as_table()->insert_or_assign("w", width());
    config::Get()["DisplayWindow"].as_table()->insert_or_assign("h", height());
  }
}

void DisplayWindow::closeEvent(QCloseEvent *event) { QApplication::quit(); }

void DisplayWindow::MoveCenter() {
  const auto screen_size = QApplication::primaryScreen()->size();
  move(
      (screen_size.width() - width()) / 2,
      (screen_size.height() - height()) / 2
  );
}

void DisplayWindow::SwitchWindowLayer(const bool &front) {
  // NOLINTNEXTLINE
  ::SetParent((HWND)winId(), front ? native::GetFrontDesktopHwnd() : native::GetBackDesktopHwnd());
  hide();
  show();
}
