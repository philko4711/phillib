#ifndef PHILLIB_UTILS_PROJECTIONPINHOLE_H_
#define PHILLIB_UTILS_PROJECTIONPINHOLE_H_

#include <Eigen/Dense>
#include <vector>

namespace phillib
{
namespace utils
{
  class ProjectionPinHole
  {
    public:
    ProjectionPinHole(std::vector<float>& projectionData);
    virtual ~ProjectionPinHole(){}
    const Eigen::Vector2i pixel(const Eigen::Vector3f& point);
    const Eigen::Vector3i point(const Eigen::Vector2i& pixel, const float w);
    private:
      Eigen::Matrix<float, 3, 4> _P;
};
}
}
#endif

