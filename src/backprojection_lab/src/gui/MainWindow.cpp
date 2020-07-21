#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow():
  _guiUi(std::unique_ptr<Ui::MainWindowBackLab>(new Ui::MainWindowBackLab()))
{
  _guiUi->setupUi(this);
}

void MainWindow::addSensor()
{
  qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::dialogVoxelGrid()
{
qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::addVoxelGrid(const float edgeLength, const unsigned int nDim)
{
qDebug() << __PRETTY_FUNCTION__;
}