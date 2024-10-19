#ifndef FACADE_H_
#define FACADE_H_

#include "../Model/model.h"

namespace s21 {
class Facade {
 public:
  void rotateModel(Model *model, double angle, char axis);
  void moveModel(Model *model, double value, char axis);
};
}  // namespace s21

#endif  // CONTROLLER_FACADE_H_
