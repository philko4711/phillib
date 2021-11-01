#include "TestQvtk.h"
#include <QtCore/QDebug>
#include <phillib_utils/random.h>
#include <vtkRenderWindow.h>

namespace phillib {
namespace qt {
TestQvtk::TestQvtk() : _viewer(std::make_unique<WidgetNewQvtk>()) {
  _timerMain.start(1000);
  connect(&_timerMain, SIGNAL(timeout()), this, SLOT(callBackTimer()));
  //_viewer->addAxes();
  // _viewer->addCube(Eigen::Vector3f(1.0f, 1.0f, 1.0f),
  //                  Eigen::Vector3f(0.0, 0.0, 0.0));
  _viewer->show();
}

void TestQvtk::randomCubes(const unsigned int nCubes,
                           const Eigen::Vector3f &threshDim,
                           const Eigen::Vector3f &threshCenterP,
                           const Eigen::Vector3f &threshCenterN) {
  std::vector<float> xD;
  std::vector<float> yD;
  std::vector<float> zD;

  phillib::utils::randomReal(nCubes, xD, 0.01f, threshDim.x());
  phillib::utils::randomReal(nCubes, yD, 0.01f, threshDim.y());
  phillib::utils::randomReal(nCubes, zD, 0.01f, threshDim.z());

  std::vector<float> xC;
  std::vector<float> yC;
  std::vector<float> zC;

  phillib::utils::randomReal(nCubes, xC, threshCenterN.x(), threshCenterP.x());
  phillib::utils::randomReal(nCubes, yC, threshCenterN.y(), threshCenterP.y());
  phillib::utils::randomReal(nCubes, zC, threshCenterN.z(), threshCenterP.z());

  for(unsigned int i = 0;  i < nCubes; i++)
  {
    Eigen::Vector3f dim(xD[i], yD[i], zD[i]);
    Eigen::Vector3f center(xC[i], yC[i], zC[i]);
    _viewer->addCube(dim, center);
  }
}

void TestQvtk::randomCloud(pcl::PointCloud<pcl::PointXYZ> &cloud,
                           const unsigned nPoints,
                           const Eigen::Vector3f &threshP,
                           const Eigen::Vector3f &threshN) {
  std::vector<float> xs;
  std::vector<float> ys;
  std::vector<float> zs;

  phillib::utils::randomReal(nPoints, xs, threshN.x(), threshP.x());
  phillib::utils::randomReal(nPoints, ys, threshN.y(), threshP.y());
  phillib::utils::randomReal(nPoints, zs, threshN.z(), threshP.z());

  for (unsigned int i = 0; i < nPoints; i++)
    cloud.push_back(pcl::PointXYZ(xs[i], ys[i], zs[i]));
}

void TestQvtk::randomCloud(pcl::PointCloud<pcl::PointXYZRGB> &cloud,
                           const unsigned nPoints,
                           const Eigen::Vector3f &threshP,
                           const Eigen::Vector3f &threshN) {
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

  for (unsigned int i = 0; i < nPoints; i++) {
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

void TestQvtk::callBackTimer() {
  _viewer->clearCubes();
  this->randomCubes(10, Eigen::Vector3f(1.0, 1.0, 1.0), Eigen::Vector3f(-5.0, -5.0, -5.0), Eigen::Vector3f(5.0, 5.0, 5.0));
  // pcl::PointCloud<pcl::PointXYZRGB> cloud;
  // this->randomCloud(cloud, 500, Eigen::Vector3f(2.0f, 2.0f, 2.0f),
  //                   Eigen::Vector3f(-2.0f, -2.0f, -2.0f));
  // std::vector<Line> lines;
  // this->randomLines(lines, 500, Eigen::Vector3f(2.0f, 2.0f, 2.0f),
  //                   Eigen::Vector3f(-2.0f, -2.0f, -2.0f), 0.05);
  // _viewer->clearLines();
  // for (auto &iter : lines)
  //   _viewer->addLine(iter);
  // _viewer->drawPoints(cloud);
  // _viewer->drawLines();
  _viewer->renderWindow()->Render();
}

void TestQvtk::randomLines(std::vector<Line> &lineVec, const unsigned nPoints,
                           const Eigen::Vector3f &threshP,
                           const Eigen::Vector3f &threshN,
                           const float thickNess) {
  std::vector<float> xs;
  std::vector<float> ys;
  std::vector<float> zs;

  std::vector<int> rs;
  std::vector<int> gs;
  std::vector<int> bs;

  phillib::utils::randomReal(2 * nPoints, xs, threshN.x(), threshP.x());
  phillib::utils::randomReal(2 * nPoints, ys, threshN.y(), threshP.y());
  phillib::utils::randomReal(2 * nPoints, zs, threshN.z(), threshP.z());

  phillib::utils::randomInts(nPoints, rs, 0, 255);
  phillib::utils::randomInts(nPoints, gs, 0, 255);
  phillib::utils::randomInts(nPoints, bs, 0, 255);

  for (unsigned int i = 0; i < nPoints; i++) {
    Eigen::Vector3f start(xs[i], ys[i], zs[i]);
    Eigen::Vector3f end(xs[nPoints + i], ys[nPoints + i], zs[nPoints + i]);
    Line line(start, end);
    line._width = thickNess;
    line._color = QColor(rs[i], gs[i], bs[i]);
    std::cout << __PRETTY_FUNCTION__ << " r g b " << rs[i] << " " << gs[i]
              << " " << bs[i] << std::endl;
    qDebug() << __PRETTY_FUNCTION__ << " color " << line._color;
    lineVec.push_back(line);
  }
}

} // namespace qt
} // namespace phillib
