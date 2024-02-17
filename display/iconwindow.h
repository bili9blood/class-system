#pragma once

namespace Ui {
class IconWindow;
}

class ExtraWindow;

class IconWindow final : public QWidget {
  Q_OBJECT
 public:
  explicit IconWindow(QWidget* parent = nullptr);
  ~IconWindow() final;

 private:
  std::unique_ptr<Ui::IconWindow> ui_;
  std::unique_ptr<ExtraWindow>    extra_window_;

  QPoint                          mouse_start_pos_;
  int                             prev_y_{};

  bool                            eventFilter(QObject* object, QEvent* event) final;
  void                            moveEvent(QMoveEvent* event) final;
};
