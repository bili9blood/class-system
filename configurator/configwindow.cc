#include "configwindow.h"

#include <google/protobuf/descriptor.h>
#include <proto/DisplayConfig.pb.h>

#include <fstream>

#include "ui_configwindow.h"

static std::shared_ptr<google::protobuf::Message> LoadDisplayConfig() {
  auto          msg = std::make_shared<class_system::DisplayConfig>();
  std::ifstream ifs{"config.dat"};
  msg->ParseFromIstream(&ifs);
  return msg;
}

static std::shared_ptr<google::protobuf::Message> LoadManageConfig() {
  auto msg = std::make_shared<class_system::DisplayConfig>();
  // TODO:
  return msg;
}

ConfigWindow::ConfigWindow(const ConfigApp &app, QWidget *parent) : QWidget(parent), ui_{new Ui::ConfigWindow} {
  ui_->setupUi(this);

  ui_->int_val_edit->setValidator(new QIntValidator{INT_MIN, INT_MAX, ui_->int_val_edit});
  ui_->edited_label->hide();

  connect(&hide_edited_timer_, &QTimer::timeout, ui_->edited_label, &QLabel::hide);

  switch (app) {
    case ConfigApp::CLASS_SYSTEM_DISPLAY:
      ui_->tip_label->setText(ui_->tip_label->text().arg("显示端"));
      msg_ = LoadDisplayConfig();
      break;
    case ConfigApp::CLASS_SYSTEM_MANAGE:
      ui_->tip_label->setText(ui_->tip_label->text().arg("管理端"));
      msg_ = LoadManageConfig();
      break;
  }

  const auto *const desc = msg_->GetDescriptor();
  refl_                  = msg_->GetReflection();
  for (int i = 0; i < desc->field_count(); ++i) {
    using Type              = google::protobuf::FieldDescriptor::Type;

    const auto *const field = desc->field(i);
    const auto        name  = QString::fromStdString(field->name());
    ui_->field_combo->addItem(name, QVariant::fromValue((void *)field));
  }
  ui_->field_combo->setCurrentIndex(0);
}

ConfigWindow::~ConfigWindow() = default;

void ConfigWindow::HandleFieldChange() {
  using Type                  = google::protobuf::FieldDescriptor::Type;
  cur_field_name_             = ui_->field_combo->currentText();
  const auto *const cur_field = (const google::protobuf::FieldDescriptor *)ui_->field_combo->currentData().value<void *>();

  HideAllEdit();
  if (cur_field->type() == Type::TYPE_STRING) {
    ui_->string_val_edit->show();
    ui_->string_val_label->show();
    ui_->string_val_edit->setText(QString::fromStdString(refl_->GetString(*msg_, cur_field)));
  } else if (cur_field->type() == Type::TYPE_INT32) {
    ui_->int_val_edit->show();
    ui_->int_val_label->show();
    ui_->int_val_edit->setText(QString::number(refl_->GetInt32(*msg_, cur_field)));
  }
}

void ConfigWindow::HandleValueChange() {
  if (!refl_ || !msg_) return;

  const auto *const cur_field = (const google::protobuf::FieldDescriptor *)ui_->field_combo->currentData().value<void *>();
  if (sender()->objectName() == "string_val_edit") {
    refl_->SetString(msg_.get(), cur_field, ui_->string_val_edit->text().toStdString());
  } else if (sender()->objectName() == "int_val_edit") {
    refl_->SetInt32(msg_.get(), cur_field, ui_->int_val_edit->text().toInt());
  }

  ui_->edited_label->show();
  hide_edited_timer_.start(150);
}

void ConfigWindow::HideAllEdit() {
  for (const auto &child : children())
    if (child->objectName().contains("_val_"))
      dynamic_cast<QWidget *>(child)->hide();
}

void ConfigWindow::SaveConfig() {
  std::ofstream ofs{"config.dat"};
  msg_->SerializeToOstream(&ofs);
}

void ConfigWindow::closeEvent(QCloseEvent *event) {
  SaveConfig();
  QApplication::quit();
}
