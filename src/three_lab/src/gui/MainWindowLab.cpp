#include "MainWindowLab.h"
#include "DialogSlopedCloud.h"
#include "DialogRandomPlane.h"
#include "RandomClouds.h"
#include "mathClouds.h"
#include <memory>
#include <QDebug>
#include <QColor>
MainWindowLab::MainWindowLab():
_guiUi(std::unique_ptr<Ui::MainWindowThLab>(new Ui::MainWindowThLab())),
_cloud(std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> >(new pcl::PointCloud<pcl::PointXYZ>()))
{
  _guiUi->setupUi(this);
  _guiUi->widget->drawAxissystem();
  connect(_guiUi->actionCreateRandomPlane, SIGNAL(triggered()), this, SLOT(randomPlaneInput()));
  connect(_guiUi->actionCreateSlopedPlane, SIGNAL(triggered()), this, SLOT(slopedInput()));
  connect(_guiUi->actionPlaneFit, SIGNAL(triggered()), this, SLOT(planeFit()));
  connect(_guiUi->actionSingDecom, SIGNAL(triggered()), this, SLOT(singDecom()));
}

void MainWindowLab::slopedInput()
{
   static DialogSlopedCloud dialog; 
   int retval = dialog.exec();
   if(retval == QDialog::DialogCode::Accepted)
   {
     _cloud->clear();
     //pcl::PointCloud<pcl::PointXYZ> cloud;
     RandomClouds::slopedRoughPlain(*_cloud, dialog.threshXdim(), dialog.threshYdim(), dialog.resolution(), 
                                    dialog.slopeX(), dialog.slopeY(), dialog.zVariance());
     _guiUi->widget->resetPoints();
     this->drawPointCloud(*_cloud);
     this->update();
   }
   else
   {
     return;
   }   
}

void MainWindowLab::randomPlaneInput()
{
  static DialogRandomPlane dialog;
  int retVal = dialog.exec();
  if(retVal == QDialog::DialogCode::Accepted)
   {
     _cloud->clear();
     _guiUi->widget->resetPoints();
     RandomClouds::roughPlain(*_cloud, dialog.threshX(), dialog.threshY(), dialog.nPoints(), dialog.variance(), dialog.slopeX(), dialog.slopeY());
     this->drawPointCloud(*_cloud);
     this->update();
   }
}

void MainWindowLab::planeFit()
{
  if(!_cloud->size())
  {
    qDebug() << __PRETTY_FUNCTION__ << " cloud empty";
    return;
  }
  _guiUi->widget->resetLines();
  _guiUi->widget->clearPlanes();
  stdVecEig3f bfr;
  for(auto& iter : *_cloud)
    bfr.push_back(Eigen::Vector3f(iter.x, iter.y, iter.z));
 Eigen::Vector3f param = leastSquarePlaneFit(bfr);   
 qDebug() << __PRETTY_FUNCTION__ << " result " << param.x() << " " << param.y() << " " << param.z();

 Eigen::Vector3f origin(-1.0, -1.0, -1.0 * param.x() + -1.0 * param.y() + param.z());
 Eigen::Vector3f point0(-1.0, 1.0, -1.0 * param.x() + 1.0 * param.y() + param.z());
 Eigen::Vector3f point1(1.0, -1.0, 1.0 * param.x() + -1.0 * param.y() + param.z());

 stdVecEig3f origins;
 origins.push_back(origin);
 stdVecEig3f points0;
 points0.push_back(point0);
 stdVecEig3f points1;
 points1.push_back(point1);

 _guiUi->widget->drawPlanes(points0, points1, origins, Qt::black);
const float slopeY = (point0.z() - origin.z()) / 2.0;
const float slopeX = (point1.z() - origin.z()) / 2.0;

qDebug() << __PRETTY_FUNCTION__ << "slopexy (" << slopeX << " / " << slopeY << ")";
this->update();
}

void MainWindowLab::singDecom()
{
 
  if(!_cloud->size())
  {
    qDebug() << __PRETTY_FUNCTION__ << " cloud empty";
    return;
  }
  _guiUi->widget->clearPlanes();
  _guiUi->widget->resetLines();
  stdVecEig3f bfr;
  for(auto& iter : *_cloud)
    bfr.push_back(Eigen::Vector3f(iter.x, iter.y, iter.z));   

  Eigen::MatrixXd* axes = pcaAnalysis(bfr);

  std::cout << __PRETTY_FUNCTION__ << "axes\n" << *axes << std::endl;

  Line xAxis(Eigen::Vector3d((*axes)(0, 0), (*axes)(0, 2), (*axes)(0, 4)), Eigen::Vector3d((*axes)(0, 1), (*axes)(0, 3), (*axes)(0, 5)));
  xAxis._color = Qt::red;
  Line yAxis(Eigen::Vector3d((*axes)(1, 0), (*axes)(1, 2), (*axes)(1, 4)), Eigen::Vector3d((*axes)(1, 1), (*axes)(1, 3), (*axes)(1, 5)));
  yAxis._color = Qt::green;
  _guiUi->widget->addLine(xAxis);
  _guiUi->widget->addLine(yAxis);
  _guiUi->widget->drawLines();

  Eigen::Vector3f v0 = Eigen::Vector3f((*axes)(0, 1), (*axes)(0, 3), (*axes)(0, 5)) - Eigen::Vector3f((*axes)(0, 0), (*axes)(0, 2), (*axes)(0, 4));
  Eigen::Vector3f v1 = Eigen::Vector3f((*axes)(1, 1), (*axes)(1, 3), (*axes)(1, 5)) - Eigen::Vector3f((*axes)(1, 0), (*axes)(1, 2), (*axes)(1, 4));
  Eigen::Vector3f n = v0.cross(v1);
  Eigen::Vector3f subbo(1.0f, 0.0f, 0.0f);
  Eigen::Vector3f subboInEcht(0.0f, 1.0f, 0.0f);
  const float sloapX = -M_PI / 2.0 + std::acos(n.dot(subbo) / (n.norm() * subbo.norm()));
const float sloapY = -M_PI / 2.0 + std::acos(n.dot(subboInEcht) / (n.norm() * subboInEcht.norm()));
qDebug() << __PRETTY_FUNCTION__ << " slope x / y " << sloapX << " " << sloapY;
}