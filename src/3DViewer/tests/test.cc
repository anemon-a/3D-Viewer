#define COMMON_TEST

#include <gtest/gtest.h>
#include <fstream>
#include "../controller/controller.h"

#define s21_EXP 1e-6

void CreateTestObjFile() {
  std::ofstream oFile ("tests/test.obj");
  oFile << "v 1.000000 -1.000000 -1.000000" << std::endl;
  oFile << "v 1.000000 -1.000000 1.000000" << std::endl;
  oFile << "v -1.000000 -1.000000 1.000000" << std::endl;
  oFile << "v -1.000000 -1.000000 -1.000000" << std::endl;
  oFile << "v 1.000000 1.000000 -1.000000" << std::endl;
  oFile << "v 1.000000 1.000000 1.000000" << std::endl;
  oFile << "v -1.000000 1.000000 1.000000" << std::endl;
  oFile << "v -1.000000 1.000000 -1.000000" << std::endl << std::endl;
  oFile << "f 1/4/1 2/1/1 4/3/1" << std::endl;
  oFile << "f 5/14/2 8/1/2 6/5/2" << std::endl;
  oFile << "f 1/12/3 5/6/3 2/8/3" << std::endl;
  oFile << "f 2/12/4 6/8/4 3/4/4" << std::endl;
  oFile << "f 4/13/5 3/9/5 8/11/5" << std::endl;
  oFile << "f 5/6/6 1/12/6 8/11/6" << std::endl;
  oFile << "f 2/1/1 3/2/1 4/3/1" << std::endl;
  oFile << "f 8/1/2 7/4/2 6/5/2" << std::endl;
  oFile << "f 5/6/3 6/7/3 2/8/3" << std::endl;
  oFile << "f 6/8/4 7/5/4 3/4/4" << std::endl;
  oFile << "f 3/9/5 7/10/5 8/11/5" << std::endl;
  oFile << "f 1/12/6 4/13/6 8/11/6" << std::endl;
}

void DeleteTestObjFile() {
  remove("tests/test.obj");
}

TEST(ParseFile, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  double* vertexes = controller.GetVertexPointer();
  ASSERT_NEAR(model.affine.GetCountOfFacets(), 12, s21_EXP);
  ASSERT_NEAR(model.affine.GetCountOfVertexes(), 8, s21_EXP);

  ASSERT_NEAR(vertexes[0], 1, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1, s21_EXP);
  ASSERT_NEAR(vertexes[2], -1, s21_EXP);

  ASSERT_NEAR(vertexes[3], 1, s21_EXP);
  ASSERT_NEAR(vertexes[4], -1, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1, s21_EXP);
  ASSERT_NEAR(vertexes[7], -1, s21_EXP);
  ASSERT_NEAR(vertexes[8], 1, s21_EXP);

  ASSERT_NEAR(vertexes[9], -1, s21_EXP);
  ASSERT_NEAR(vertexes[10], -1, s21_EXP);
  ASSERT_NEAR(vertexes[11], -1, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1, s21_EXP);
  ASSERT_NEAR(vertexes[13], 1, s21_EXP);
  ASSERT_NEAR(vertexes[14], -1, s21_EXP);

  ASSERT_NEAR(vertexes[15], 1, s21_EXP);
  ASSERT_NEAR(vertexes[16], 1, s21_EXP);
  ASSERT_NEAR(vertexes[17], 1, s21_EXP);

  ASSERT_NEAR(vertexes[18], -1, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1, s21_EXP);
  ASSERT_NEAR(vertexes[20], 1, s21_EXP);

  ASSERT_NEAR(vertexes[21], -1, s21_EXP);
  ASSERT_NEAR(vertexes[22], 1, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1, s21_EXP);

  DeleteTestObjFile();
}

