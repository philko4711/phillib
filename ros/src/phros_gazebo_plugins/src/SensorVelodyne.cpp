#include "SensorVelodyne.h"
#include <laser_geometry/laser_geometry.h>
#include <pcl_ros/point_cloud.h>
#include <string>

SensorVelodyne::SensorVelodyne()
    : _listener(std::make_unique<tf::TransformListener>())
    , _cloud(std::make_unique<pcl::PointCloud<pcl::PointXYZ> >())
{
  ros::NodeHandle prvNh("~");
  std::string     topicScan;
  std::string     topicCloud;
  prvNh.param<std::string>("topic_scan", topicScan, "scan");
  prvNh.param<std::string>("topic_cloud", topicCloud, "velodyne_points");
  prvNh.param<std::string>("tf_base_frame", _tfBaseFrame, "base_link");
  _subsScan = _nh.subscribe(topicScan, 1, &SensorVelodyne::callBackScan, this);
  _pubCloud = _nh.advertise<pcl::PointCloud<pcl::PointXYZ> >(topicCloud, 1);
  _cloud->header.frame_id = _tfBaseFrame;
}

SensorVelodyne::~SensorVelodyne(){};

void SensorVelodyne::callBackScan(const sensor_msgs::LaserScan& scan)
{
  static double anglePrev = 0.0;
  laser_geometry::LaserProjection projector;
  if(!_listener->waitForTransform(scan.header.frame_id, _tfBaseFrame, scan.header.stamp + ros::Duration().fromSec(scan.ranges.size() * scan.time_increment),
                                  ros::Duration(1.0)))
  {
    ROS_ERROR_STREAM(__PRETTY_FUNCTION__ << "timeout looking up transform from " << scan.header.frame_id << " to " << _tfBaseFrame);
    return;
  }
  tf::StampedTransform tf;
  try
  {
    _listener->lookupTransform("velodyne::top", "velodyne::base", ros::Time(0), tf);
  }
  catch(tf::TransformException& ex)
  {
    std::cout << ex.what() << '\n';
    return;
  }
  double roll = 0.0;
  double pitch = 0.0;
  double yaw = 0.0;
  //tf::Quaternion quat = ;
  tf::Matrix3x3 mat(tf.getRotation());
  mat.getRPY(roll, pitch, yaw);
  std::cout << __PRETTY_FUNCTION__ << " rpy " << roll << " " << pitch << " " << yaw << std::endl;
  
  

  sensor_msgs::PointCloud cloud;
  projector.transformLaserScanToPointCloud(_tfBaseFrame, scan, cloud, *_listener);
  for(auto& iter : cloud.points)
  {
    pcl::PointXYZ pointPCL(iter.x, iter.y, iter.z);
    _cloud->push_back(pointPCL);
  }
  if((yaw * anglePrev < 0.0) && ((yaw * anglePrev > -0.5)))
  {
  _cloud->header.stamp = pcl_conversions::toPCL(ros::Time::now());
  _cloud->header.seq++;
  _pubCloud.publish(*_cloud);
  _cloud->clear();
  }
  anglePrev = yaw;
}
