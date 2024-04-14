#ifndef CONTROLLER_CONTROLLER_H
#define CONTROLLER_CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 public:
  Controller(Model *m) : model_(m){};
  ~Controller(){};

  void OpenFile(const std::string &file) { model_->affine.ParseFile(file); }
  void Rotate(char axis, double x_angle, double y_angle, double z_angle);
  void Move(char axis, double x_distance, double y_distance, double z_distance);
  void Scale(double scale);
  std::vector<int>::pointer GetFacetPointer() {
    return model_->affine.GetFacetPointer();
  };
  std::vector<double>::pointer GetVertexPointer() {
    return model_->affine.GetVertexPointer();
  };
  int GetCountOfVertexes() { return model_->affine.GetCountOfVertexes(); }
  int GetCountOfFacets() { return model_->affine.GetCountOfFacets(); }
  int GetCountOfEdges() { return model_->affine.GetCountOfEdges(); }
  double GetMaxVertex() { return model_->affine.GetMaxVertex(); }

 private:
  Model *model_;
};

}  // namespace s21

#endif  // CONTROLLER_CONTROLLER_H
