#include "PluginSensorRay.h"
#include <boost/algorithm/string/trim.hpp>
#include <gazebo/sensors/SensorTypes.hh>
#include <gazebo/transport/Node.hh>
#include <gazebo_plugins/gazebo_ros_utils.h>
#include <pcl_ros/point_cloud.h>

namespace gazebo
{

PluginSensorRay::PluginSensorRay() {}

PluginSensorRay::~PluginSensorRay() {}

void PluginSensorRay::Load(sensors::SensorPtr parent, sdf::ElementPtr sdf)
{
  std::cout << __PRETTY_FUNCTION__ << " huhu " << std::endl;
  _sdf = sdf;
  RayPlugin::Load(parent, sdf);
  //std::string worldName = parent->GetWorldName();
  _world = physics::get_world();//worldName);

  GAZEBO_SENSORS_USING_DYNAMIC_POINTER_CAST;
  _parentRaySensor = dynamic_pointer_cast<sensors::RaySensor>(parent);
  //std::string frameName;
  if(!_parentRaySensor)
    gzthrow("GazeboRosLaser controller requires a Ray Sensor as its parent");
  if(!_sdf->HasElement("frame_name"))
  {
    ROS_INFO("GazeboRosLaser plugin missing <frameName>, defaults to /world");
    _tfFrameSensor = "/world";
  }
  else
    _tfFrameSensor = _sdf->Get<std::string>("frame_name");

  std::string topicName;
  if(!_sdf->HasElement("topic_name"))
  {
    ROS_INFO("GazeboRosLaser plugin missing <topicName>, defaults to "
             "/velodyne_points");
    topicName = "/velodyne_points";
  }
  else
    topicName = _sdf->Get<std::string>("topic_name");

  if(!ros::isInitialized())
  {
    ROS_ERROR_STREAM("Error. Ros-Gazebo Api not found. Start gazebo in ros environment");
    gzthrow("RosRayPlugin Ros-Api-Error");
  }
  _gazeboNode = gazebo::transport::NodePtr(new gazebo::transport::Node());
  _gazeboNode->Init(_world->Name());

  _pub = _nh.advertise<sensor_msgs::LaserScan>(topicName, 1);
  _laserScanSub = _gazeboNode->Subscribe(_parentRaySensor->Topic(), &PluginSensorRay::OnScan, this);
  _parentRaySensor->SetActive(false);
}

void PluginSensorRay::OnScan(ConstLaserScanStampedPtr& msg)
{
  //std::cout << __PRETTY_FUNCTION__ << " entry " << std::endl;
   sensor_msgs::LaserScan laserMsg;
   laserMsg.header.stamp          = ros::Time::now();
   laserMsg.header.frame_id       = _tfFrameSensor;
   laserMsg.angle_min = msg->scan().angle_min();
   laserMsg.angle_max = msg->scan().angle_max();
   laserMsg.angle_increment = msg->scan().angle_step();
   laserMsg.time_increment = 0;  // instantaneous simulator scan
   laserMsg.scan_time = 0;  // not sure whether this is correct
   laserMsg.range_min = msg->scan().range_min();
   laserMsg.range_max = msg->scan().range_max();
   laserMsg.ranges.resize(msg->scan().ranges_size());
   std::copy(msg->scan().ranges().begin(),
       msg->scan().ranges().end(),
       laserMsg.ranges.begin());
   laserMsg.intensities.resize(msg->scan().intensities_size());
   std::copy(msg->scan().intensities().begin(),
       msg->scan().intensities().end(),
       laserMsg.intensities.begin());
  
  _pub.publish(laserMsg);
  //_pubQueue->push(laserMsg, _pub);
}
GZ_REGISTER_SENSOR_PLUGIN(PluginSensorRay)
} // namespace gazebo