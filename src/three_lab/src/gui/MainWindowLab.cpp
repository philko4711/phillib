#include "MainWindowLab.h"
#include "DialogSlopedCloud.h"
#include "RandomClouds.h"
#include "mathClouds.h"
#include <memory>
#include <QDebug>
MainWindowLab::MainWindowLab():
_guiUi(std::unique_ptr<Ui::MainWindowThLab>(new Ui::MainWindowThLab())),
_cloud(std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> >(new pcl::PointCloud<pcl::PointXYZ>()))
{
  _guiUi->setupUi(this);
  _guiUi->widget->drawAxissystem();
  connect(_guiUi->actionCreateRandomPlane, SIGNAL(triggered()), this, SLOT(slopedInput()));
  connect(_guiUi->actionPlaneFit, SIGNAL(triggered()), this, SLOT(planeFit()));
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
void MainWindowLab::planeFit()
{
  if(!_cloud->size())
  {
    qDebug() << __PRETTY_FUNCTION__ << " cloud empty";
    return;
  }
  stdVecEig3f bfr;
  for(auto& iter : *_cloud)
    bfr.push_back(Eigen::Vector3f(iter.x, iter.y, iter.z));
 Eigen::Vector3f param = leastSquarePlaneFit(bfr);   
 qDebug() << __PRETTY_FUNCTION__ << " result " << param.x() << " " << param.y() << " " << param.z();

}