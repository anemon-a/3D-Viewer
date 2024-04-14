#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget{parent} {}

void GLWidget::initializeGL() {}

void GLWidget::resizeGL(int w, int h) {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
}

void GLWidget::paintGL() {
  glClearColor(bg_color_.redF(), bg_color_.greenF(), bg_color_.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type_ == 0)
    SetOrtho(2 * bound_);
  else
    SetFrustum(bound_);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glEnableClientState(GL_VERTEX_ARRAY);
  DrawVertexes();
  DrawEdges();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::DrawVertexes() {
  switch (vertex_type_) {
    case 0:
      glEnable(GL_POINT_SMOOTH);
      break;
    case 1:
      glDisable(GL_POINT_SMOOTH);
      break;
    case 2:
      return;
  }
  glColor3d(vertex_color_.redF(), vertex_color_.greenF(),
            vertex_color_.blueF());
  glPointSize(vertex_size_);
  glVertexPointer(3, GL_DOUBLE, 0, vertexes_);
  glDrawArrays(GL_POINTS, 0, count_of_vertexes_);
}

void GLWidget::DrawEdges() {
  if (edge_type_) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glColor3d(edge_color_.redF(), edge_color_.greenF(), edge_color_.blueF());
  glLineWidth(edge_size_);
  glDrawElements(GL_LINES, count_of_edges_ * 2, GL_UNSIGNED_INT, facets_);
}

void GLWidget::SetOrtho(double bound) {
  glOrtho(-bound, bound, -bound, bound, -bound, 1000);
}

void GLWidget::SetFrustum(double bound) {
  double fov = M_PI / 3;
  double heapHeight = bound / (2 * tan(fov / 2));
  glFrustum(-bound, bound, -bound, bound, heapHeight, 1000);
  glTranslated(0, 0, -heapHeight * 2);
}

void GLWidget::SetVertexPointer(std::vector<double>::pointer p) {
  vertexes_ = p;
}
void GLWidget::SetCountOfVertexes(int count) { count_of_vertexes_ = count; }

void GLWidget::SetVertexType(int type) { vertex_type_ = type; }

void GLWidget::SetVertexSize(double size) { vertex_size_ = size; }

void GLWidget::SetFacetPointer(std::vector<int>::pointer p) { facets_ = p; }

void GLWidget::SetCountOfEdges(int count) { count_of_edges_ = count; }

void GLWidget::SetEdgeType(int type) { edge_type_ = type; }

void GLWidget::SetEdgeSize(double size) { edge_size_ = size; }

void GLWidget::SetBound(double bound) { bound_ = bound; }

void GLWidget::SetProjectionType(int type) { projection_type_ = type; }

void GLWidget::SetScale(double scale) { scale_ = scale; }

QColor GLWidget::GetColor(int type) {
  if (type == 0)
    return vertex_color_;
  else if (type == 1)
    return edge_color_;
  else
    return bg_color_;
}

void GLWidget::SetColor(QColor color, int type) {
  if (type == 0)
    vertex_color_ = color;
  else if (type == 1)
    edge_color_ = color;
  else
    bg_color_ = color;
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  QPoint delta = event->angleDelta();
  if (!delta.isNull()) {
    if (delta.y() > 0) {
      scale_ += 0.05;
    } else {
      if (scale_ > 0.01) scale_ -= 0.05;
    }
  }
  event->accept();
  emit ChangeScale(scale_);
}
