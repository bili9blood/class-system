#include "configwindow.h"

#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) : QWidget(parent), ui_{new Ui::ConfigWindow} {
  ui_->setupUi(this);
}

ConfigWindow::~ConfigWindow() = default;
