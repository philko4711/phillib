#include "MainWindowLab.h"
#include "DialogSlopedCloud.h"
#include "RandomClouds.h"
#include <memory>
#include <QDebug>
MainWindowLab::MainWindowLab():
_guiUi(std::unique_ptr<Ui::MainWindowThLab>(new Ui::MainWindowThLab()))
{
  _guiUi->setupUi(this);
  _guiUi->widget->drawAxissystem();
  connect(_guiUi->actionCreateRandomPlane, SIGNAL(triggered()), this, SLOT(slopedInput()));
}

void MainWindowLab::slopedInput()
{
   static DialogSlopedCloud dialog; 
   int retval = dialog.exec();
   if(retval == QDialog::DialogCode::Accepted)
   {
     pcl::PointCloud<pcl::PointXYZ> cloud;
     RandomClouds::slopedRoughPlain(cloud, dialog.threshXdim(), dialog.threshYdim(), dialog.resolution(), 
                                    dialog.slopeX(), dialog.slopeY(), dialog.zVariance());
     _guiUi->widget->resetPoints();
     this->drawPointCloud(cloud);
     this->update();
   }
   else
   {
     return;
   }
   
}