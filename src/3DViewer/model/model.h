#ifndef MODEL_MODEL_H
#define MODEL_MODEL_H

#include <cmath>
#include <string>

#include "../model/affine.h"

namespace s21 {

class Model {
 public:
  Model(){};
  s21::Affine affine;

 private:
};

}  // namespace s21

#endif  // MODEL_MODEL_H