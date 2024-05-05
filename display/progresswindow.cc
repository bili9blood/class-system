#include "progresswindow.h"

#include <qboxlayout.h>
#include <qlabel.h>
#include <qprogressbar.h>

ProgressWindow::ProgressWindow(QWidget* parent) : QDialog{parent, Qt::MSWindowsFixedSizeDialogHint} {
  setLayout(new QHBoxLayout{this});

  label_        = std::make_unique<QLabel>(this);
  progress_bar_ = std::make_unique<QProgressBar>(this);

  layout()->addWidget(label_.get());
  layout()->addWidget(progress_bar_.get());
}

ProgressWindow::~ProgressWindow() = default;

void ProgressWindow::SetLabelText(const QString& text) {
  label_->setText(text);
}

void ProgressWindow::SetRange(const int& min, const int& max) {
  progress_bar_->setRange(min, max);
}

void ProgressWindow::SetValue(const int& value) {
  progress_bar_->setValue(value);
}
