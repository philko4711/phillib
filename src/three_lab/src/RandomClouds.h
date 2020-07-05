#ifndef RANDOM_CLOUDS_H_
#define RANDOM_CLOUDS_H_

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

class RandomClouds
{
  public: 
    static void roughPlain(pcl::PointCloud<pcl::PointXYZ>& cloud, const float threshX, const float threshY, const unsigned int nPoints,
                                    const float zVariance);
    static void slopedRoughPlain(pcl::PointCloud<pcl::PointXYZ>& cloud, const float threshX, const float threshY, const float resolution, const float slopeX, const float slopeY, 
                                 const float zVariance);                                  
};

#endif