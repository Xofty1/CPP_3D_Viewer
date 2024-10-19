#include "controller.h"

namespace s21 {
std::pair<double *, unsigned *> Controller::getPair(std::string filename) {
  return adapter_->convert(model_, filename);
}
std::pair<unsigned, unsigned> Controller::getModelSize() {
  return model_->getSize();
}
void Controller::rotateModel(double angle, char axis) {
  facade_->rotateModel(model_, angle, axis);
}
void Controller::moveModel(double value, char axis) {
  facade_->moveModel(model_, value, axis);
}
void Controller::setModelScale(double scale) { model_->setScale(scale); }
}  // namespace s21
