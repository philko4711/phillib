#ifndef PHILLIB_UTILS_TYPEDEFS_EIGEN_H_
#define PHILLIB_UTILS_TYPEDEFS_EIGEN_H_

#include <vector>
#include <Eigen/Dense>
#include <Eigen/StdVector>

namespace phillib
{
    namespace utils
    {  
        typedef std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> stdVecEig3d;
        typedef std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f>> stdVecEig3f;
        typedef std::vector<Eigen::Vector2i, Eigen::aligned_allocator<Eigen::Vector2i>> stdVecEig2i;
        typedef std::vector<Eigen::Vector3i, Eigen::aligned_allocator<Eigen::Vector3i>> stdVecEig3i;

    } // namespace utils

} // namespace phillib

#endif /* PHILLIB_UTILS_TYPEDEFS_EIGEN_H_ */