/*
 * PluginSensorVelodyne.h
 *
 *  Created on: May 5, 2016
 *      Author: phil
 */

#ifndef ROS_SRC_GAZEBO_PLUGINS_SRC_PLUGINSENSORVELODYNE_H_
#define ROS_SRC_GAZEBO_PLUGINS_SRC_PLUGINSENSORVELODYNE_H_


#include <string>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <ros/ros.h>
#include <ros/advertise_options.h>
#include <sensor_msgs/LaserScan.h>
#include <pcl_ros/point_cloud.h>

#include <gazebo/physics/physics.hh>
#include <gazebo/transport/TransportTypes.hh>
#include <gazebo/msgs/MessageTypes.hh>
#include <gazebo/common/Time.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Events.hh>
#include <gazebo/sensors/SensorTypes.hh>
#include <gazebo/plugins/GpuRayPlugin.hh>

#include <sdf/sdf.hh>

#include <gazebo_plugins/PubQueue.h>

namespace gazebo
{

class PluginSensorVelodyne : public GpuRayPlugin
{
public:
  PluginSensorVelodyne();
  virtual ~PluginSensorVelodyne();
  virtual void Load(sensors::SensorPtr parent, sdf::ElementPtr sdf);
private:
  void loadThread();
  void laserConnect();
  void laserDisconnect();
  void OnScan(ConstLaserScanStampedPtr& msg);
  void OnMsg(ConstVector3dPtr &_msg);
  std::string _worldName;
  physics::WorldPtr _world;
  sensors::GpuRaySensorPtr _parentRaySensor;
  ros::NodeHandle* _rosNode;
  ros::Publisher   _pub;
  std::string      _frameName;
  std::string      _tfPrefix;
  sdf::ElementPtr  _sdf;
  boost::thread _deferredLoadThread;
  unsigned int  _seed;
  gazebo::transport::NodePtr _gazeboNode;
  gazebo::transport::SubscriberPtr _laserScanSub;
  std::string _robotNameSpace;
  std::string _topicName;
  int _laserConnectCount;
  PubMultiQueue _pmq;
  PubQueue<pcl::PointCloud<pcl::PointXYZ> >::Ptr _pubQueue;
   transport::SubscriberPtr _sub;
   transport::NodePtr _node;
   double _angle;
};

}

#endif
