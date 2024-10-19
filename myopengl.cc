#include "myopengl.h"

Myopengl::Myopengl(QWidget *parent) : QOpenGLWidget{parent} {}

void Myopengl::initializeGL() {
  initializeOpenGLFunctions();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glTranslatef(0, 0, 0);
}
void Myopengl::resizeGL(int w, int h) {}

void Myopengl::paintGL() {
  glClearColor(background_color.redF(), background_color.greenF(),
               background_color.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();  // Reset the modelview matrix

  // Apply rotations
  glRotated(xRot_mo, 1, 0, 0);
  glRotated(yRot_mo, 0, 1, 0);

  // Apply projection
  if (proection == 1) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  } else {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glTranslatef(0, 0, 0);
  }

  // Draw elements
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(thickness);
  glVertexPointer(3, GL_DOUBLE, 0, res.first);
  glDrawElements(GL_LINES, size.second, GL_UNSIGNED_INT, res.second);
  stripleSet();

  if (form_points != 0) {
    pointSet();
    glDrawElements(GL_POINTS, size.second, GL_UNSIGNED_INT, res.second);
  }

  glDisableClientState(GL_VERTEX_ARRAY);
}

void Myopengl::mouseMoveEvent(QMouseEvent *mo) {
  // Calculate the difference in mouse position
  double dx = mo->pos().x() - mPos.x();
  double dy = mo->pos().y() - mPos.y();

  // Accumulate rotation changes
  xRot_mo += 1 / M_PI * dy;
  yRot_mo += 1 / M_PI * dx;

  // Update the last mouse position
  mPos = mo->pos();

  // Request a redraw
  update();
}

void Myopengl::mousePressEvent(QMouseEvent *mo) {
  scale = 1;
  mPos = mo->pos();
}

void Myopengl::stripleSet() {
  if (striple == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
}

void Myopengl::pointSet() {
  glColor3d(points_color.redF(), points_color.greenF(), points_color.blueF());
  glPointSize(point_thickness);  // Можно поменять на нужный размер
  if (form_points == 2) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
}
