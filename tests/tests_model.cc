#include <gtest/gtest.h>

#include <fstream>

#include "../Model/model.h"

namespace s21 {

// Вспомогательный метод для создания тестового OBJ файла
void CreateTestOBJFile(const std::string &filename) {
  std::ofstream obj_file(filename);
  obj_file << "v 1.0 1.0 1.0\n"
           << "v -1.0 -1.0 -1.0\n"
           << "f 1 2\n";
  obj_file.close();
}

class ModelTest : public ::testing::Test {
 protected:
  Model model;
  void SetUp() override {
    // Создание тестового OBJ файла
    CreateTestOBJFile("test.obj");
  }

  void TearDown() override {
    // Удаление тестового файла после каждого теста
    remove("test.obj");
  }
};

// Тестирование метода parse (чтение правильного файла)
TEST_F(ModelTest, ParseValidFile) {
  model.parse("test.obj");

  // Проверка, что было загружено правильное количество вершин и полигонов
  ASSERT_EQ(model.getSize().first, 6);  // 2 вершины по 3 координаты = 6
  ASSERT_EQ(model.getSize().second, 4);  // 1 полигон (линия), 4 индекса
}

// Тестирование метода parse с несуществующим файлом
TEST_F(ModelTest, ParseInvalidFile) {
  // Попытка парсинга несуществующего файла не должна приводить к ошибкам
  ASSERT_NO_THROW(model.parse("invalid.obj"));

  // Должны остаться пустые векторы вершин и полигонов
  ASSERT_EQ(model.getSize().first, 0);
  ASSERT_EQ(model.getSize().second, 0);
}

// Тестирование вращения вокруг оси X
TEST_F(ModelTest, RotationXTest) {
  model.parse("test.obj");
  model.conv();

  model.rotationX(-M_PI / 2);  // Вращение на 90 градусов
  double *vertices = model.getVector();
  // После вращения вокруг оси X:
  // Первая вершина должна быть (1.0, -1.0, 1.0)
  ASSERT_NEAR(vertices[1], -1.0, 1e-6);  // Y координата должна стать -1.0
  ASSERT_NEAR(vertices[2], 1.0, 1e-6);  // Z координата должна остаться 1.0
}

// Тестирование вращения вокруг оси Y
TEST_F(ModelTest, RotationYTest) {
  model.parse("test.obj");
  model.conv();
  model.rotationY(M_PI / 2);  // Вращение на 90 градусов

  double *vertices = model.getVector();
  // После вращения вокруг оси Y:
  // Первая вершина должна быть (1.0, 1.0, -1.0)
  ASSERT_NEAR(vertices[0], 1.0, 1e-6);  // X координата остаётся 1.0
  ASSERT_NEAR(vertices[2], -1.0, 1e-6);  // Z координата должна стать -1.0
}

// Тестирование вращения вокруг оси Z
TEST_F(ModelTest, RotationZTest) {
  model.parse("test.obj");
  model.conv();
  model.rotationZ(M_PI / 2);  // Вращение на 90 градусов

  // auto vertices = model.getArr().first;
  double *vertices = model.getVector();
  // После вращения вокруг оси Z:
  // Первая вершина должна быть (-1.0, 1.0, 1.0)
  ASSERT_NEAR(vertices[0], -1.0, 1e-6);  // X координата должна стать -1.0
  ASSERT_NEAR(vertices[1], 1.0, 1e-6);  // Y координата остаётся 1.0
}

// Тестирование метода setToMid
TEST_F(ModelTest, SetToMidTest) {
  model.parse("test.obj");
  model.conv();
  model.setToMid();

  // auto vertices = model.getArr().first;

  double *vertices = model.getVector();
  // После центровки первая вершина должна оказаться на координатах (0.0, 0.0,
  // 0.0)
  ASSERT_NEAR(vertices[0], 1.0, 1e-6);  // X координата первой вершины
  ASSERT_NEAR(vertices[1], 1.0, 1e-6);  // Y координата первой вершины
  ASSERT_NEAR(vertices[2], 1.0, 1e-6);  // Z координата первой вершины
}

// Тестирование метода normalize (нормализация модели)
TEST_F(ModelTest, NormalizeTest) {
  model.parse("test.obj");
  model.conv();
  double scale = model.normalize();

  // Проверяем, что масштаб нормализации корректен и находится в пределах от 0
  // до 1
  ASSERT_GT(scale, 0.0);
  ASSERT_LT(scale, 1.0);
}

// Тестирование метода setScale
TEST_F(ModelTest, SetScaleTest) {
  model.parse("test.obj");
  model.conv();
  model.setScale(2.0);  // Масштабирование в 2 раза

  // auto vertices = model.getArr().first;
  double *vertices = model.getVector();
  // Первая вершина должна быть (2.0, 2.0, 2.0) после масштабирования
  ASSERT_NEAR(vertices[0], 2.0, 1e-6);  // X координата первой вершины
  ASSERT_NEAR(vertices[1], 2.0, 1e-6);  // Y координата первой вершины
  ASSERT_NEAR(vertices[2], 2.0, 1e-6);  // Z координата первой вершины
}

// Тестирование метода move
TEST_F(ModelTest, MoveTest) {
  model.parse("test.obj");
  model.conv();
  model.move(1.0, 0);  // Сдвиг по оси X на 1

  // auto vertices = model.getArr().first;
  double *vertices = model.getVector();
  // Первая вершина должна быть (2.0, 1.0, 1.0) после сдвига
  ASSERT_NEAR(vertices[0], 2.0,
              1e-6);  // X координата первой вершины увеличивается на 1
}

// Тестирование метода getArr (получение массивов вершин и полигонов)
TEST_F(ModelTest, GetArrTest) {
  model.parse("test.obj");
  model.conv();
  auto arrays = model.getArr();

  // Проверка на то, что массивы не пустые
  ASSERT_NE(arrays.first, nullptr);   // Массив вершин
  ASSERT_NE(arrays.second, nullptr);  // Массив полигонов

  // Проверка количества элементов в массивах
  ASSERT_EQ(model.getSize().first, 6);  // 2 вершины, каждая по 3 координаты
  ASSERT_EQ(model.getSize().second, 4);  // 1 полигон (линия) с 4 индексами
}

// Тестирование метода getSize (получение размеров массивов)
TEST_F(ModelTest, GetSizeTest) {
  model.parse("test.obj");
  model.conv();
  auto sizes = model.getSize();

  // Проверяем правильность размера массивов
  ASSERT_EQ(sizes.first, 6);  // Количество координат вершин
  ASSERT_EQ(sizes.second, 4);  // Количество индексов полигонов
}

}  // namespace s21
