/*
 * typedefs.h
 *
 *  Created on: Mar 21, 2015
 *      Author: phil
 */

#ifndef SRC_OHM_TRAVERSABILITY_SRC_MISCELLANEOUS_TYPEDEFS_H_
#define SRC_OHM_TRAVERSABILITY_SRC_MISCELLANEOUS_TYPEDEFS_H_

#include <vector>
#include <Eigen/Dense>
#include <Eigen/StdVector>

typedef std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d> > stdVecEig3d;
typedef std::vector<Eigen::Vector3f, Eigen::aligned_allocator<Eigen::Vector3f> > stdVecEig3f;
typedef std::vector<Eigen::Vector2i, Eigen::aligned_allocator<Eigen::Vector2i> > stdVecEig2i;
typedef std::vector<Eigen::Vector3i, Eigen::aligned_allocator<Eigen::Vector3i> > stdVecEig3i;

#endif /* SRC_OHM_TRAVERSABILITY_SRC_MISCELLANEOUS_TYPEDEFS_H_ */
