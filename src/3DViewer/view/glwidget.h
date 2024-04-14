#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QWheelEvent>

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget* parent = nullptr);

  void SetVertexPointer(std::vector<double>::pointer p);
  void SetCountOfVertexes(int count);
  void SetVertexType(int type);
  void SetVertexSize(double size);
  void SetFacetPointer(std::vector<int>::pointer p);
  void SetCountOfEdges(int count);
  void SetEdgeType(int type);
  void SetEdgeSize(double size);
  void SetBound(double bound);
  void SetProjectionType(int type);
  void SetColor(QColor color, int type);
  QColor GetColor(int type);

 public slots:
  void SetScale(double scale);

 signals:
  void ChangeScale(double value);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  void wheelEvent(QWheelEvent* event) override;
  void DrawVertexes();
  void DrawEdges();
  void SetOrtho(double bound);
  void SetFrustum(double bound);

  std::vector<double>::pointer vertexes_;
  uint count_of_vertexes_;
  uint vertex_type_;
  double vertex_size_;

  std::vector<int>::pointer facets_;
  uint count_of_edges_;
  uint edge_type_;
  uint edge_size_;

  int projection_type_;
  QColor bg_color_, vertex_color_, edge_color_;

  double bound_;
  double scale_;
};

#endif  // GLWIDGET_H
