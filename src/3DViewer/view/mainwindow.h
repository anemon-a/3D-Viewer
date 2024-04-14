#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>

#include "../controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(s21::Controller *c);
  ~MainWindow();

 public slots:
  void ChangeScale(double value);

 private slots:
  void on_XMovSlider_valueChanged(int value);
  void on_YMovSlider_valueChanged(int value);
  void on_ZMovSlider_valueChanged(int value);
  void on_XMovSpinBox_valueChanged(double value);
  void on_YMovSpinBox_valueChanged(double value);
  void on_ZMovSpinBox_valueChanged(double value);

  void on_XRotSlider_valueChanged(int value);
  void on_YRotSlider_valueChanged(int value);
  void on_ZRotSlider_valueChanged(int value);
  void on_XRotSpinBox_valueChanged(double value);
  void on_YRotSpinBox_valueChanged(double value);
  void on_ZRotSpinBox_valueChanged(double value);
  void on_ScaleSpinBox_valueChanged(double value);

  void on_SizeVertexSlider_valueChanged(int value);
  void on_SizeVertexSpinBox_valueChanged(double value);
  void on_SizeEdgeSlider_valueChanged(int value);
  void on_SizeEdgeSpinBox_valueChanged(double value);

  void on_VertexColor_clicked();
  void on_EdgeColor_clicked();
  void on_BackgoundColor_clicked();

  void on_VertexType_currentIndexChanged(int type);
  void on_EdgeType_currentIndexChanged(int type);

  void on_actionOpen_triggered();
  void on_actionSave_As_triggered();
  void on_Reset_clicked();

  void on_ProjectionType_currentIndexChanged(int index);

 private:
  void OpenFile();
  void SetInfo();
  void saveSettings();
  void readSettings();

  s21::Controller *controller_;
  Ui::MainWindow *ui;
  QString filename_;
};
#endif  // MAINWINDOW_H
