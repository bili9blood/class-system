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

  void                             closeEvent(QCloseEvent* event) final;
};
