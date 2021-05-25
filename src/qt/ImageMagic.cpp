#include "ImageMagic.h"
#include <vtkRenderWindow.h>
#include <phillib_utils/ProjectionPinHole.h>
#include <pcl/common/transforms.h>

namespace phillib
{
namespace qt
{
ImageMagic::ImageMagic(const std::string& pathToImage, const std::string& pathToPcl):
_pcl(std::make_unique<pcl::PointCloud<pcl::PointXYZ> >())
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
  _viewer.updatePlaneImage(_viewer.actorPlaneImage(), _imageCamera);
  }

  ImageMagic::ImageMagic():
  _pcl(nullptr)
  {
    _viewer.resize(800, 800);
    _viewer.show();
    _viewer.addPlane(Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3f(0.0f, 0.0f, 0.0f), std::string("dummy"));
    connect(&_timer, SIGNAL(timeout()), this, SLOT(callBackTimer()));
    _timer.start(1000);
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
    std::vector<float> p = {561.065430/2, 0.0, 318.726308/2.0, 0.0,
  										0.0, 562.793762/2.0, 249.564153/2, 0.0,
  										0.0, 0.0, 1.0, 0.000000};
    phillib::utils::ProjectionPinHole P(p);
  }
  void ImageMagic::transformChanged()
  {
    if(!_pcl)
      return;
    auto T = _menuTransform.T();
    pcl::transformPointCloud(*_pcl, *_pcl, T);
    _viewer.drawPoints(*_pcl);
  }
}
}
