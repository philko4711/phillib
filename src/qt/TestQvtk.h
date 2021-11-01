#ifndef PHILLIB_QT_TESTQVTK_H_
#define PHILLIB_QT_TESTQVTK_H_


#include <QtCore/QObject>
#include <QtCore/QTimer>
#include "WidgetNewQvtk.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
namespace phillib
{
namespace qt
{
  class TestQvtk : public QObject
  {
    Q_OBJECT
    public:
    TestQvtk();
    virtual ~TestQvtk(){}
    public slots:
      void callBackTimer();
    private:
      void randomCloud(pcl::PointCloud<pcl::PointXYZ>& cloud, const unsigned nPoints, const Eigen::Vector3f& threshP, const Eigen::Vector3f& threshN);
      void randomCloud(pcl::PointCloud<pcl::PointXYZRGB>& cloud, const unsigned nPoints, const Eigen::Vector3f& threshP, const Eigen::Vector3f& threshN);
      void randomLines(std::vector<Line>& lineVec, const unsigned nPoints, const Eigen::Vector3f& threshP, const Eigen::Vector3f& threshN, const float thickNess);
      void randomCubes(const unsigned int nCubes, const Eigen::Vector3f& threshDim, const Eigen::Vector3f& threshCenterP, const Eigen::Vector3f& threshCenterN);
      
      std::unique_ptr<WidgetNewQvtk> _viewer; 
      QTimer _timerMain;
};
}
}
#endif

