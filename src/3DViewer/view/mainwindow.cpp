#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Controller* c)
    : controller_(c), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  connect(ui->GLwidget, &GLWidget::ChangeScale, this, &MainWindow::ChangeScale);
  readSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

//---------------------------------------------------------------------------------------------------------------

void MainWindow::on_XMovSlider_valueChanged(int value) {
  on_XMovSpinBox_valueChanged(value);
}

void MainWindow::on_YMovSlider_valueChanged(int value) {
  on_YMovSpinBox_valueChanged(value);
}

void MainWindow::on_ZMovSlider_valueChanged(int value) {
  on_ZMovSpinBox_valueChanged(value);
}

void MainWindow::on_XMovSpinBox_valueChanged(double value) {
  ui->XMovSpinBox->setValue(value);
  ui->XMovSlider->setValue(value);
  controller_->Move('x', value, 0, 0);
  ui->GLwidget->update();
}

void MainWindow::on_YMovSpinBox_valueChanged(double value) {
  ui->YMovSpinBox->setValue(value);
  ui->YMovSlider->setValue(value);
  controller_->Move('y', 0, value, 0);
  ui->GLwidget->update();
}

void MainWindow::on_ZMovSpinBox_valueChanged(double value) {
  ui->ZMovSpinBox->setValue(value);
  ui->ZMovSlider->setValue(value);
  controller_->Move('z', 0, 0, value);
  ui->GLwidget->update();
}

//---------------------------------------------------------------------------------------------------------------

void MainWindow::on_XRotSlider_valueChanged(int value) {
  on_XRotSpinBox_valueChanged(value);
}

void MainWindow::on_YRotSlider_valueChanged(int value) {
  on_YRotSpinBox_valueChanged(value);
}

void MainWindow::on_ZRotSlider_valueChanged(int value) {
  on_ZRotSpinBox_valueChanged(value);
}

void MainWindow::on_XRotSpinBox_valueChanged(double value) {
  ui->XRotSpinBox->setValue(value);
  ui->XRotSlider->setValue(value);
  controller_->Rotate('x', value, 0, 0);
  ui->GLwidget->update();
}

void MainWindow::on_YRotSpinBox_valueChanged(double value) {
  ui->YRotSpinBox->setValue(value);
  ui->YRotSlider->setValue(value);
  controller_->Rotate('y', 0, value, 0);
  ui->GLwidget->update();
}

void MainWindow::on_ZRotSpinBox_valueChanged(double value) {
  ui->ZRotSpinBox->setValue(value);
  ui->ZRotSlider->setValue(value);
  controller_->Rotate('z', 0, 0, value);
  ui->GLwidget->update();
}

void MainWindow::on_ScaleSpinBox_valueChanged(double value) {
  ui->GLwidget->SetScale(value);
  controller_->Scale(value);
  ChangeScale(value);
}

void MainWindow::ChangeScale(double value) {
  ui->ScaleSpinBox->setValue(value);
  ui->GLwidget->update();
}

//---------------------------------------------------------------------------------------------------------------

void MainWindow::on_VertexType_currentIndexChanged(int index) {
  ui->GLwidget->SetVertexType(index);
  ui->GLwidget->update();
}

void MainWindow::on_SizeVertexSlider_valueChanged(int value) {
  on_SizeVertexSpinBox_valueChanged(value);
}

void MainWindow::on_SizeVertexSpinBox_valueChanged(double value) {
  ui->SizeVertexSpinBox->setValue(value);
  ui->SizeVertexSlider->setValue(value);
  ui->GLwidget->SetVertexSize(value);
  ui->GLwidget->update();
}

//---------------------------------------------------------------------------------------------------------------

void MainWindow::on_EdgeType_currentIndexChanged(int index) {
  ui->GLwidget->SetEdgeType(index);
  ui->GLwidget->update();
}

