#include <cmath>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <thread>
#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include "phros_gazebo_plugins/PluginJointRotaryConfig.h"
#include <tf/transform_broadcaster.h>

namespace gazebo
{

class PluginJointRotary : public ModelPlugin
{
public:
  PluginJointRotary();
  virtual ~PluginJointRotary(void);
  virtual void Load(physics::ModelPtr model, sdf::ElementPtr sdf);
  void eventLoop();
private:
   //void callBackDynamicReconfigure(phros_gazebo_plugins::PluginJointRotaryConfig& config, const uint32_t level);
    ros::NodeHandle _nh;
  // dynamic_reconfigure::Server<phros_gazebo_plugins::PluginJointRotaryConfig>               _serverReconf;   ///< ROS dynamic reconfigure server
  // dynamic_reconfigure::Server<phros_gazebo_plugins::PluginJointRotaryConfig>::CallbackType _callBackConfig; ///< ROS dynamic reconfigure object
  physics::ModelPtr               _model;
  sdf::ElementPtr                  _sdf;
  physics::JointPtr               _joint;
  common::PID                     _pid;
  std::thread                     _threadCommunication;
  transport::NodePtr              _node;
  gazebo::transport::PublisherPtr _pub;
  phros_gazebo_plugins::PluginJointRotaryConfig _config;
  tf::TransformBroadcaster _bc;
  tf::StampedTransform _tf;
};

}