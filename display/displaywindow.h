#pragma once
#include <proto/Response.pb.h>
#include <qmainwindow.h>

namespace Ui {
class DisplayWindow;
}

class DisplayWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit DisplayWindow(QWidget *parent = nullptr);
  ~DisplayWindow() override;

 public slots:
  void HandleSucceesfulResp(const class_system::Response &resp);

 protected:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void closeEvent(QCloseEvent *event) override;

 private:
  std::unique_ptr<Ui::DisplayWindow> ui_;
  QPoint                             mouse_start_pos_;
};
