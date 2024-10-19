#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->scale_slider->setSliderPosition(50);
  ui->scale_line_edit->setText("50");
  ui->x_move->setText("0");
  ui->y_move->setText("0");
  ui->z_move->setText("0");
  ui->x_rotate->setText("0");
  ui->y_rotate->setText("0");
  ui->z_rotate->setText("0");
  ui->x_move_slider->setSliderPosition(0);
  ui->y_move_slider->setSliderPosition(0);
  ui->z_move_slider->setSliderPosition(0);
  ui->x_rotate_slider->setSliderPosition(0);
  ui->y_rotate_slider->setSliderPosition(0);
  ui->z_rotate_slider->setSliderPosition(0);
  previous_value_slider_x_ = 0;
  previous_value_slider_y_ = 0;
  previous_value_slider_z_ = 0;
  previous_value_rotate_x_ = 0;
  previous_value_rotate_y_ = 0;
  previous_value_rotate_z_ = 0;
  previous_scale_ = 50.0;
}

MainWindow::~MainWindow() {
  delete ui;
  delete timer_;
  delete frame_;
  delete gif_;
}

void MainWindow::get_position(int x) {
  ui->label_vertex->setText(QString::number(x));
}

void MainWindow::on_EditFile_clicked() {
  QString str =
      QFileDialog::getOpenFileName(this, "Open file", "/Users/", "*.obj");
  ui->filepath->setText(str);
  std::string v_str = str.toStdString();
  ui->widget->res = s21::Singleton::instance()->GetController()->getPair(v_str);
  ui->widget->size =
      s21::Singleton::instance()->GetController()->getModelSize();
  QString buf_line = QString::number(
      s21::Singleton::instance()->GetController()->getModelSize().second / 2 /
      2);
  ui->label_line->setText(buf_line);
  buf_line = QString::number(
      s21::Singleton::instance()->GetController()->getModelSize().first / 3);
  ui->label_vertex->setText(buf_line);
}

void MainWindow::on_scale_line_edit_returnPressed() {
  double value = ui->scale_line_edit->text().toDouble();
  if (ui->scale_line_edit->text().toDouble() <= 0) {
    value = 1;
  } else if (ui->scale_line_edit->text().toDouble() > 100) {
    value = 100;
  }
  ui->scale_line_edit->setText(QString::number(value));
  on_scale_slider_sliderMoved(value);
  ui->scale_slider->setValue(value);
  ui->widget->update();
}

void MainWindow::on_x_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->x_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->x_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->x_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_x_) * (M_PI / 45.0);
  previous_value_rotate_x_ = (int)value;
  ui->x_rotate_slider->setValue((int)value);
  char x = 'x';
  s21::Singleton::instance()->GetController()->rotateModel(radian, x);
  ui->widget->update();
}

void MainWindow::on_y_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->y_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->y_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->y_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_y_) * (M_PI / 45.0);
  previous_value_rotate_y_ = (int)value;
  ui->y_rotate_slider->setValue((int)value);
  char y = 'y';
  s21::Singleton::instance()->GetController()->rotateModel(radian, y);
  ui->widget->update();
}

void MainWindow::on_z_rotate_returnPressed() {
  ui->widget->scale = 1;
  double value = ui->z_rotate->text().toDouble();
  if (value > 100) {
    value = 100;
    ui->z_rotate->setText(QString::number(100));
  } else if (value < -100) {
    value = -100;
    ui->z_rotate->setText(QString::number(-100));
  }
  double radian = (value - previous_value_rotate_z_) * (M_PI / 45.0);
  previous_value_rotate_z_ = (int)value;
  ui->z_rotate_slider->setValue((int)value);
  char z = 'z';
  s21::Singleton::instance()->GetController()->rotateModel(radian, z);
  ui->widget->update();
}

void MainWindow::on_x_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->x_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->x_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->x_move->setText(QString::number(-100));
  }
  s21::Singleton::instance()->GetController()->moveModel(
      (a - previous_value_slider_x_) * 0.01, 'x');
  previous_value_slider_x_ = (int)a;
  ui->x_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_y_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->y_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->y_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->y_move->setText(QString::number(-100));
  }
  s21::Singleton::instance()->GetController()->moveModel(
      (a - previous_value_slider_y_) * 0.01, 'y');
  previous_value_slider_y_ = (int)a;
  ui->y_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_z_move_returnPressed() {
  ui->widget->scale = 1;
  double a = ui->z_move->text().toDouble();
  if (a > 100) {
    a = 100;
    ui->z_move->setText(QString::number(100));
  } else if (a < -100) {
    a = -100;
    ui->z_move->setText(QString::number(-100));
  }
  s21::Singleton::instance()->GetController()->moveModel(
      (a - previous_value_slider_z_) * 0.01, 'z');
  previous_value_rotate_z_ = (int)a;
  ui->z_move_slider->setValue((int)a);
  ui->widget->update();
}

