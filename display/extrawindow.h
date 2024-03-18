#pragma once
#include <qtimer.h>

namespace Ui {
class ExtraWindow;
}

namespace class_system {
class Response;
}

class ExtraWindow final : public QWidget {
  Q_OBJECT
 public:
  explicit ExtraWindow(QWidget* parent = nullptr);
  ~ExtraWindow() final;

 signals:
  void Hided();

 private:
  std::unique_ptr<Ui::ExtraWindow> ui_;

  QTimer                           rollcall_timer_;

  void                             paintEvent(QPaintEvent* event) final;
  void                             moveEvent(QMoveEvent* event) final;
  void                             resizeEvent(QResizeEvent* event) final;
  void                             closeEvent(QCloseEvent* event) final;

  void                             RollCallOne();

 private slots:
  void HandleSuccessfulResp();
  void HandleStartRollCall();
  void HandleRollCallTick();
  void HandleResetRollCall();
  void HandleChangeRollCallCount();
};
