#pragma once

#include <google/protobuf/reflection.h>
#include <qtimer.h>

enum class ConfigApp {
  CLASS_SYSTEM_DISPLAY,
  CLASS_SYSTEM_MANAGE,
};

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QWidget {
  Q_OBJECT
 public:
  explicit ConfigWindow(const ConfigApp& app, QWidget* parent = nullptr);
  ~ConfigWindow() override;

  // NOLINTNEXTLINE
 public slots:
  void HandleFieldChange();
  void HandleValueChange();

 private:
  std::unique_ptr<Ui::ConfigWindow> ui_;
  QString                                    cur_field_name_;
  const google::protobuf::Reflection*        refl_;
  std::shared_ptr<google::protobuf::Message> msg_;
  QTimer                                     hide_edited_timer_;

  // NOLINTNEXTLINE
 private slots:
  void HideAllEdit();
  void SaveConfig();

 protected:
  void closeEvent(QCloseEvent* event) override;
};
