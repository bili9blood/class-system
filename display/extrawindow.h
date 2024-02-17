#pragma once

namespace Ui {
class ExtraWindow;
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

  void                             paintEvent(QPaintEvent* event) final;
  void                             moveEvent(QMoveEvent* event) final;
  void                             resizeEvent(QResizeEvent* event) final;
  void                             closeEvent(QCloseEvent* event) final;
};
