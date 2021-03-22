#include "TestQvtk.h"
#include <phillib_utils/random.h>

namespace phillib
{
namespace qt
{
TestQvtk::TestQvtk()
    : _viewer(std::make_unique<WidgetNewQvtk>())
{
  _timerMain.start(1000);
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(callBackTimer()));
  _viewer->addAxes();
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

void TestQvtk::callBackTimer()
{
  pcl::PointCloud<pcl::PointXYZ> cloud;
  this->randomCloud(cloud, 500, Eigen::Vector3f(2.0f, 2.0f, 2.0f), Eigen::Vector3f(-2.0f, -2.0f, -2.0f));
  _viewer->drawPoints(cloud);
  _viewer->update();
}

} // namespace qt
} // namespace phillib
