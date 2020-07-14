#ifndef MAIN_WINDOW_LAB_H_
#define MAIN_WINDOW_LAB_H_

#include <QMainWindow>
#include "ui_main_window.h"
#include <pcl/point_cloud.h>
#include <memory>

class MainWindowLab : public QMainWindow
{
  Q_OBJECT
  public:
    MainWindowLab();
    virtual ~MainWindowLab(){}
    public slots:
      void slopedInput();
      void randomPlaneInput();
      void drawPointCloud(pcl::PointCloud<pcl::PointXYZ>& cloud){_guiUi->widget->drawPoints(cloud);}
      void planeFit();
      void singDecom();
    private:
      std::unique_ptr<Ui::MainWindowThLab> _guiUi;
      std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> > _cloud;
};

#endif