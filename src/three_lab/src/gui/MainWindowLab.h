#ifndef MAIN_WINDOW_LAB_H_
#define MAIN_WINDOW_LAB_H_

#include <QMainWindow>
#include "ui_main_window.h"
#include <pcl/point_cloud.h>
#include <memory>


struct Line
{
  Line():
    _color(Qt::black),
    _width(1.0)
  {}
  Line(const Eigen::Vector3d& start, const Eigen::Vector3d& end):
    _start(start),
    _end(end),
    _color(Qt::white),
    _width(1.0)
    {}
  Line(const pcl::PointXYZ& start, const pcl::PointXYZ& end):
    _start(Eigen::Vector3d(static_cast<double>(start.x), static_cast<double>(start.y), static_cast<double>(start.z))),
    _end(Eigen::Vector3d(static_cast<double>(end.x), static_cast<double>(end.y), static_cast<double>(end.z))),
    _color(Qt::white),
    _width(1.0)
    {}
  Eigen::Vector3d _start;
  Eigen::Vector3d _end;
  QColor _color;
  float _width;
};
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
      void pclPlaneFit();
    private:
      std::unique_ptr<Ui::MainWindowThLab> _guiUi;
      std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> > _cloud;
};

#endif