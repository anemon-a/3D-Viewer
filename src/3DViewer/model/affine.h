#ifndef MODEL_AFFINE_H
#define MODEL_AFFINE_H

#include <cmath>
#include <stack>
#include <string>
#include <vector>

#include "../model/parser.h"

namespace s21 {

class Affine {
 public:
  Affine(){};
  ~Affine(){};
  void ParseFile(const std::string filename);
  void ChangeScaleObject(double scale);
  void RotationByOX(double angle);
  void RotationByOY(double angle);
  void RotationByOZ(double angle);
  void MoveObjectByOX(double distance);
  void MoveObjectByOY(double distance);
  void MoveObjectByOZ(double distance);
  std::vector<int>::pointer GetFacetPointer() { return &facets_[0]; };
  std::vector<double>::pointer GetVertexPointer() { return &vertexes_[0]; };
  int GetCountOfFacets() { return parser_.GetCountOfFacets(); }
  int GetCountOfVertexes() { return parser_.GetCountOfVertexes(); }
  int GetCountOfEdges() { return parser_.GetCountOfEdges(); }
  double GetMaxVertex() { return max_vertex_; }
  void CalculationOfMaxVertex();

 private:
  void TransfromVertexes();
  void MulMatrix(double *matrix1, double *matrix2, double *matrix3);

  std::vector<int> facets_;
  std::vector<double> vertexes_;
  double max_vertex_;
  Parser parser_;
  double rotation_matrix_x_[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  double rotation_matrix_y_[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  double rotation_matrix_z_[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  double transformation_matrix_[4][3] = {
      {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0, 0, 0}};
  double scale_ = 1;
};

}  // namespace s21

#endif  // MODEL_AFFINE_H
