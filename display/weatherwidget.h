#pragma once

namespace Ui {
class WeatherWidget;
}

class WeatherWidget : public QWidget {
  Q_OBJECT
 public:
  explicit WeatherWidget(QWidget* parent = nullptr);
  ~WeatherWidget() override;

 private:
  std::unique_ptr<Ui::WeatherWidget> ui_;
};
