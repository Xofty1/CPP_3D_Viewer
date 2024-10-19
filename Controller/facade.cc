#include "facade.h"

namespace s21 {
void Facade::rotateModel(Model *model, double angle, char axis) {
  if (axis == 'x')
    model->rotationX(angle);
  else if (axis == 'y')
    model->rotationY(angle);
  else if (axis == 'z')
    model->rotationZ(angle);
}
void Facade::moveModel(Model *model, double value, char axis) {
  if (axis == 'x')
    model->move(value, 0U);
  else if (axis == 'y')
    model->move(value, 1U);
  else if (axis == 'z')
    model->move(value, 2U);
}
}  // namespace s21
