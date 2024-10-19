#include "model.h"

namespace s21 {

void Model::parse(std::string filename) {
  // setlocale(LC_ALL, "en-US");
  setlocale(LC_NUMERIC, "C");
  if (!vertex_vector_.empty()) {
    vertex_vector_.clear();
  }
  if (!polygons_vector_.empty()) {
    polygons_vector_.clear();
  }
  std::string line;
  std::ifstream file(filename);
  if (file) {
    minmaxX_[0] = 0;
    minmaxX_[1] = 0;
    minmaxY_[0] = 0;
    minmaxY_[1] = 0;
    minmaxZ_[0] = 0;
    minmaxZ_[1] = 0;
    char *ptr = nullptr;
    while (getline(file, line)) {
      ptr = const_cast<char *>(line.c_str());
      if (*ptr == 'v') {
        parseVertex(ptr);
      } else if (*ptr == 'f') {
        parsePolygons(ptr);
      }
    }
    file.close();
  }
}

void Model::parseVertex(char *ptr) {
  int counter_axis = 0;
  ptr++;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr) && *ptr != '-') {
        ptr++;
      } else {
        vertex_vector_.push_back(strtod(ptr, &ptr));
        minMaxCords(counter_axis, vertex_vector_.back());
        counter_axis++;
        while (*ptr == ' ') {
          ptr++;
        }
      }
    }
  }
}

void Model::parsePolygons(char *ptr) {
  ptr++;
  int counter_first_pol = 0, first_polygon = 0, tmp_pol = 0;
  if (*ptr == ' ') {
    while (*ptr != '\0') {
      if (!isdigit(*ptr)) {
        ptr++;
      } else {
        if (counter_first_pol == 0) {
          polygons_vector_.push_back(strtol(ptr, &ptr, 0) - 1);
          first_polygon = polygons_vector_.back();
          counter_first_pol++;
        } else {
          tmp_pol = strtol(ptr, &ptr, 0) - 1;
          polygons_vector_.push_back(tmp_pol);
          polygons_vector_.push_back(tmp_pol);
        }
        while (*ptr != '\0' && *ptr != ' ') {
          ptr++;
        }
      }
    }
  }
  polygons_vector_.push_back(first_polygon);
}

void Model::minMaxCords(int counter_axis, double coord) {
  if (counter_axis == 0) {
    if (minmaxX_[0] > coord) {
      minmaxX_[0] = coord;
    }
    if (minmaxX_[1] < coord) {
      minmaxX_[1] = coord;
    }
  } else if (counter_axis == 1) {
    if (minmaxY_[0] > coord) {
      minmaxY_[0] = coord;
    }
    if (minmaxY_[1] < coord) {
      minmaxY_[1] = coord;
    }
  } else if (counter_axis == 2) {
    if (minmaxZ_[0] > coord) {
      minmaxZ_[0] = coord;
    }
    if (minmaxZ_[1] < coord) {
      minmaxZ_[1] = coord;
    }
  }
}

void Model::rotationX(double angle) {
  for (unsigned i = 0; i < vertex_vector_.size(); i += 3) {
    double temp_y = vertex_[i + 1];
    double temp_z = vertex_[i + 2];
    vertex_[i + 1] = cos(angle) * temp_y + sin(angle) * temp_z;
    vertex_[i + 2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void Model::rotationY(double angle) {
  for (unsigned i = 0; i < vertex_vector_.size(); i += 3) {
    double temp_x = vertex_[i];
    double temp_z = vertex_[i + 2];
    vertex_[i] = cos(angle) * temp_x + sin(angle) * temp_z;
    vertex_[i + 2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void Model::rotationZ(double angle) {
  for (unsigned i = 0; i < vertex_vector_.size(); i += 3) {
    double temp_x = vertex_[i];
    double temp_y = vertex_[i + 1];
    vertex_[i] = cos(angle) * temp_x - sin(angle) * temp_y;
    vertex_[i + 1] = sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

void Model::setToMid() {
  double centX = minmaxX_[0] + (minmaxX_[1] - minmaxX_[0]) / 2;
  double centY = minmaxY_[0] + (minmaxY_[1] - minmaxY_[0]) / 2;
  double centZ = minmaxZ_[0] + (minmaxZ_[1] - minmaxZ_[0]) / 2;
  for (unsigned i = 0; i < vertex_vector_.size(); i += 3) {
    vertex_[i] -= centX;
    vertex_[i + 1] -= centY;
    vertex_[i + 2] -= centZ;
  }
}
void Model::setScale(double scale) {
  for (unsigned i = 0; i < vertex_vector_.size(); i++) {
    vertex_[i] *= scale;
  }
}

void Model::move(double a, unsigned i) {
  for (; i < vertex_vector_.size(); i += 3) {
    vertex_[i] += a;
  }
}

double Model::normalize() {
  double x = minmaxX_[1] - minmaxX_[0];
  double y = minmaxY_[1] - minmaxY_[0];
  double z = minmaxZ_[1] - minmaxZ_[0];
  double d = fmax(fmax(x, y), z);
  double value = 0.5;
  double scale = (value - (value * (-1))) / d;
  return scale;
}
void Model::conv() {
  if (vertex_ != nullptr) {
    delete[] vertex_;
    vertex_ = nullptr;
  }
  if (polygons_ != nullptr) {
    delete[] polygons_;
    polygons_ = nullptr;
  }
  vertex_ = new double[vertex_vector_.size()]();
  int i = 0;
  for (auto it : vertex_vector_) {
    vertex_[i] = it;
    i++;
  }
  polygons_ = new unsigned[polygons_vector_.size()]();
  int j = 0;
  for (auto it : polygons_vector_) {
    polygons_[j] = it;
    j++;
  }
}

std::pair<double *, unsigned *> Model::getArr() {
  conv();
  setToMid();
  double scale = normalize();
  setScale(scale);

  return std::pair<double *, unsigned *>(vertex_, polygons_);
}
std::pair<unsigned, unsigned> Model::getSize() {
  return std::pair<unsigned, unsigned>(vertex_vector_.size(),
                                       polygons_vector_.size());
}
}  // namespace s21