void MainWindow::on_SizeEdgeSlider_valueChanged(int value) {
  on_SizeEdgeSpinBox_valueChanged(value);
}

void MainWindow::on_SizeEdgeSpinBox_valueChanged(double value) {
  ui->SizeEdgeSpinBox->setValue(value);
  ui->SizeEdgeSlider->setValue(value);
  ui->GLwidget->SetEdgeSize(value);
  ui->GLwidget->update();
}

void MainWindow::on_ProjectionType_currentIndexChanged(int index) {
  ui->ProjectionType->setCurrentIndex(index);
  ui->GLwidget->SetProjectionType(index);
  ui->GLwidget->update();
}

//--------------------------------------------------------------------------------------------------------------

void MainWindow::on_VertexColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->GLwidget->SetColor(color, 0);
  ui->GLwidget->update();
}

void MainWindow::on_EdgeColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->GLwidget->SetColor(color, 1);
  ui->GLwidget->update();
}

void MainWindow::on_BackgoundColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, tr("Select color"));
  ui->GLwidget->SetColor(color, 2);
  ui->GLwidget->update();
}

//---------------------------------------------------------------------------------------------------------------

void MainWindow::on_Reset_clicked() {
  ui->XMovSpinBox->setValue(0);
  ui->YMovSpinBox->setValue(0);
  ui->ZMovSpinBox->setValue(0);

  ui->XRotSpinBox->setValue(0);
  ui->YRotSpinBox->setValue(0);
  ui->ZRotSpinBox->setValue(0);
  ui->ScaleSpinBox->setValue(1);

  ui->GLwidget->SetColor(Qt::white, 0);
  ui->GLwidget->SetColor(Qt::white, 1);
  ui->GLwidget->SetColor(Qt::black, 2);

  ui->VertexType->setCurrentIndex(0);
  ui->EdgeType->setCurrentIndex(0);
  ui->ProjectionType->setCurrentIndex(0);

  ui->SizeVertexSpinBox->setValue(0);
  ui->SizeEdgeSpinBox->setValue(0);
  ui->GLwidget->update();
}

void MainWindow::OpenFile() {
  controller_->OpenFile(filename_.toStdString());
  if (!filename_.isEmpty()) {
    SetInfo();
    ui->GLwidget->SetVertexPointer(controller_->GetVertexPointer());
    ui->GLwidget->SetCountOfVertexes(controller_->GetCountOfVertexes());
    ui->GLwidget->SetFacetPointer(controller_->GetFacetPointer());
    ui->GLwidget->SetCountOfEdges(controller_->GetCountOfEdges());
    ui->GLwidget->SetBound(controller_->GetMaxVertex());
    ui->GLwidget->update();
  }
}

void MainWindow::SetInfo() {
  ui->Filename->setText(filename_);
  ui->VertexesAmount->setNum(controller_->GetCountOfVertexes());
  ui->FacetsAmount->setNum(controller_->GetCountOfFacets());
  ui->EdgesAmount->setNum(controller_->GetCountOfEdges());
}

void MainWindow::on_actionOpen_triggered() {
  filename_ = QFileDialog::getOpenFileName(
      this, "Choose the file", QDir::homePath(), "obj file (*.obj);;");
  OpenFile();
}

void MainWindow::on_actionSave_As_triggered() {
  QImage image = ui->GLwidget->grabFramebuffer();
  QString defaultName = "image";
  QStringList filters({"image/bmp", "image/jpeg"});
  QFileDialog saveDialog(this, tr("Save as"), defaultName, QDir::homePath());
  saveDialog.setAcceptMode(QFileDialog::AcceptSave);
  saveDialog.setDirectory(QDir::homePath());
  saveDialog.setFileMode(QFileDialog::AnyFile);
  saveDialog.setMimeTypeFilters(filters);
  if (saveDialog.exec() == QDialog::Accepted) {
    const QString fname = saveDialog.selectedFiles().constFirst();
    if (!image.save(fname)) {
      QMessageBox::warning(this, tr("Error"),
                           tr("Imposible to save image in \"%1\".")
                               .arg(QDir::toNativeSeparators(fname)));
    }
  }
}