void MainWindow::on_backgroundcolor_clicked() {
  ui->widget->background_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_2_sliderReleased() {}

void MainWindow::on_comboBox_3_activated(int index) {
  ui->widget->scale = 1;
  if (index == 0) {
    ui->widget->striple = 0;
  } else {
    ui->widget->striple = 1;
  }
  ui->widget->update();
}

void MainWindow::on_scale_slider_sliderMoved(int position) {
  if ((position - previous_scale_) < 0) {
    for (int i = 0; i < previous_scale_ - position; i++) {
      s21::Singleton::instance()->GetController()->setModelScale(0.9);
      ui->widget->update();
    }

    previous_scale_ = position;

  } else if ((position - previous_scale_) > 0) {
    for (int i = 0; i < position - previous_scale_; i++) {
      s21::Singleton::instance()->GetController()->setModelScale(1.1111);
      ui->widget->update();
    }
    previous_scale_ = position;
  }
  ui->scale_line_edit->setText(QString::number(position));
}

void MainWindow::on_Color_of_line_clicked() {
  ui->widget->line_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_parallel_pro_clicked() {
  ui->widget->proection = 0;
  ui->widget->update();
}

void MainWindow::on_central_pro_clicked() {
  ui->widget->proection = 1;
  ui->widget->update();
}

void MainWindow::on_color_points_but_clicked() {
  ui->widget->points_color =
      QColorDialog::getColor(Qt::white, this, tr("Select Color"));
  ui->widget->update();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position) {
  ui->widget->point_thickness = position;
  ui->widget->update();
}

void MainWindow::on_reset_clicked() {
  QString str = ui->filepath->text();
  std::string v_str = str.toStdString();
  ui->widget->res = s21::Singleton::instance()->GetController()->getPair(v_str);
  ui->widget->size =
      s21::Singleton::instance()->GetController()->getModelSize();
  QString buf_line = QString::number(
      s21::Singleton::instance()->GetController()->getModelSize().second / 2 /
      2);
  ui->label_line->setText(buf_line);
  buf_line = QString::number(
      s21::Singleton::instance()->GetController()->getModelSize().first / 3);
  ui->label_vertex->setText(buf_line);
  ui->scale_slider->setValue(50);
  ui->scale_line_edit->setText(QString::number(50));
  previous_scale_ = 50;
  previous_value_rotate_x_ = 0;
  previous_value_rotate_y_ = 0;
  previous_value_rotate_z_ = 0;
  previous_value_slider_x_ = 0;
  previous_value_slider_y_ = 0;
  previous_value_slider_z_ = 0;
  ui->x_move_slider->setValue(0);
  ui->y_move_slider->setValue(0);
  ui->z_move_slider->setValue(0);
  ui->x_rotate_slider->setValue(0);
  ui->y_rotate_slider->setValue(0);
  ui->z_rotate_slider->setValue(0);
  ui->x_move->setText(QString::number(0));
  ui->y_move->setText(QString::number(0));
  ui->z_move->setText(QString::number(0));
  ui->x_rotate->setText(QString::number(0));
  ui->y_rotate->setText(QString::number(0));
  ui->z_rotate->setText(QString::number(0));
  ui->widget->xRot_mo = 0;
  ui->widget->yRot_mo = 0;

  ui->widget->update();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  ui->widget->scale = 1;
  ui->widget->thickness = value;
  ui->widget->update();
}

void MainWindow::on_x_move_slider_valueChanged(int value) {
  s21::Singleton::instance()->GetController()->moveModel(
      (value - previous_value_slider_x_) * 0.01, 'x');
  ui->x_move->setText(QString::number(value));
  previous_value_slider_x_ = value;
  ui->widget->update();
}

void MainWindow::on_y_move_slider_valueChanged(int value) {
  s21::Singleton::instance()->GetController()->moveModel(
      (value - previous_value_slider_y_) * 0.01, 'y');
  ui->y_move->setText(QString::number(value));
  previous_value_slider_y_ = value;
  ui->widget->update();
}

void MainWindow::on_z_move_slider_valueChanged(int value) {
  s21::Singleton::instance()->GetController()->moveModel(
      (value - previous_value_slider_z_) * 0.01, 'z');
  ui->z_move->setText(QString::number(value));
  previous_value_slider_z_ = value;
  ui->widget->update();
}

void MainWindow::on_x_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_x_) * (M_PI / 45.0);
  s21::Singleton::instance()->GetController()->rotateModel(radian, 'x');
  ui->x_rotate->setText(QString::number(value));
  previous_value_rotate_x_ = value;
  ui->widget->update();
}

