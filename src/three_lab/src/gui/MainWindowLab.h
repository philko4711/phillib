#ifndef MAIN_WINDOW_LAB_H_
#define MAIN_WINDOW_LAB_H_

#include <QMainWindow>
#include "ui_main_window.h"

class MainWindowLab : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindowLab();
    virtual ~MainWindowLab(){}
    public slots:
      void slopedInput();
      void drawPointCloud(pcl::PointCloud<pcl::PointXYZ>& cloud){_guiUi->widget->drawPoints(cloud);}
    private:
      std::unique_ptr<Ui::MainWindowThLab> _guiUi;
};

#endif