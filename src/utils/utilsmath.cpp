#include "utilsmath.h"

#include <iostream>

namespace phillib
{

namespace utils
{

float meanHeight(const stdVecEig3f& pointCloud) // toDO: this method has a wrong name..should be meanZ something
{
  if(!pointCloud.size())
  {
    std::cout << __PRETTY_FUNCTION__ << " error! Invalid cloud" << std::endl;
    return NAN;
  }
  float mean = 0.0;
  for(auto& iter : pointCloud)
    mean += iter.z();
  mean /= static_cast<float>(pointCloud.size());
  return mean;
}

float varianceHeight(const stdVecEig3f& points, const float mean)
{
  if(!points.size())
  {
    std::cout << __PRETTY_FUNCTION__ << " error! Invalid cloud" << std::endl;
    return NAN;
  }
  float variance = 0.0;
  for(auto& iter : points)
  {
    variance += (iter.z() - mean) * (iter.z() - mean);
  }

  variance /= static_cast<float>(points.size());
  return variance;
}

void minMaxHeight(const stdVecEig3f& pointCloud, float& min, float& max)
{
  stdVecEig3f copy = pointCloud;
  std::sort(copy.begin(), copy.end(), [](const Eigen::Vector3f& a, const Eigen::Vector3f& b) { return a.z() < b.z(); });
  min = copy.front().z();
  max = copy.back().z();
}

}

}