#ifndef MYOPENGL_H_
#define MYOPENGL_H_

#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QMoveEvent>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QThread>

#include "View/mainwindow.h"

class Myopengl : public QOpenGLWidget, public QOpenGLFunctions {
 public:
  Myopengl(QWidget *parent = nullptr);
  ~Myopengl() {}
  QColor background_color = QColorConstants::Black;
  QColor points_color = QColorConstants::White;
  QColor line_color = QColorConstants::White;
  std::pair<double *, unsigned *> res;
  std::pair<unsigned, unsigned> size;
  double scale = 1;
  double point_thickness = 0;
  int striple = 0;
  int proection = 0;
  int form_points = 0;
  int save_set = 0;
  double thickness = 1;
  double xRot_mo = 0;
  double yRot_mo = 0;

 protected:
  void pointSet();
  void stripleSet();
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  QPoint mPos;
};

#endif  // MYOPENGL_H_
