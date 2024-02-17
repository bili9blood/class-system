#pragma once

namespace Ui {
class WeatherWidget;
}

class WeatherWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit WeatherWidget(
      const int& icon_day, const int& temp_min, const int& temp_max,
      const QDate& date,
      QWidget*     parent = nullptr
  );
  ~WeatherWidget() final;

 private:
  std::unique_ptr<Ui::WeatherWidget> ui_;
};