TEST(MoveObjectBX, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Move('x', 5, 0, 0);

  ASSERT_NEAR(vertexes[0], 6, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1, s21_EXP);
  ASSERT_NEAR(vertexes[2], -1, s21_EXP);

  ASSERT_NEAR(vertexes[3], 6, s21_EXP);
  ASSERT_NEAR(vertexes[4], -1, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1, s21_EXP);

  ASSERT_NEAR(vertexes[6], 4, s21_EXP);
  ASSERT_NEAR(vertexes[7], -1, s21_EXP);
  ASSERT_NEAR(vertexes[8], 1, s21_EXP);

  ASSERT_NEAR(vertexes[9], 4, s21_EXP);
  ASSERT_NEAR(vertexes[10], -1, s21_EXP);
  ASSERT_NEAR(vertexes[11], -1, s21_EXP);

  ASSERT_NEAR(vertexes[12], 6, s21_EXP);
  ASSERT_NEAR(vertexes[13], 1, s21_EXP);
  ASSERT_NEAR(vertexes[14], -1, s21_EXP);

  ASSERT_NEAR(vertexes[15], 6, s21_EXP);
  ASSERT_NEAR(vertexes[16], 1, s21_EXP);
  ASSERT_NEAR(vertexes[17], 1, s21_EXP);

  ASSERT_NEAR(vertexes[18], 4, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1, s21_EXP);
  ASSERT_NEAR(vertexes[20], 1, s21_EXP);

  ASSERT_NEAR(vertexes[21], 4, s21_EXP);
  ASSERT_NEAR(vertexes[22], 1, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1, s21_EXP);

  DeleteTestObjFile();
}

TEST(MoveObjectBY, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Move('y', 0, 5, 0);

  ASSERT_NEAR(vertexes[0], 1, s21_EXP);
  ASSERT_NEAR(vertexes[1], 4, s21_EXP);
  ASSERT_NEAR(vertexes[2], -1, s21_EXP);

  ASSERT_NEAR(vertexes[3], 1, s21_EXP);
  ASSERT_NEAR(vertexes[4], 4, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1, s21_EXP);
  ASSERT_NEAR(vertexes[7], 4, s21_EXP);
  ASSERT_NEAR(vertexes[8], 1, s21_EXP);

  ASSERT_NEAR(vertexes[9], -1, s21_EXP);
  ASSERT_NEAR(vertexes[10], 4, s21_EXP);
  ASSERT_NEAR(vertexes[11], -1, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1, s21_EXP);
  ASSERT_NEAR(vertexes[13], 6, s21_EXP);
  ASSERT_NEAR(vertexes[14], -1, s21_EXP);

  ASSERT_NEAR(vertexes[15], 1, s21_EXP);
  ASSERT_NEAR(vertexes[16], 6, s21_EXP);
  ASSERT_NEAR(vertexes[17], 1, s21_EXP);

  ASSERT_NEAR(vertexes[18], -1, s21_EXP);
  ASSERT_NEAR(vertexes[19], 6, s21_EXP);
  ASSERT_NEAR(vertexes[20], 1, s21_EXP);

  ASSERT_NEAR(vertexes[21], -1, s21_EXP);
  ASSERT_NEAR(vertexes[22], 6, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1, s21_EXP);

  DeleteTestObjFile();
}

TEST(MoveObjectBZ, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Move('z', 0, 0, 5);

  ASSERT_NEAR(vertexes[0], 1, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1, s21_EXP);
  ASSERT_NEAR(vertexes[2], 4, s21_EXP);

  ASSERT_NEAR(vertexes[3], 1, s21_EXP);
  ASSERT_NEAR(vertexes[4], -1, s21_EXP);
  ASSERT_NEAR(vertexes[5], 6, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1, s21_EXP);
  ASSERT_NEAR(vertexes[7], -1, s21_EXP);
  ASSERT_NEAR(vertexes[8], 6, s21_EXP);

  ASSERT_NEAR(vertexes[9], -1, s21_EXP);
  ASSERT_NEAR(vertexes[10], -1, s21_EXP);
  ASSERT_NEAR(vertexes[11], 4, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1, s21_EXP);
  ASSERT_NEAR(vertexes[13], 1, s21_EXP);
  ASSERT_NEAR(vertexes[14], 4, s21_EXP);

  ASSERT_NEAR(vertexes[15], 1, s21_EXP);
  ASSERT_NEAR(vertexes[16], 1, s21_EXP);
  ASSERT_NEAR(vertexes[17], 6, s21_EXP);

  ASSERT_NEAR(vertexes[18], -1, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1, s21_EXP);
  ASSERT_NEAR(vertexes[20], 6, s21_EXP);

  ASSERT_NEAR(vertexes[21], -1, s21_EXP);
  ASSERT_NEAR(vertexes[22], 1, s21_EXP);
  ASSERT_NEAR(vertexes[23], 4, s21_EXP);

  DeleteTestObjFile();
}

