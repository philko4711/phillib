/*
 * PluginSensorVelodyne.cpp
 *
 *  Created on: May 5, 2016
 *      Author: phil
 */

#include "PluginSensorVelodyne.h"
#include <boost/algorithm/string/trim.hpp>
#include <gazebo/sensors/GpuRaySensor.hh>
#include <gazebo/sensors/SensorTypes.hh>
#include <gazebo/transport/Node.hh>
#include <gazebo_plugins/gazebo_ros_utils.h>
#include <pcl_ros/point_cloud.h>

#include <tf/tf.h>
#include <tf/transform_listener.h>

namespace gazebo
{

PluginSensorVelodyne::PluginSensorVelodyne()
    : _seed(0)
    , _rosNode(NULL)
    , _laserConnectCount(0)
{
}

PluginSensorVelodyne::~PluginSensorVelodyne()
{
  ROS_DEBUG_STREAM_NAMED("velodyne_sensor_plugin", "Shutting down GPU Laser");
  _rosNode->shutdown();
  delete _rosNode;
  ROS_DEBUG_STREAM_NAMED("velodyne_sensor_plugin", "Unloaded");
}

void PluginSensorVelodyne::Load(sensors::SensorPtr parent, sdf::ElementPtr sdf)
{
  _sdf = sdf;
  GpuRayPlugin::Load(parent, sdf);
  // std::string _worldName = parent->GetWorldName();
  _world = physics::get_world(_worldName);

  GAZEBO_SENSORS_USING_DYNAMIC_POINTER_CAST;
  _parentRaySensor = dynamic_pointer_cast<sensors::GpuRaySensor>(parent);

  if(!_parentRaySensor)
    gzthrow("GazeboRosLaser controller requires a Ray Sensor as its parent");

  _robotNameSpace = GetRobotNamespace(parent, sdf, "Laser");

  if(!_sdf->HasElement("frameName"))
  {
    ROS_INFO("GazeboRosLaser plugin missing <frameName>, defaults to /world");
    _frameName = "/world";
  }
  else
    _frameName = _sdf->Get<std::string>("frameName");

  if(!_sdf->HasElement("topicName"))
  {
    ROS_INFO("GazeboRosLaser plugin missing <topicName>, defaults to "
             "/velodyne_points");
    _topicName = "/velodyne_points";
  }
  else
    _topicName = _sdf->Get<std::string>("topicName");

  // Make sure the ROS node for Gazebo has already been initialized
  if(!ros::isInitialized())
  {
    ROS_FATAL_STREAM("A ROS node for Gazebo has not been initialized, unable to load "
                     "plugin. "
                     << "Load the Gazebo system plugin 'libgazebo_ros_api_plugin.so' in the "
                        "gazebo_ros package)");
    return;
  }

  ROS_INFO("Starting GazeboRosLaser Plugin (ns = %s)!", _robotNameSpace.c_str());
  _deferredLoadThread = boost::thread(boost::bind(&PluginSensorVelodyne::loadThread, this));
  // if(parent->model->GetJointCount())
  // {
  //   std::cout << __PRETTY_FUNCTION__ << " no joint ...no fun" << std::endl;
  // }
  // else
  //   std::cout << __PRETTY_FUNCTION__ << " model contains " <<
  //   parent->GetJointCount() << " joints " << std::endl;
  // Subscribe to the topic, and register a callback
  // Create the node
  _node = transport::NodePtr(new transport::Node());
#if GAZEBO_MAJOR_VERSION < 8
  this->node->Init(this->model->GetWorld()->GetName());
#else
  _node->Init();
#endif

  //_sub = _node->Subscribe("motor_angle", &PluginSensorVelodyne::OnMsg, this);
  physics::ModelPtr model = _world->ModelByName("velodyne");  
  if(model)
  {
    _jointi = model->GetJoint("velodyne::joint");
    if(_jointi)
    {
      std::cout << " juhuuuu " << std::endl;
    }
  }
}

void PluginSensorVelodyne::loadThread()
{
  _gazeboNode = gazebo::transport::NodePtr(new gazebo::transport::Node());
  _gazeboNode->Init(_worldName);

  _pmq.startServiceThread();

  _rosNode = new ros::NodeHandle(_robotNameSpace);

  _tfPrefix = tf::getPrefixParam(*_rosNode);
  if(_tfPrefix.empty())
  {
    _tfPrefix = _robotNameSpace;
    boost::trim_right_if(_tfPrefix, boost::is_any_of("/"));
  }
  ROS_INFO("GPU Laser Plugin (ns = %s) <tf_prefix_>, set to \"%s\"", _robotNameSpace.c_str(), _tfPrefix.c_str());

  // resolve tf prefix
  _frameName = tf::resolve(_tfPrefix, _frameName);

  if(_topicName != "")
  {
    ros::AdvertiseOptions ao =
        ros::AdvertiseOptions::create<pcl::PointCloud<pcl::PointXYZ> >(_topicName, 1, boost::bind(&PluginSensorVelodyne::laserConnect, this),
                                                                       boost::bind(&PluginSensorVelodyne::laserDisconnect, this), ros::VoidPtr(), NULL);
    // ros::AdvertiseOptions ao =
    //     ros::AdvertiseOptions::create<sensor_msgs::LaserScan>(_topicName, 1, boost::bind(&PluginSensorVelodyne::laserConnect, this),
    //                                                                    boost::bind(&PluginSensorVelodyne::laserDisconnect, this), ros::VoidPtr(), NULL);
    _pub      = _rosNode->advertise(ao);
    _pubQueue = _pmq.addPub<pcl::PointCloud<pcl::PointXYZ> >();
    //_pubQueue = _pmq.addPub<sensor_msgs::LaserScan>();
  }

  // Initialize the controller
  // sensor generation off by default
  _parentRaySensor->SetActive(false);

  ROS_INFO_STREAM_NAMED("gpu_laser", "LoadThread function completed");
}

void PluginSensorVelodyne::laserConnect()
{
  _laserConnectCount++;
  if(_laserConnectCount == 1)
    _laserScanSub = _gazeboNode->Subscribe(_parentRaySensor->Topic(), &PluginSensorVelodyne::OnScan, this);
}
void PluginSensorVelodyne::laserDisconnect()
{
  _laserConnectCount--;
  if(_laserConnectCount == 0)
    _laserScanSub.reset();
}

void PluginSensorVelodyne::OnScan(ConstLaserScanStampedPtr& msg)
{
  _parentRaySensor->SetActive(false);
  // std::cout << __PRETTY_FUNCTION__ << " huhu " << std::endl;
  // const double       angleStep = 0.1;
  // const unsigned int n         = static_cast<unsigned int>(std::round((2.0 * M_PI) / angleStep));
  double popo = 0.0;
  if(_jointi)
  {
      double       pos = _jointi->Position();
    const double nTp = std::floor(pos / (2.0 * M_PI));
    pos              = pos - nTp * (2.0 * M_PI); 
    popo = pos;
  }

  std::cout << __PRETTY_FUNCTION__ << " popo " << popo << std::endl;
   static double      angleLast = _angle;
  // We got a new message from the Gazebo sensor.  Stuff a
  // corresponding ROS message and publish it.
  static pcl::PointCloud<pcl::PointXYZ> cloud;
  cloud.header.stamp                   = pcl_conversions::toPCL(ros::Time(msg->time().sec(), msg->time().nsec()));
  cloud.header.frame_id                = _frameName;
  const double angleMin                = (M_PI / 2.0) - 1.0 * msg->scan().angle_min();
  const double angleIncrement          = -1.0 * msg->scan().angle_step();
//unsigned int nSteps = 0;
  //std::cout << __PRETTY_FUNCTION__ << " min " << angleMin << " incr " << angleIncrement << std::endl;
//  std::cout << __PRETTY_FUNCTION__ << " (" << _angle  << " - "  << angleLast << ") > " << angleStep << " ? " << std::endl;
  // if((_angle - angleLast) > angleStep)
  // {
    for(unsigned int i = 0; i < msg->scan().ranges().size(); i++)
    {

      const double theta = angleMin + static_cast<double>(i) * angleIncrement;
      const double phi   = popo;
      const double r     = msg->scan().ranges()[i];
      // if(std::isinf(r))
      //   continue;
      //std::cout << __PRETTY_FUNCTION__ << " theta " << theta << " r " << r << " phi " << phi << " incr " << angleIncrement << std::endl;
      pcl::PointXYZ point(r * std::sin(theta) * std::cos(phi), r * std::sin(theta) * std::sin(phi), r * std::cos(theta)); //,
      //std::cout << __PRETTY_FUNCTION__ << " x = " << r * std::sin(theta) << " y = " << r * std::cos(theta) << std::endl;
      // pcl::PointXYZ point(r * std::sin(theta) , 0.0 , r * std::cos(theta));
      //std::cout << __PRETTY_FUNCTION__ << " point " << point << std::endl;
      cloud.push_back(point);
    }
    //_pubQueue->push(cloud, _pub);
  
  //}
  //std::cout << __PRETTY_FUNCTION__ << _angle << " - " <<  angleLast << std::endl;
  if(std::abs(popo - angleLast) > M_PI)
  {
  _pubQueue->push(cloud, _pub);
  //nSteps = 0;
  cloud.clear();
  }
  angleLast = popo;
  _parentRaySensor->SetActive(true);
  // sensor_msgs::LaserScan laserMsg;
  // laserMsg.header.stamp          = ros::Time::now();
  // laserMsg.header.frame_id       = _frameName;
  // laserMsg.angle_min = msg->scan().angle_min();
  // laserMsg.angle_max = msg->scan().angle_max();
  // laserMsg.angle_increment = msg->scan().angle_step();
  // laserMsg.time_increment = 0;  // instantaneous simulator scan
  // laserMsg.scan_time = 0;  // not sure whether this is correct
  // laserMsg.range_min = msg->scan().range_min();
  // laserMsg.range_max = msg->scan().range_max();
  // laserMsg.ranges.resize(msg->scan().ranges_size());
  // std::copy(msg->scan().ranges().begin(),
  //     msg->scan().ranges().end(),
  //     laserMsg.ranges.begin());
  // laserMsg.intensities.resize(msg->scan().intensities_size());
  // std::copy(msg->scan().intensities().begin(),
  //     msg->scan().intensities().end(),
  //     laserMsg.intensities.begin());
  // arsch += 0.001;
  // if(arsch > 0.1)
  //   arsch = 0.0;
  // std::cout << __PRETTY_FUNCTION__ << " arsch = " << arsch << std::endl;

  
  //_pubQueue->push(laserMsg, _pub);
}

void PluginSensorVelodyne::OnMsg(ConstVector3dPtr& msg)
{

  // std::cout << __PRETTY_FUNCTION__ << " got angle " << msg->x() << std::endl;
  _angle = msg->x();
}

void PluginSensorVelodyne::onNewLaserScans()
{

}

GZ_REGISTER_SENSOR_PLUGIN(PluginSensorVelodyne)

} /* namespace gazebo */
