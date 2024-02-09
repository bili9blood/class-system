#pragma once

namespace Ui {
class TitleWidget;
}

class TitleWidget : public QWidget {
  Q_OBJECT
 public:
  explicit TitleWidget(QWidget* parent = nullptr);
  ~TitleWidget() override;

 private:
  std::unique_ptr<Ui::TitleWidget> ui_;
};