void MainWindow::on_y_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_y_) * (M_PI / 45.0);
  s21::Singleton::instance()->GetController()->rotateModel(radian, 'y');
  ui->y_rotate->setText(QString::number(value));
  previous_value_rotate_y_ = value;
  ui->widget->update();
}

void MainWindow::on_z_rotate_slider_valueChanged(int value) {
  double radian = (value - previous_value_rotate_z_) * (M_PI / 45.0);
  s21::Singleton::instance()->GetController()->rotateModel(radian, 'z');
  ui->z_rotate->setText(QString::number(value));
  previous_value_rotate_z_ = value;
  ui->widget->update();
}

void MainWindow::on_Choice_points_activated(int index) {
  double buf_scale = ui->widget->scale;
  ui->widget->scale = 1;
  ui->widget->form_points = index;
  ui->widget->update();
  ui->widget->scale = buf_scale;
}

// void MainWindow::on_pushButton_4_clicked() {
//   if (!ui->filepath->text().isEmpty()) {
//     int option = ui->comboBox_2->currentIndex();
//     frame_ = new QImage;
//     if (option == 2) {
//       gif_ = new QGifImage;
//       timer_ = new QTimer(this);
//       time_ = 0;
//       connect(timer_, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
//       ui->pushButton_4->setDisabled(true);
//       timer_->start(10);
//     } else if (option == 1) {
//       *frame_ = ui->widget->grabFramebuffer();
//       QString img =
//           QFileDialog::getSaveFileName(this, NULL, NULL, "BPM (*.bmp)");
//       frame_->save(img);
//     } else if (option == 0) {
//       *frame_ = ui->widget->grab().toImage();
//       QString img =
//           QFileDialog::getSaveFileName(this, NULL, NULL, "JPEG (*.jpeg)");
//       frame_->save(img);
//     }
//   }
// }
void MainWindow::on_pushButton_saveGif_clicked() {
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(captureFrame()));
  timer->start(100);  // Устанавливаем интервал таймера (в миллисекундах) для
                      // захвата кадров
  //            elapsedTimer.start();
  gif.clear();

  currentFrameIndex = 0;
}

void MainWindow::captureFrame() {
  // Если прошло менее 5 секунд, продолжаем создавать кадры и сохранять их
  if (gif.length() < 50) {
    QPixmap pixmap = centralWidget()->grab();
    // readyGif.addFrame(pixmap.toImage(), 100);

    gif.append(pixmap.toImage());
    std::cout << currentFrameIndex << std::endl;
    currentFrameIndex++;
  } else {
    timer->stop();
    // disconnect(timer);
    for (int i = 0; i < 50; readyGif.addFrame(gif[i++], 100)) {
    }
    QString filePath =
        QFileDialog::getSaveFileName(0, "Сохранить файл как", "", "*.gif");

    if (filePath != nullptr) {
      readyGif.save(filePath);
      std::cout << "GIF Image was saved" << std::endl;
    } else {
      std::cout << "Pathh wwasn not choosen" << std::endl;
    }
  }
}

