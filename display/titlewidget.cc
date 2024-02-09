#include "titlewidget.h"

#include "ui_titlewidget.h"

TitleWidget::TitleWidget(QWidget *parent) : QWidget{parent}, ui_{new Ui::TitleWidget} {
  ui_->setupUi(this);
}

TitleWidget::~TitleWidget() = default;
