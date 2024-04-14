#include "../model/affine.h"

void s21::Affine::ParseFile(const std::string filename) {
  parser_.ParseFile(filename);
  vertexes_ = parser_.GetVertexes();
  facets_ = parser_.GetFacets();
  CalculationOfMaxVertex();
}

void s21::Affine::ChangeScaleObject(double scale) {
  scale_ = scale;
  TransfromVertexes();
}

void s21::Affine::CalculationOfMaxVertex() {
  max_vertex_ = fabs(vertexes_[0]);
  for (int i = 0; i < static_cast<int>(vertexes_.size()); i++)
    if (fabs(vertexes_[i]) > max_vertex_) max_vertex_ = fabs(vertexes_[i]);
}

void s21::Affine::RotationByOX(double angle) {
  angle = angle * M_PI / 180;
  rotation_matrix_x_[4] = cos(angle);
  rotation_matrix_x_[5] = sin(angle);
  rotation_matrix_x_[7] = -sin(angle);
  rotation_matrix_x_[8] = cos(angle);
  MulMatrix(rotation_matrix_x_, rotation_matrix_y_, rotation_matrix_z_);
  TransfromVertexes();
}

void s21::Affine::RotationByOY(double angle) {
  angle = angle * M_PI / 180;
  rotation_matrix_y_[0] = cos(angle);
  rotation_matrix_y_[2] = -sin(angle);
  rotation_matrix_y_[6] = sin(angle);
  rotation_matrix_y_[8] = cos(angle);
  MulMatrix(rotation_matrix_x_, rotation_matrix_y_, rotation_matrix_z_);
  TransfromVertexes();
}

void s21::Affine::RotationByOZ(double angle) {
  angle = angle * M_PI / 180;
  rotation_matrix_z_[0] = cos(angle);
  rotation_matrix_z_[1] = sin(angle);
  rotation_matrix_z_[3] = -sin(angle);
  rotation_matrix_z_[4] = cos(angle);
  MulMatrix(rotation_matrix_x_, rotation_matrix_y_, rotation_matrix_z_);
  TransfromVertexes();
}

void s21::Affine::MoveObjectByOX(double distance) {
  transformation_matrix_[3][0] = distance;
  TransfromVertexes();
}

void s21::Affine::MoveObjectByOY(double distance) {
  transformation_matrix_[3][1] = distance;
  TransfromVertexes();
}

void s21::Affine::MoveObjectByOZ(double distance) {
  transformation_matrix_[3][2] = distance;
  TransfromVertexes();
}

void s21::Affine::TransfromVertexes() {
  const std::vector<double>& start_vertexes = parser_.GetVertexesReference();
  double temp;
  int n = static_cast<int>(start_vertexes.size()) / 3;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < n; j++) {
      temp = 0;
      for (int k = 0; k < 3; k++) {
        temp += transformation_matrix_[i][k] * start_vertexes[j * 3 + k];
      }
      vertexes_[j * 3 + i] = temp;
    }
  }
  for (int i = 0; i < 3; i++) {
    if (transformation_matrix_[8 + i] != 0) {
      for (int j = 0; j < n; j++) {
        vertexes_[j * 3 + i] =
            vertexes_[j * 3 + i] + transformation_matrix_[3][i];
      }
    }
  }
  for (int i = 0; i < static_cast<int>(vertexes_.size()); i++) {
    vertexes_[i] = vertexes_[i] * scale_;
  }
}

void s21::Affine::MulMatrix(double* matrix1, double* matrix2, double* matrix3) {
  double temp;
  double temp_matrix[9] = {0};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      temp = 0;
      for (int k = 0; k < 3; k++) {
        temp += matrix1[i * 3 + k] * matrix2[k * 3 + j];
      }
      temp_matrix[i * 3 + j] = temp;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      temp = 0;
      for (int k = 0; k < 3; k++) {
        temp += temp_matrix[i * 3 + k] * matrix3[k * 3 + j];
      }
      transformation_matrix_[i][j] = temp;
    }
  }
}
