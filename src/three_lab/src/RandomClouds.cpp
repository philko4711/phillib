#include "RandomClouds.h"
#include <cmath>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/centroid.h>
#include <pcl/common/transforms.h>
#include <random>

void RandomClouds::roughPlain(pcl::PointCloud<pcl::PointXYZ>& cloud, const float threshX, const float threshY, const unsigned int nPoints,
                              const float zVariance)
{
  std::random_device                rd;
  std::default_random_engine        gen(rd());
  std::uniform_real_distribution<>  dist_x(-threshX, threshX);
  std::uniform_real_distribution<>  dist_y(-threshY, threshY);
  std::uniform_real_distribution<>  dist_roughness(-zVariance, zVariance);
  pcl::CentroidPoint<pcl::PointXYZ> centroid;

  for(unsigned int i = 0; i < nPoints; i++)
  {
    pcl::PointXYZ point(dist_x(gen), dist_y(gen), dist_roughness(gen));
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