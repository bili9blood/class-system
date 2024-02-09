#include "weatherwidget.h"

#include "ui_weatherwidget.h"

WeatherWidget::WeatherWidget(QWidget *parent) : QWidget{parent}, ui_{new Ui::WeatherWidget} {
  ui_->setupUi(this);
}

WeatherWidget::~WeatherWidget() = default;
