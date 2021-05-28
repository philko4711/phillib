#include "ProjectionPinHole.h"
#include <stdexcept>
#include <iostream>
namespace phillib
{
namespace utils
{
ProjectionPinHole::ProjectionPinHole(std::vector<float>& projectionData)
{
  if(projectionData.size() != 12)
    throw std::invalid_argument("Input data size wrong (!= 12)\n");
  _P = Eigen::Map<Eigen::Matrix<float, 3, 4, Eigen::RowMajor> >(projectionData.data());
  //std::cout << __PRETTY_FUNCTION__ << std::endl << _P << std::endl;
}
const Eigen::Vector2i ProjectionPinHole::pixel(const Eigen::Vector3f& point)
{
  Eigen::Vector3f pxl(0.0f, 0.0f, 0.0f);
  Eigen::Vector4f cordsHom(point.x(), point.y(), point.z(), 1.0f);
  pxl = _P * cordsHom;
  //std::cout << __PRETTY_FUNCTION__ << " pixel: " <<std::endl << pxl << std::endl;
  float var = std::floor(pxl.x() / pxl.z());
  int vari = static_cast<int>(var);
  // std::cout << __PRETTY_FUNCTION__ << " var: " <<std::endl << var << std::endl;
  // std::cout << __PRETTY_FUNCTION__ << " vari: " <<std::endl << vari << std::endl;
  Eigen::Vector2i intPixel(static_cast<int>(std::floor(pxl.x() / pxl.z())), static_cast<int>(std::floor(pxl.y() / pxl.z())));
  //std::cout << __PRETTY_FUNCTION__ << " intpixel: " <<std::endl << intPixel << std::endl;
  return intPixel;
}
const Eigen::Vector3f ProjectionPinHole::point(const Eigen::Vector2i& pixel, const float w) {
  return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
}
} // namespace utils
} // namespace phillib
