#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "../Model/model.h"
#include "adapter.h"
#include "facade.h"

namespace s21 {
class Controller {
 public:
  Controller() { model_ = new Model; }
  ~Controller() { delete model_; }
  std::pair<double *, unsigned *> getPair(std::string filename);
  std::pair<unsigned, unsigned> getModelSize();
  void rotateModel(double angle, char axis);
  void moveModel(double value, char axis);
  void setModelScale(double scale);
  Model *GetModel() { return model_; }

 private:
  Model *model_;
  Adapter *adapter_;
  Facade *facade_;
};
}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H_