void MainWindow::saveSettings() {
  QSettings settings(QDir::homePath() + "/3DViewer/Settings",
                     QSettings::NativeFormat);
  settings.beginGroup("filename");
  settings.setValue("filename", filename_);
  settings.endGroup();

  settings.beginGroup("Moving");
  settings.setValue("xMov", ui->XMovSpinBox->value());
  settings.setValue("yMov", ui->YMovSpinBox->value());
  settings.setValue("zMov", ui->ZMovSpinBox->value());
  settings.endGroup();

  settings.beginGroup("Rotation");
  settings.setValue("xRot", ui->XRotSpinBox->value());
  settings.setValue("yRot", ui->YRotSpinBox->value());
  settings.setValue("zRot", ui->ZRotSpinBox->value());
  settings.endGroup();

  settings.beginGroup("Colors");
  settings.setValue("vColor", ui->GLwidget->GetColor(0));
  settings.setValue("fColor", ui->GLwidget->GetColor(1));
  settings.setValue("bgColor", ui->GLwidget->GetColor(2));
  settings.endGroup();

  settings.beginGroup("Options");
  settings.setValue("VertexType", ui->VertexType->currentIndex());
  settings.setValue("EdgeType", ui->EdgeType->currentIndex());
  settings.setValue("ProjectionType", ui->ProjectionType->currentIndex());

  settings.setValue("VertexSize", ui->SizeVertexSpinBox->value());
  settings.setValue("EdgeSize", ui->SizeEdgeSpinBox->value());
  settings.setValue("Scale", ui->ScaleSpinBox->value());
  settings.endGroup();
}

void MainWindow::readSettings() {
  if (QFile::exists(QDir::homePath() + "/3DViewer/Settings")) {
    QSettings settings(QDir::homePath() + "/3DViewer/Settings",
                       QSettings::NativeFormat);
    settings.beginGroup("filename");
    filename_ = settings.value("filename").value<QString>();
    settings.endGroup();

    if (QFile::exists(filename_)) OpenFile();

    settings.beginGroup("Moving");
    ui->XMovSpinBox->setValue(settings.value("xMov").value<double>());
    ui->YMovSpinBox->setValue(settings.value("yMov").value<double>());
    ui->ZMovSpinBox->setValue(settings.value("zMov").value<double>());
    settings.endGroup();

    settings.beginGroup("Rotation");
    ui->XRotSpinBox->setValue(settings.value("xRot").value<double>());
    ui->YRotSpinBox->setValue(settings.value("yRot").value<double>());
    ui->ZRotSpinBox->setValue(settings.value("zRot").value<double>());
    settings.endGroup();

    settings.beginGroup("Colors");
    ui->GLwidget->SetColor(settings.value("vColor").value<QColor>(), 0);
    ui->GLwidget->SetColor(settings.value("fColor").value<QColor>(), 1);
    ui->GLwidget->SetColor(settings.value("bgColor").value<QColor>(), 2);
    settings.endGroup();

    settings.beginGroup("Options");
    on_VertexType_currentIndexChanged(
        settings.value("VertexType").value<int>());
    on_EdgeType_currentIndexChanged(settings.value("EdgeType").value<int>());
    on_ProjectionType_currentIndexChanged(
        settings.value("ProjectionType").value<int>());

    on_SizeVertexSpinBox_valueChanged(
        settings.value("VertexSize").value<double>());
    on_SizeEdgeSpinBox_valueChanged(settings.value("EdgeSize").value<double>());
    on_ScaleSpinBox_valueChanged(settings.value("Scale").value<double>());
    settings.endGroup();
  } else {
    on_Reset_clicked();
  }
}
