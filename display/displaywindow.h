#pragma once
#include <proto/Response.pb.h>
#include <qmainwindow.h>
#include <qtimer.h>

#include <queue>

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
  std::unique_ptr<Ui::DisplayWindow>         ui_;
  QPoint                                     mouse_start_pos_;

  class_system::ClassInfo                    class_info_;
  std::queue<class_system::Sentence>         sentences_;

  QTimer                                     clock_timer_;
  QTimer                                     sentences_notices_switch_timer_;

  void                                       UpdateLessonsClass();

 private slots:
  void HandleClockTick();
  void HandleSwitchSentences();
  void HandleSwitchNotices();
};
