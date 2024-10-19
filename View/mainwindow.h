#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QColorDialog>
#include <QFileDialog>
#include <QFrame>
#include <QImageWriter>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>

#include "../Controller/singleton.h"
#include "../QtGifimage/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 public slots:
  void get_position(int x);

 private slots:

  void on_EditFile_clicked();

  void on_scale_line_edit_returnPressed();

  void on_x_rotate_returnPressed();

  void on_y_rotate_returnPressed();

  void on_z_rotate_returnPressed();

  void on_x_move_returnPressed();

  void on_y_move_returnPressed();

  void on_z_move_returnPressed();

  void on_backgroundcolor_clicked();

  void on_horizontalSlider_2_sliderReleased();

  void on_comboBox_3_activated(int index);

  void on_scale_slider_sliderMoved(int position);

  void on_Save_set_clicked();

  void on_Color_of_line_clicked();

  void on_parallel_pro_clicked();

  void on_central_pro_clicked();

  void on_color_points_but_clicked();

  void on_horizontalSlider_sliderMoved(int position);

  void on_reset_clicked();

  void on_horizontalSlider_2_valueChanged(int value);

  void on_x_move_slider_valueChanged(int value);

  void on_y_move_slider_valueChanged(int value);

  void on_z_move_slider_valueChanged(int value);

  void on_x_rotate_slider_valueChanged(int value);

  void on_y_rotate_slider_valueChanged(int value);

  void on_z_rotate_slider_valueChanged(int value);

  void on_Choice_points_activated(int index);

  void on_pushButton_4_clicked();
  void on_pushButton_saveGif_clicked();

  void captureFrame();
  void LoadSetting();

  void on_load_set_but_clicked();

 private:
  QGifImage readyGif;
  QTimer *timer;
  QList<QImage> gif;
  int currentFrameIndex = 0;
  int previous_value_slider_x_;
  int previous_value_slider_y_;
  int previous_value_slider_z_;
  QTimer *timer_;
  QGifImage *gif_;
  QImage *frame_;
  QString gif_save_path_;
  int time_;
  int previous_value_rotate_x_;
  int previous_value_rotate_y_;
  int previous_value_rotate_z_;
  Ui::MainWindow *ui;
  double previous_scale_;
};
#endif  // VIEW_MAINWINDOW_H_
