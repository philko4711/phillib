#include "ImageMagic.h"
#include <vtkRenderWindow.h>
#include <phillib_utils/ProjectionPinHole.h>
#include <pcl/common/transforms.h>
#include <phillib_utils/typedefs_eigen.h>

namespace phillib
{
namespace qt
{
ImageMagic::ImageMagic(const std::string& pathToImage, const std::string& pathToPcl):
_pcl(std::make_unique<pcl::PointCloud<pcl::PointXYZ> >()),
_pclVar(std::make_unique<pcl::PointCloud<pcl::PointXYZ> >())
  {
    _viewer.resize(800, 800);
    _viewer.show();
    _viewer.addPlane(Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3f(0.0f, 0.0f, 0.0f), pathToImage);
    _viewer.drawPoints(pathToPcl);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(callBackTimer()));
    connect(&_menuTransform, SIGNAL(transformChanged()), this, SLOT(transformChanged()));
    _timer.start(1000);
   pcl::PLYReader reader;
  reader.read(pathToPcl, *_pcl);
  const bool retval = _imageCamera.load(pathToImage.c_str());
  if(retval)
    std::cout << " loaded image with " << _imageCamera.width() << " x " << _imageCamera.height() << " size" << std::endl;
  else
    throw std::invalid_argument(std::string("Error ") + pathToImage + std::string(" invalid"));
  _imageCamera = _imageCamera.rgbSwapped();    
  _viewer.updatePlaneImage(_viewer.actorPlaneImage(), _imageCamera);
  _imageCamera.save("/tmp/picture.jpg");
  }

  ImageMagic::ImageMagic():
  _pcl(nullptr)
  {
    _viewer.resize(800, 800);
    _viewer.show();
    _viewer.addPlane(Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3f(0.0f, 0.0f, 0.0f), std::string("dummy"));
    // connect(&_timer, SIGNAL(timeout()), this, SLOT(callBackTimer()));
    // _timer.start(1000);
  }
  void ImageMagic::callBackTimer()
  {
    // if(!_viewer.actorPlaneImage())
    //   return;
    // _viewer.updatePlaneImage(_viewer.actorPlaneImage());
    // _viewer.renderWindow()->Render();
  }
  void ImageMagic::backProject()
  {
    pcl::PointCloud<pcl::PointXYZ> cloud;
    static std::vector<float> p = {561.065430/2, 0.0, 318.726308/2.0, 0.0,
  										0.0, 562.793762/2.0, 249.564153/2, 0.0,
  										0.0, 0.0, 1.0, 0.000000};
    static phillib::utils::ProjectionPinHole P(p);
    unsigned int ctr = 0;
    for(auto& iter : *_pclVar)
    {
      auto pxl = P.pixel(Eigen::Vector3f(iter.x, iter.y, iter.z));
      // if((pxl.x() < 0) || (pxl.y() < 0) || (pxl.x() >= _imageCamera.width()) || (pxl.y() >= _imageCamera.height()))
      //   continue;
      // else  
      //   ctr++;
      pcl::PointXYZ p(static_cast<float>(pxl.x()), static_cast<float>(pxl.y()), 0.0f);
      // std::cout << __PRETTY_FUNCTION__ <<std::endl << iter << std::endl;
      // std::cout << __PRETTY_FUNCTION__ <<std::endl << p << std::endl;
      // std::cout << __PRETTY_FUNCTION__ <<std::endl << pxl << std::endl;
      cloud.push_back(p);
    }
    // if(ctr)
       //std::cout << __PRETTY_FUNCTION__ << cloud.size() << " elements  in cloud" << std::endl;
    _viewer.drawPoints(cloud);
  }
  void ImageMagic::forwardProject(pcl::PointCloud<pcl::PointXYZ>& cloud)
  {
   // std::vector<phillib::utils::stdVecEig3f> map(1000)
  }
  void ImageMagic::transformChanged()
  {
    if(!_pcl)
      return;
    auto T = _menuTransform.T();
    pcl::transformPointCloud(*_pcl, *_pclVar, T);
    //_viewer.drawPoints(*_pclVar);
    
  this->backProject();  
  _viewer.GetRenderWindow()->Render();
  }
}
}
