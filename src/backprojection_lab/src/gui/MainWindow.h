#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include "ui_main_window.h"
#include <QMainWindow>

class MainWindow : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindow();
    virtual ~MainWindow(){}
  public slots:
    void addSensor();
    void dialogVoxelGrid();
    void addVoxelGrid(const float edgeLength, const unsigned int nDim);  
  private:
  std::unique_ptr<Ui::MainWindowBackLab> _guiUi;
};

#endif 