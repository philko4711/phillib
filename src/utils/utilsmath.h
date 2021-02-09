#ifndef PHILLIB_UTILS_UTILSMATH_H_
#define PHILLIB_UTILS_UTILSMATH_H_

#include "typedefs_eigen.h"

namespace phillib
{

namespace utils
{
float meanHeight(const stdVecEig3f& pointCloud);
float varianceHeight(const stdVecEig3f& points, const float mean);
void minMaxHeight(const stdVecEig3f& pointCloud, float& min, float& max);
}

} // namespace phillib

#endif
