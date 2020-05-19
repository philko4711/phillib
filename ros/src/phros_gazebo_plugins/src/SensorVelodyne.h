#ifndef SENSOR_VELODYNE_H_
#define SENSOR_VELODYNE_H_


#include <memory>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <tf/transform_listener.h>
#include <string>
#include <pcl_ros/point_cloud.h>

class SensorVelodyne
{
public:
  SensorVelodyne();
  virtual ~SensorVelodyne();
  void start(){this->run();}
private:
  void                                   callBackScan(const sensor_msgs::LaserScan& scan);
  void run(){ros::spin(); }
  ros::NodeHandle                        _nh;
  ros::Subscriber                        _subsScan;
  ros::Publisher _pubCloud;
  std::unique_ptr<tf::TransformListener> _listener;
  std::string _tfBaseFrame;
  std::unique_ptr<pcl::PointCloud<pcl::PointXYZ> > _cloud;
};

#endif