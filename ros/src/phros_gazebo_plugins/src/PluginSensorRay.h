#ifndef PLUGIN_SENSOR_RAY_h
#define PLUGIN_SENSOR_RAY_h

#include <string>

#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include <ros/advertise_options.h>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include <gazebo/common/Events.hh>
#include <gazebo/common/Plugin.hh>
#include <gazebo/common/Time.hh>
#include <gazebo/msgs/MessageTypes.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/plugins/RayPlugin.hh>
#include <gazebo/sensors/SensorTypes.hh>
#include <gazebo/transport/TransportTypes.hh>

#include <sdf/sdf.hh>

#include <gazebo_plugins/PubQueue.h>

namespace gazebo
{

class PluginSensorRay : public RayPlugin
{
public:
  PluginSensorRay();
  virtual ~PluginSensorRay();
  virtual void Load(sensors::SensorPtr parent, sdf::ElementPtr sdf);

private:
  void loadThread();
  void laserConnect();
  void laserDisconnect();
  void OnScan(ConstLaserScanStampedPtr& msg);
  sensors::RaySensorPtr _parentRaySensor;
  physics::WorldPtr _world;
  gazebo::transport::NodePtr _gazeboNode;
  gazebo::transport::SubscriberPtr _laserScanSub;
  ros::NodeHandle _nh;
  ros::Publisher   _pub;
  sdf::ElementPtr  _sdf;
  //boost::thread _deferredLoadThread;
  
  int _laserConnectCount;
  PubMultiQueue _pmq;
  PubQueue<sensor_msgs::LaserScan>::Ptr _pubQueue;
   std::string _tfFrameSensor;
};

} // namespace gazebo

#endif
