#include "adapter.h"

namespace s21 {
std::pair<double *, unsigned *> Adapter::convert(Model *model,
                                                 std::string filename) {
  model->parse(filename);
  return model->getArr();
}
}  // namespace s21
