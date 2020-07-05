#include "mathClouds.h"

Eigen::Vector3f leastSquarePlaneFit(const stdVecEig3f& pointCloud)
{

  Eigen::Matrix3f m;
  m.setZero();
  Eigen::Vector3f c;
  c.setZero();
  for(auto& iter : pointCloud)
  {
    m(0, 0) += iter.x() * iter.x(); 
    m(0, 1) += iter.x() * iter.y();
    m(0, 2) +=  iter.x();

    m(1, 0) = m(0, 1); 
    m(1, 1) += iter.y() * iter.y();
    m(1, 2) += iter.y();

    m(2, 0) = m(0, 2);
    m(2, 1) = m(1, 2);
    
    c(0) = iter.x() * iter.z();
    c(1) = iter.y() * iter.z();
    c(2) = iter.z();
  }
  m(2, 2) = static_cast<float>(pointCloud.size());
  Eigen::Vector3f sol = m.inverse() * c;
  return sol;

}