TEST(RotationObjBX, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Rotate('x', 5, 0, 0);

  ASSERT_NEAR(vertexes[0], 1, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[2], -0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[3], 1, s21_EXP);
  ASSERT_NEAR(vertexes[4], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1, s21_EXP);
  ASSERT_NEAR(vertexes[7], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[8], 1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[9], -1, s21_EXP);
  ASSERT_NEAR(vertexes[10], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[11], -0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1, s21_EXP);
  ASSERT_NEAR(vertexes[13], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[14], -1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[15], 1, s21_EXP);
  ASSERT_NEAR(vertexes[16], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[17], 0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[18], -1, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[20], 0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[21], -1, s21_EXP);
  ASSERT_NEAR(vertexes[22], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1.08335, s21_EXP);

  DeleteTestObjFile();
}

TEST(RotationObjBY, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Rotate('y', 0, 5, 0);

  ASSERT_NEAR(vertexes[0], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1, s21_EXP);
  ASSERT_NEAR(vertexes[2], -0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[3], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[4], -1, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[7], -1, s21_EXP);
  ASSERT_NEAR(vertexes[8], 0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[9], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[10], -1, s21_EXP);
  ASSERT_NEAR(vertexes[11], -1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[13], 1, s21_EXP);
  ASSERT_NEAR(vertexes[14], -0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[15], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[16], 1, s21_EXP);
  ASSERT_NEAR(vertexes[17], 1.08335, s21_EXP);

  ASSERT_NEAR(vertexes[18], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1, s21_EXP);
  ASSERT_NEAR(vertexes[20], 0.909039, s21_EXP);

  ASSERT_NEAR(vertexes[21], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[22], 1, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1.08335, s21_EXP);

  DeleteTestObjFile();
}

TEST(RotationObjBZ, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Rotate('z', 0, 0, 5);

  ASSERT_NEAR(vertexes[0], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[1], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[2], -1, s21_EXP);

  ASSERT_NEAR(vertexes[3], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[4], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[5], 1, s21_EXP);

  ASSERT_NEAR(vertexes[6], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[7], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[8], 1, s21_EXP);

  ASSERT_NEAR(vertexes[9], -1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[10], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[11], -1, s21_EXP);

  ASSERT_NEAR(vertexes[12], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[13], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[14], -1, s21_EXP);

  ASSERT_NEAR(vertexes[15], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[16], 0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[17], 1, s21_EXP);

  ASSERT_NEAR(vertexes[18], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[19], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[20], 1, s21_EXP);

  ASSERT_NEAR(vertexes[21], -0.909039, s21_EXP);
  ASSERT_NEAR(vertexes[22], 1.08335, s21_EXP);
  ASSERT_NEAR(vertexes[23], -1, s21_EXP);

  DeleteTestObjFile();
}

TEST(ScaleObj, 1) {
  CreateTestObjFile();
  s21::Model model;
  s21::Controller controller(&model);
  controller.OpenFile("tests/test.obj");
  std::vector<double>::pointer vertexes = controller.GetVertexPointer();
  controller.Scale(4);

  ASSERT_NEAR(vertexes[0], 4, s21_EXP);
  ASSERT_NEAR(vertexes[1], -4, s21_EXP);
  ASSERT_NEAR(vertexes[2], -4, s21_EXP);

  ASSERT_NEAR(vertexes[3], 4, s21_EXP);
  ASSERT_NEAR(vertexes[4], -4, s21_EXP);
  ASSERT_NEAR(vertexes[5], 4, s21_EXP);

  ASSERT_NEAR(vertexes[6], -4, s21_EXP);
  ASSERT_NEAR(vertexes[7], -4, s21_EXP);
  ASSERT_NEAR(vertexes[8], 4, s21_EXP);

  ASSERT_NEAR(vertexes[9], -4, s21_EXP);
  ASSERT_NEAR(vertexes[10], -4, s21_EXP);
  ASSERT_NEAR(vertexes[11], -4, s21_EXP);

  ASSERT_NEAR(vertexes[12], 4, s21_EXP);
  ASSERT_NEAR(vertexes[13], 4, s21_EXP);
  ASSERT_NEAR(vertexes[14], -4, s21_EXP);

  ASSERT_NEAR(vertexes[15], 4, s21_EXP);
  ASSERT_NEAR(vertexes[16], 4, s21_EXP);
  ASSERT_NEAR(vertexes[17], 4, s21_EXP);

  ASSERT_NEAR(vertexes[18], -4, s21_EXP);
  ASSERT_NEAR(vertexes[19], 4, s21_EXP);
  ASSERT_NEAR(vertexes[20], 4, s21_EXP);

  ASSERT_NEAR(vertexes[21], -4, s21_EXP);
  ASSERT_NEAR(vertexes[22], 4, s21_EXP);
  ASSERT_NEAR(vertexes[23], -4, s21_EXP);

  DeleteTestObjFile();
}


int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
