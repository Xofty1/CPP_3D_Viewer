#ifndef MODEL_H_
#define MODEL_H_

#include <locale.h>

#include <cmath>
#include <cstring>
#include <fstream>
#include <vector>

/*! \mainpage 3DViewer_v2.0 Documentation
 *
 * \section Project Description
 * There is an implementation of a program to visualise the 3D wireframe models.
 * The program is developed in C++ language of C++17 standard
 * and implemented using the MVC pattern.
 *
 * The program provides the ability to:\n
 * 1) load a wireframe model from an obj file;\n
 * 2) translate the model by a given distance in relation to the X, Y, Z axes;\n
 * 3) rotate the model by a given angle in relation to its X, Y, Z axes;\n
 * 4) scale the model by a given value.\n\n
 *
 * Graphical user interface contains:\n
 * 1) button to select the model file and a field to output its name;\n
 * 2) visualisation area for the wireframe model;\n
 * 3) button and input field for translating the model;\n
 * 4) button and input field for rotating the model;\n
 * 5) button and input field for scaling the model.\n\n
 *
 * The program allows customizing the type of projection (parallel and central),
 * setting up the type (solid, dashed), color and thickness of the edges,
 * display method (none, circle, square), color and size of the vertices.
 * It also allows choosing the background color.
 * Settings is saved between program restarts.
 *
 * The program allows saving the captured (rendered) images as bmp and jpeg
 * files and recording small screencast by a special button.
 *
 * \section Commands
 * Run "make" or "make all" to build the application.\n
 * Run "make install" to install the application on your PC.\n
 * Run "make uninstall" to uninstall the application.\n
 * Run "make dvi" to get this documentation.\n
 * Run "make dist" to archive the application.\n
 * Run "make tests" to run the tests.\n
 */
namespace s21 {
class Model {
 public:
  /// @brief Main function of parsing obj file and make
  /// @param filename name obj file
  /// @return error
  void parse(std ::string filename);
  /// @brief function for parse coordinates point
  /// @param ptr pointer for current line
  void parseVertex(char *ptr);
  /// @brief function for parse polygons
  /// @param ptr pointer for current line
  void parsePolygons(char *ptr);
  /// @brief function for find max and min coordinates of all axis
  /// @param counter_axis counter of current axis
  /// @param coord current coordinate
  void minMaxCords(int counter_axis, double coord);
  /// @brief function find coefficient for normalize value  coordinate points to
  /// -1 / 1
  /// @return coefficient
  double normalize();
  /// @brief function for setting model on center of widget
  void setToMid();
  /// @brief function for multiplication coordinates point on necessary
  /// coefficient of scale
  /// @param scale scale
  void setScale(double scale);
  /// @brief function for rotation along the axis x on necessary angle
  /// @param angle
  void rotationX(double angle);
  /// @brief function for rotation along the axis y on necessary angle
  /// @param angle
  void rotationY(double angle);
  /// @brief function for rotation along the axis z on necessary angle
  /// @param angle
  void rotationZ(double angle);
  /// @brief function for moving model on necessary coefficient along the axis
  /// @param a coefficient
  /// @param i axis
  void move(double a, unsigned i);
  /// @brief Getter for array vertex and poligons
  /// @return pair of array
  std::pair<double *, unsigned *> getArr();
  /// @brief function for convert vectors to arrays
  void conv();
  /// @brief Getter for size of arrays
  /// @return pair size
  std::pair<unsigned, unsigned> getSize();
  double *getVector() { return vertex_; }
  Model() = default;

  ~Model() {
    delete[] vertex_;
    delete[] polygons_;
  }

 private:
  std::vector<double> vertex_vector_;
  std::vector<unsigned> polygons_vector_;
  double *vertex_ = nullptr;
  unsigned *polygons_ = nullptr;
  double minmaxX_[2] = {0};
  double minmaxY_[2] = {0};
  double minmaxZ_[2] = {0};
};
}  // namespace s21

#endif  // MODEL_MODEL_H_
