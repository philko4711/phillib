/*
 * static_tf_recon.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: phil
 */

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <dynamic_reconfigure/server.h>
#include "phros_utils/ReconfigureStatTfConfig.h"

#include <string>

static std::string _baseFrame;
static std::string _childFrame1;

void callbackDynamicReconfigure(phros_utils::ReconfigureStatTfConfig& config, uint32_t level);
void callbackTimer(const ros::TimerEvent&);

static phros_utils::ReconfigureStatTfConfig _config;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "base_tf_node");
  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");

  double upDateRate = 0.0;

  prvNh.param<double>     ("update_rate" , upDateRate, 50.0);
  prvNh.param<std::string>("base_frame", _baseFrame, "base_link");
  prvNh.param<std::string>("child_frame", _childFrame1, "ldmrs_mount_link");

  ros::Timer timer1 = nh.createTimer(ros::Duration(1 / upDateRate), callbackTimer);
  dynamic_reconfigure::Server<phros_utils::ReconfigureStatTfConfig> serverReconf;
  dynamic_reconfigure::Server<phros_utils::ReconfigureStatTfConfig>::CallbackType callBackConfig;

  callBackConfig = boost::bind(callbackDynamicReconfigure, _1, _2);
  serverReconf.setCallback(callBackConfig);

  ros::spin();
  return 0;
}

void callbackDynamicReconfigure(phros_utils::ReconfigureStatTfConfig& config, uint32_t level)
{
  _config = config;
}

void callbackTimer(const ros::TimerEvent&)
{
  static tf::TransformBroadcaster broadCaster;
  tf::StampedTransform tf;
  tf::Quaternion quat;
  tf.frame_id_ = _baseFrame;
  tf.child_frame_id_ = _childFrame1;
  tf.setOrigin(tf::Vector3(_config.offset_x, _config.offset_y, _config.offset_z));
  quat.setRPY(_config.roll_angle, _config.tilt_angle, _config.yaw_angle);
  tf.setRotation(quat);
  tf.stamp_ = ros::Time::now();
  broadCaster.sendTransform(tf);
}