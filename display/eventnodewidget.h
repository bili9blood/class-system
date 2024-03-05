#pragma once
#include "globalstore.h"

namespace Ui {
class EventNodeWidget;
}

class EventNodeWidget final : public QWidget {
  Q_OBJECT
 public:
  explicit EventNodeWidget(const GlobalStore::Event &event, QWidget *parent = nullptr);
  ~EventNodeWidget() final;

 private:
  std::unique_ptr<Ui::EventNodeWidget> ui_;
};
