#include "titlewidget.h"

#include "ui_titlewidget.h"
#include "version.h"

TitleWidget::TitleWidget(QWidget *parent) : QWidget{parent}, ui_{new Ui::TitleWidget} {
  ui_->setupUi(this);

  ui_->title_label->setText(QString::asprintf(ui_->title_label->text().toUtf8().data(), kVersion + 1));
}

TitleWidget::~TitleWidget() = default;
