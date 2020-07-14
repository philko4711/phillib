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
    
    c(0) += iter.x() * iter.z();
    c(1) += iter.y() * iter.z();
    c(2) += iter.z();
  }
  m(2, 2) = static_cast<float>(pointCloud.size());
  Eigen::Vector3f sol = m.inverse() * c;
  return sol;

}

Eigen::MatrixXd* pcaAnalysis(const stdVecEig3f& cloud)
{

  const unsigned int width = cloud.size();
  Eigen::MatrixXd M;
  M.resize(width, 3);
  for(unsigned int i = 0; i < width; i++)
  {
    M(i, 0) = cloud[i].x();
    M(i, 1) = cloud[i].y();
    M(i, 2) = cloud[i].z();
  }


  //  Eigen::MatrixXd M = _M;
  Eigen::VectorXd centroid =  M.colwise().mean();
  Eigen::MatrixXd centered = M.rowwise() - M.colwise().mean();
  Eigen::MatrixXd cov = centered.adjoint() * centered;
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);

  unsigned int dim = M.cols();
  Eigen::MatrixXd* axes = new Eigen::MatrixXd;
  axes->resize(3, 6);    //todo: magic numbers

  //cout << "eigenvalues" << endl;
  //cout << eig.eigenvalues() << endl;

  //cout << "V" << endl;
  //cout << eig.eigenvectors().rightCols(3) << endl;

  Eigen::MatrixXd Vtmp = eig.eigenvectors();
  for(unsigned int i=0; i<Vtmp.cols(); i++)
    if(eig.eigenvalues()(i) < 0) Vtmp.col(i) *= -1;

  Eigen::MatrixXd V = Vtmp;
  for(unsigned int i=0; i<V.cols(); i++)
    V.col(i) = Vtmp.col(V.cols()-i-1);

  //cout << "V2" << endl;
  //cout << V << endl;

  Eigen::MatrixXd P = V.transpose() * centered.transpose();

  //cout << "P" << endl;
  //cout << P << endl;

  for(unsigned int i=0; i<dim; i++)
  {
    // corresponding eigenvector in original coordinate system
    double max = P.row(i).maxCoeff();
    double min = P.row(i).minCoeff();
    double ext = max - min;
    double align = 0.0;
    if(ext > 1e-6)
    {
      align = (max + min)/2.0;
    }

    for(size_t j=0; j<dim; j++)
    {
      double e = V(j, i)*align;
      centroid(j) += e;
    }

    //cout << "max/min/ext/align: " << max << " " << min << " " << ext << " " << align << endl;
  }

  for(unsigned int i=0; i<dim; i++)
  {
    //cout << "cent: " << centroid(i) << endl;
    // extends of axis in orientation of eigenvector i
    double ext = P.row(i).maxCoeff() - P.row(i).minCoeff();

    // coordinates of axis j
    for(size_t j=0; j<dim; j++)
    {
      double e = V.col(i)(j)*ext/2.0;
      // axis coordinates with respect to center of original coordinate system
      (*axes)(i, 2*j) = centroid(j) - e;
      (*axes)(i, 2*j+1) = centroid(j) + e;
    }
  }

  return axes;
}