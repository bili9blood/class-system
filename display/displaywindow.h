#pragma once
#include <qmainwindow.h>
#include <qtimer.h>
#include <queue>
#include "globalstore.h"

namespace Ui {
class DisplayWindow;
}

class DisplayWindow final : public QMainWindow {
  Q_OBJECT

  struct DailyArrangement {
    QString    job;
    QList<GlobalStore::Student> students;
  };

 public:
  explicit DisplayWindow(QWidget *parent = nullptr);
  ~DisplayWindow() final;

 public slots:
  void HandleClassInfo();

 private:
  std::unique_ptr<Ui::DisplayWindow>         ui_;
  QPoint                                     mouse_start_pos_;

  std::queue<GlobalStore::Sentence>         sentences_;

  QTimer                                     clock_timer_;
  QTimer                                     sentences_notices_switch_timer_;

  void                                       InitSentences(const QList<GlobalStore::Sentence> &sentences);
  QList<DailyArrangement>                    GetDailyArrangement();
  void                                       DisplayEvents();
  void                                       DisplayArrangement();
  void                                       DisplayLessons();
  void                                       DisplayWeather();
  void                                       UpdateLessonsStatus();
  void                                       UpdateWindowStatus();
  void                                       MoveCenter();
  void                                       SwitchWindowLayer(const bool &front);

  void                                       mousePressEvent(QMouseEvent *event) final;
  void                                       mouseMoveEvent(QMouseEvent *event) final;
  void                                       mouseReleaseEvent(QMouseEvent *event) final;
  bool                                       nativeEvent(const QByteArray &event_type, void *message, long *result) final;
  void                                       paintEvent(QPaintEvent *event) final;
  void                                       moveEvent(QMoveEvent *event) final;
  void                                       resizeEvent(QResizeEvent *event) final;
  void                                       closeEvent(QCloseEvent *event) final;

 private slots:
  void HandleClockTick();
  void HandleSwitchSentences();
  void HandleSwitchNotices();
};