void MainWindow::on_pushButton_4_clicked() {
  QPixmap imageToSave = ui->widget->grab();
  QImage image = imageToSave.toImage();

  QString imagePath = QFileDialog::getSaveFileName(
      this, tr("Save Image"), "", tr("JPEG (*.jpg *.jpeg);;BMP (*.bmp)"));

  if (imagePath.isEmpty()) return;

  qDebug() << "Путь к файлу сохранения изображения:" << imagePath;

  QString format = QFileInfo(imagePath).suffix().toLower();
  qDebug() << "Формат изображения:" << format;

  if (format != "jpg" && format != "jpeg" && format != "bmp") {
    qDebug() << "Неверный формат изображения";
    QMessageBox::information(
        nullptr, "Ошибка",
        "Можно сохранить изображение только в форматах JPEG и BMP");
    return;
  }

  QImageWriter writer(imagePath);
  if (!format.isEmpty()) writer.setFormat(format.toLatin1());

  if (!writer.canWrite()) {
    qDebug() << "Не удалось записать изображение";
    QMessageBox::information(nullptr, "Ошибка",
                             "Не удалось сохранить изображение\nПопробуйте "
                             "добавить в название файла его разрешение");
    return;
  }

  if (!writer.write(image)) {
    qDebug() << "Не удалось сохранить изображение";
    return;
  }

  QMessageBox::information(nullptr, "Успех", "Изображение успешно сохранено");
  qDebug() << "Изображение успешно сохранено";
}

void MainWindow::LoadSetting() {
  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  ui->widget->save_set = settings.value("save_save_set").toFloat();
  if (ui->widget->save_set == 1) {
    ui->widget->background_color.setRedF(
        settings.value("save_Color_redF").toFloat());
    ui->widget->background_color.setGreenF(
        settings.value("save_Color_greenF").toFloat());
    ui->widget->background_color.setBlueF(
        settings.value("save_Color_blueF").toFloat());

    ui->widget->points_color.setRedF(
        settings.value("save_Color_point_redF").toFloat());
    ui->widget->points_color.setGreenF(
        settings.value("save_Color_point_greenF").toFloat());
    ui->widget->points_color.setBlueF(
        settings.value("save_Color_point_blueF").toFloat());

    ui->widget->line_color.setRedF(
        settings.value("save_Color_line_redF").toFloat());
    ui->widget->line_color.setGreenF(
        settings.value("save_Color_line_greenF").toFloat());
    ui->widget->line_color.setBlueF(
        settings.value("save_Color_line_blueF").toFloat());

    ui->widget->striple = settings.value("save_line_style").toInt();
    ui->comboBox_3->setCurrentIndex(ui->widget->striple);

    ui->widget->form_points = settings.value("save_points_style").toInt();
    ui->Choice_points->setCurrentIndex(ui->widget->form_points);

    ui->widget->thickness = settings.value("save_line_thickness").toDouble();
    ui->horizontalSlider_2->setValue(
        (int)(settings.value("save_line_thickness").toDouble()));

    ui->widget->point_thickness =
        settings.value("save_point_thickness").toDouble();
    ui->horizontalSlider->setValue(
        (int)(settings.value("save_point_thickness").toDouble()));

    if ((int)settings.value("save_proection").toDouble()) {
      ui->central_pro->setChecked(1);
      ui->widget->proection = 1;
    } else {
      ui->widget->proection = 0;
    }

    settings.endGroup();
  }
}

void MainWindow::on_Save_set_clicked() {
  ui->widget->save_set = 1;

  QSettings settings("settings.ini", QSettings::IniFormat);
  settings.beginGroup("Settings");

  settings.setValue("save_save_set", ui->widget->save_set);

  settings.setValue("save_Color_redF", ui->widget->background_color.redF());
  settings.setValue("save_Color_greenF", ui->widget->background_color.greenF());
  settings.setValue("save_Color_blueF", ui->widget->background_color.blueF());

  settings.setValue("save_Color_point_redF", ui->widget->points_color.redF());
  settings.setValue("save_Color_point_greenF",
                    ui->widget->points_color.greenF());
  settings.setValue("save_Color_point_blueF", ui->widget->points_color.blueF());

  settings.setValue("save_Color_line_redF", ui->widget->line_color.redF());
  settings.setValue("save_Color_line_greenF", ui->widget->line_color.greenF());
  settings.setValue("save_Color_line_blueF", ui->widget->line_color.blueF());

  settings.setValue("save_line_style", ui->widget->striple);

  settings.setValue("save_points_style", ui->widget->form_points);

  settings.setValue("save_line_thickness", ui->widget->thickness);
  printf("save line_thickness = %lf", ui->widget->thickness);

  settings.setValue("save_point_thickness", ui->widget->point_thickness);

  settings.setValue("save_proection", ui->widget->proection);

  settings.endGroup();
}

void MainWindow::on_load_set_but_clicked() {
  LoadSetting();
  ui->widget->update();
}
