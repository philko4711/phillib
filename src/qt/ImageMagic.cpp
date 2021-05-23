#include "ImageMagic.h"

namespace phillib
{
namespace qt
{
ImageMagic::ImageMagic(const std::string& pathToImage, const std::string& pathToPcl)
  {
    _viewer.resize(800, 800);
    _viewer.show();
    _viewer.addPlane(Eigen::Vector3f(1.0f, 0.0f, 0.0f), Eigen::Vector3f(0.0f, 1.0f, 0.0f), Eigen::Vector3f(0.0f, 0.0f, 0.0f), pathToImage);
    _viewer.drawPoints(pathToPcl);
    //_viewer.addAxes();
  }


}
}
