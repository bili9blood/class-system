#pragma once

namespace Ui {
class WeatherWidget;
}

class WeatherWidget : public QWidget {
  Q_OBJECT
 public:
  explicit WeatherWidget(
      const int& icon_day, const int& temp_min, const int& temp_max,
      const QDate& date,
      QWidget*     parent = nullptr
  );
  ~WeatherWidget() override;

 private:
  std::unique_ptr<Ui::WeatherWidget> ui_;
};
