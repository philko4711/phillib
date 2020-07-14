#ifndef MATHCLOUDS_H_
#define MATHCLOUDS_H_

#include <Eigen/Dense>
#include "typedefs.h"

Eigen::Vector3f leastSquarePlaneFit(const stdVecEig3f& pointCloud);
Eigen::MatrixXd* pcaAnalysis(const stdVecEig3f& cloud);

#endif