#include "ProjectionPinHole.h"
#include <stdexcept>
namespace phillib
{
namespace utils
{
ProjectionPinHole::ProjectionPinHole(std::vector<float>& projectionData)
{
  if(projectionData.size() != 12)
    throw std::invalid_argument("Input data size wrong (!= 12)\n");
  _P = Eigen::Map<Eigen::Matrix<float, 3, 4, Eigen::RowMajor> >(projectionData.data());
}
const Eigen::Vector2i ProjectionPinHole::pixel(const Eigen::Vector3f& point)
{
  Eigen::Vector2i pxl(0, 0);
  Eigen::Vector4f cordsHom(point.x(), point.y(), point.z(), 1.0f);
  pxl = _P * cordsHom;
  return pxl;
}
const Eigen::Vector3i ProjectionPinHole::point(const Eigen::Vector2i& pixel, const float w) {
  return Eigen::Vector3f(0.0f, 0.0f, 0.0f);
}
} // namespace utils
} // namespace phillib
