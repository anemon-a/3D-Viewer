#include "../controller/controller.h"

void s21::Controller::Rotate(char axis, double x_angle, double y_angle,
                             double z_angle) {
  if (axis == 'x') model_->affine.RotationByOX(x_angle);
  if (axis == 'y') model_->affine.RotationByOY(y_angle);
  if (axis == 'z') model_->affine.RotationByOZ(z_angle);
}

void s21::Controller::Move(char axis, double x_direction, double y_direction,
                           double z_direction) {
  if (axis == 'x') model_->affine.MoveObjectByOX(x_direction);
  if (axis == 'y') model_->affine.MoveObjectByOY(y_direction);
  if (axis == 'z') model_->affine.MoveObjectByOZ(z_direction);
}

void s21::Controller::Scale(double scale) {
  model_->affine.ChangeScaleObject(scale);
}
