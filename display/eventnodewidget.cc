#include "eventnodewidget.h"

#include <qdatetime.h>
#include <qstyle.h>

#include "constants/constants.h"
#include "ui_eventnodewidget.h"

EventNodeWidget::EventNodeWidget(const class_system::ClassInfo::Event &event, QWidget *parent)
    : QWidget{parent}, ui_{new Ui::EventNodeWidget} {
  ui_->setupUi(this);

  const auto date = QDate::fromString(QString::fromStdString(event.date()), constants::kProtobufDateFormat);

  if (date != QDate::currentDate())
    ui_->days_left_label->setText(ui_->days_left_label->text().arg(QDate::currentDate().daysTo(date)));
  else
    ui_->days_left_label->setText("今天");

  ui_->date_label->setText(date.toString(ui_->date_label->text()));
  ui_->name_label->setText(QString::fromStdString(event.title()));
  if (event.important()) {
    ui_->icon_label->setProperty("class", "important");
    ui_->icon_label->style()->unpolish(ui_->icon_label);
    ui_->icon_label->style()->polish(ui_->icon_label);

    ui_->icon_label->setText(u8"\uf005");
  } else {
    ui_->icon_label->setText(u8"\uf111");
  }
}

EventNodeWidget::~EventNodeWidget() = default;
