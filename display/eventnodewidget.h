#pragma once

#include <proto/ClassInfo.pb.h>

namespace Ui {
class EventNodeWidget;
}

class EventNodeWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit EventNodeWidget(const class_system::ClassInfo::Event &event, QWidget *parent = nullptr);
  ~EventNodeWidget() final;

 private:
  std::unique_ptr<Ui::EventNodeWidget> ui_;
};
