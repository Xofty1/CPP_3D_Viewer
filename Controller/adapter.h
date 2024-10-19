#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <iostream>

#include "../Model/model.h"

namespace s21 {
class Adapter {
 public:
  std::pair<double *, unsigned *> convert(Model *model, std::string filename);
};
}  // namespace s21

#endif  // CONTROLLER_ADAPTER_H_
