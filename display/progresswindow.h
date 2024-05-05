#pragma once

#include <qdialog.h>

class QProgressBar;

class ProgressWindow : public QDialog {
  Q_OBJECT
 public:
  explicit ProgressWindow(QWidget* parent = nullptr);
  ~ProgressWindow() override;

  void SetLabelText(const QString& text);
  void SetRange(const int& min, const int& max);
  void SetValue(const int& value);

 private:
  std::unique_ptr<QLabel>       label_;
  std::unique_ptr<QProgressBar> progress_bar_;
};
