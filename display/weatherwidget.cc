#include "weatherwidget.h"

#include <qdatetime.h>

#include "constants/constants.h"
#include "ui_weatherwidget.h"

WeatherWidget::WeatherWidget(
    const int& icon_day, const int& temp_min, const int& temp_max,
    const QDate& date,
    QWidget*     parent
) : QWidget{parent}, ui_{new Ui::WeatherWidget} {
  // set class before setup ui
  if (date == QDate::currentDate()) setProperty("class", "weather-today");

  ui_->setupUi(this);

  const auto* const it = std::find_if(
      constants::kQweatherIconMap, std::end(constants::kQweatherIconMap),
      [&icon_day](const auto& pair) { return pair.first == icon_day; }
  );

  if (it != std::end(constants::kQweatherIconMap))
    ui_->icon_label->setText(it->second);

  ui_->temp_label->setText(QString{constants::kTemptureFormat}.arg(temp_min).arg(temp_max));

  ui_->date_weekday_label->setText(date.toString(constants::kDateWeekdayFormat));
}

WeatherWidget::~WeatherWidget() = default;
