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

std::shared_ptr<Eigen::MatrixXd> pcaAnalysis(const stdVecEig3f& cloud)
{

  const unsigned int width = cloud.size();
  Eigen::MatrixXd    M;
  M.resize(width, 3);
  for(unsigned int i = 0; i < width; i++)
  {
    M(i, 0) = cloud[i].x();
    M(i, 1) = cloud[i].y();
    M(i, 2) = cloud[i].z();
  }

  //  Eigen::MatrixXd M = _M;
  Eigen::VectorXd                                centroid = M.colwise().mean();
  Eigen::MatrixXd                                centered = M.rowwise() - M.colwise().mean();
  Eigen::MatrixXd                                cov      = centered.adjoint() * centered;
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);

  unsigned int                     dim  = M.cols();
  std::shared_ptr<Eigen::MatrixXd> axes = std::make_shared<Eigen::MatrixXd>(); // todo: this is a potential memory leak. Maybe use smart pointer?!
  axes->resize(3, 6);                                                          // todo: magic numbers

  // cout << "eigenvalues" << endl;
  // cout << eig.eigenvalues() << endl;

  // cout << "V" << endl;
  // cout << eig.eigenvectors().rightCols(3) << endl;

  Eigen::MatrixXd Vtmp = eig.eigenvectors();
  for(unsigned int i = 0; i < Vtmp.cols(); i++)
    if(eig.eigenvalues()(i) < 0)
      Vtmp.col(i) *= -1;

  Eigen::MatrixXd V = Vtmp;
  for(unsigned int i = 0; i < V.cols(); i++)
    V.col(i) = Vtmp.col(V.cols() - i - 1);

  // cout << "V2" << endl;
  // cout << V << endl;

  Eigen::MatrixXd P = V.transpose() * centered.transpose();

  // cout << "P" << endl;
  // cout << P << endl;

  for(unsigned int i = 0; i < dim; i++)
  {
    // corresponding eigenvector in original coordinate system
    double max   = P.row(i).maxCoeff();
    double min   = P.row(i).minCoeff();
    double ext   = max - min;
    double align = 0.0;
    if(ext > 1e-6)
    {
      align = (max + min) / 2.0;
    }

    for(size_t j = 0; j < dim; j++)
    {
      double e = V(j, i) * align;
      centroid(j) += e;
    }

    // cout << "max/min/ext/align: " << max << " " << min << " " << ext << " " << align << endl;
  }

  for(unsigned int i = 0; i < dim; i++)
  {
    // cout << "cent: " << centroid(i) << endl;
    // extends of axis in orientation of eigenvector i
    double ext = P.row(i).maxCoeff() - P.row(i).minCoeff();

    // coordinates of axis j
    for(size_t j = 0; j < dim; j++)
    {
      double e = V.col(i)(j) * ext / 2.0;
      // axis coordinates with respect to center of original coordinate system
      (*axes)(i, 2 * j)     = centroid(j) - e;
      (*axes)(i, 2 * j + 1) = centroid(j) + e;
    }
  }

  return axes;
}

}

}