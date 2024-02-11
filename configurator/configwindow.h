#pragma once

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QWidget {
  Q_OBJECT
 public:
  explicit ConfigWindow(QWidget* parent = nullptr);
  ~ConfigWindow() override;

 private:
  std::unique_ptr<Ui::ConfigWindow> ui_;
};
