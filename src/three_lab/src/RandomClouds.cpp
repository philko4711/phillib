#include "RandomClouds.h"
#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/centroid.h>
#include <pcl/common/transforms.h>
#include <random>
#include <QDebug>

void RandomClouds::roughPlain(pcl::PointCloud<pcl::PointXYZ>& cloud, const float threshX, const float threshY, const unsigned int nPoints,
                              const float zVariance, const float slopeX, const float slopeY)
{
  std::random_device                rd;
  std::default_random_engine        gen(rd());
  std::uniform_real_distribution<>  dist_x(-threshX, threshX);
  std::uniform_real_distribution<>  dist_y(-threshY, threshY);
  std::uniform_real_distribution<>  dist_variance(-zVariance, zVariance);
  pcl::CentroidPoint<pcl::PointXYZ> centroid;


  Eigen::Vector3f p0(-threshX, -threshY, 0.0);
  Eigen::Vector3f v0(threshX, -threshY, threshX * 2.0 * slopeX);
  v0 = v0 - p0;
  Eigen::Vector3f v1(-threshX, threshY, threshY * 2.0 * slopeY);
  v1 = v1 - p0;
  Eigen::Vector3f n = v0.cross(v1);

  for(unsigned int i = 0; i < nPoints; i++)
  {
    const float pX = dist_x(rd);
    const float pY = dist_y(rd);
    const float c0 = (pX - p0.x()) * n.x() + (pY - p0.y()) * n.y();
    const float c1 = p0.z() * n.z();
     float pZ = (c1 - c0) / n.z() + dist_variance(rd);
    if(std::isnan(pZ))
      pZ = 0.0f;
    
    pcl::PointXYZ point(pX, pY, pZ);
     centroid.add(point);
     cloud.push_back(point);
  }
  pcl::PointXYZ center;
  centroid.get(center);
  Eigen::Affine3f transform = Eigen::Affine3f::Identity();
  transform.translation() << -center.x, -center.y, 0.0f;
  pcl::transformPointCloud(cloud, cloud, transform);
}

void RandomClouds::slopedRoughPlain(pcl::PointCloud<pcl::PointXYZ>& cloud, const float threshX, const float threshY, 
                                    const float resolution, const float slopeX, const float slopeY, const float zVariance)
 {
   std::random_device                rd;
  std::default_random_engine        gen(rd());
  std::uniform_real_distribution<>  dist_z(-zVariance / 2.0f, zVariance / 2.0f);
   const unsigned int nPointsX = static_cast<unsigned int>(std::round(2.0 * threshX) / resolution);
   const unsigned int nPointsY = static_cast<unsigned int>(std::round(2.0 * threshY) / resolution);
   Eigen::Vector3f start(-threshX, -threshY, 0.0);
   Eigen::Vector3f v0(resolution, 0.0f, slopeX);
   Eigen::Vector3f v1(0.0f, resolution, slopeY);
   for(unsigned int i = 0; i < nPointsY; i++)
    for(unsigned int j = 0; j < nPointsX; j++)
    {
       pcl::PointXYZ point(start(0) + static_cast<float>(j) * v0(0) + static_cast<float>(i) * v1(0), 
                           start(1) + static_cast<float>(j) * v0(1) + static_cast<float>(i) * v1(1),
                           start(2) + static_cast<float>(j) * v0(2) + static_cast<float>(i) * v1(2) + dist_z(gen));
      cloud.push_back(point);
    }
 }