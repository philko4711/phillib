#include "TestQvtk.h"
#include <phillib_utils/random.h>
#include <vtkRenderWindow.h>

namespace phillib
{
namespace qt
{
TestQvtk::TestQvtk()
    : _viewer(std::make_unique<WidgetNewQvtk>())
{
  _timerMain.start(1000);
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(callBackTimer()));
  //_viewer->addAxes();
  _viewer->show();
}

void TestQvtk::randomCloud(pcl::PointCloud<pcl::PointXYZ>& cloud, const unsigned nPoints, const Eigen::Vector3f& threshP, const Eigen::Vector3f& threshN)
{
  std::vector<float> xs;
  std::vector<float> ys;
  std::vector<float> zs;

  phillib::utils::randomReal(nPoints, xs, threshN.x(), threshP.x());
  phillib::utils::randomReal(nPoints, ys, threshN.y(), threshP.y());
  phillib::utils::randomReal(nPoints, zs, threshN.z(), threshP.z());

  for(unsigned int i = 0; i < nPoints; i++)
    cloud.push_back(pcl::PointXYZ(xs[i], ys[i], zs[i]));
}

void TestQvtk::randomCloud(pcl::PointCloud<pcl::PointXYZRGB>& cloud, const unsigned nPoints, const Eigen::Vector3f& threshP, const Eigen::Vector3f& threshN)
{
  std::vector<float> xs;
  std::vector<float> ys;
  std::vector<float> zs;

  std::vector<int> rs;
  std::vector<int> gs;
  std::vector<int> bs;

  phillib::utils::randomReal(nPoints, xs, threshN.x(), threshP.x());
  phillib::utils::randomReal(nPoints, ys, threshN.y(), threshP.y());
  phillib::utils::randomReal(nPoints, zs, threshN.z(), threshP.z());

  phillib::utils::randomInts(nPoints, rs, 0, 255);
  phillib::utils::randomInts(nPoints, gs, 0, 255);
  phillib::utils::randomInts(nPoints, bs, 0, 255);

  for(unsigned int i = 0; i < nPoints; i++)
  {
    pcl::PointXYZRGB point;
    point.x = xs[i];
    point.y = ys[i];
    point.z = zs[i];
    point.r = rs[i];
    point.g = gs[i];
    point.b = bs[i];
    cloud.push_back(point);
  }
}

void TestQvtk::callBackTimer()
{
  pcl::PointCloud<pcl::PointXYZRGB> cloud;
  this->randomCloud(cloud, 500, Eigen::Vector3f(2.0f, 2.0f, 2.0f), Eigen::Vector3f(-2.0f, -2.0f, -2.0f));
  _viewer->drawPoints(cloud);
  _viewer->renderWindow()->Render();
}

} // namespace qt
} // namespace phillib
