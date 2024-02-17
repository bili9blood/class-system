#pragma once

namespace Ui {
class TitleWidget;
}

class TitleWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit TitleWidget(QWidget* parent = nullptr);
  ~TitleWidget() final;

 private:
  std::unique_ptr<Ui::TitleWidget> ui_;
};
