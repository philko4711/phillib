#include <dynamic_reconfigure/server.h>
#include <memory>
#include <phros_utils/ReconfigureFrameChangerConfig.h>
#include <ros/ros.h>
#include <string>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

static std::unique_ptr<tf::TransformListener>                      _listener;
static std::unique_ptr<phros_utils::ReconfigureFrameChangerConfig> _config;
static std::string                                                 _tfFrameBaseOriginal;
static std::string                                                 _tfFrameChildOriginal;
static std::string                                                 _tfFrameBaseNew;
static std::string                                                 _tfFrameChildNew;

void callBackTimer(const ros::TimerEvent& ev);
void createTransform(tf::Transform& tf);
void callbackDynamicReconfigure(phros_utils::ReconfigureFrameChangerConfig& config, uint32_t level);

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf_frame_changer");
  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");

  _listener = std::make_unique<tf::TransformListener>();

  double updateRate = 0.0;

  prvNh.param<std::string>("tf_frame_base_original", _tfFrameBaseOriginal, "camera_odom_frame");
  prvNh.param<std::string>("tf_frame_child_original", _tfFrameChildOriginal, "camera_pose_frame");
  prvNh.param<std::string>("tf_frame_base_new", _tfFrameBaseNew, "map");
  prvNh.param<std::string>("tf_frame_child_new", _tfFrameChildNew, "gay_camera_link");
  prvNh.param<double>("update_rate", updateRate, 100.0);

  ros::Timer                                                              timer1 = nh.createTimer(ros::Duration(1 / updateRate), callBackTimer);
  dynamic_reconfigure::Server<phros_utils::ReconfigureFrameChangerConfig> serverReconf;
  dynamic_reconfigure::Server<phros_utils::ReconfigureFrameChangerConfig>::CallbackType callBackConfig;

  callBackConfig = boost::bind(callbackDynamicReconfigure, _1, _2);
  serverReconf.setCallback(callBackConfig);
  ros::spin();

  return 0;
}

void callBackTimer(const ros::TimerEvent& ev)
{
  static tf::TransformBroadcaster bc;
  if(!_config)
    return;
  tf::Transform tf;
  createTransform(tf);
  if(!_listener->waitForTransform(_tfFrameBaseOriginal, _tfFrameChildOriginal, ros::Time::now(), ros::Duration(0.1)))
  {
    ROS_ERROR_STREAM(__PRETTY_FUNCTION__ << " timeout waiting for tf " << _tfFrameBaseOriginal << "->" << _tfFrameChildOriginal << std::endl);
    return;
  }
  tf::StampedTransform tfOriginal;
  try
  {
    _listener->lookupTransform(_tfFrameBaseOriginal, _tfFrameChildOriginal, ros::Time(0), tfOriginal);
  }
  catch(const tf::TransformException& e)
  {
    ROS_ERROR_STREAM(__PRETTY_FUNCTION__ << e.what() << std::endl);
    return;
  }
  tf::Transform tfNew = tfOriginal * tf;
  tf::StampedTransform tfNewStamped(tfNew, tfOriginal.stamp_,_tfFrameBaseNew, _tfFrameChildNew);
  // tfNew.frame_id_ = _tfFrameBaseNew;
  // tfNew.child_frame_id_ = _tfFrameChilNew;
  // tfNew.stamp = tfOriginal.stamp;
  bc.sendTransform(tfNewStamped);

}

void createTransform(tf::Transform& tf)
{
  tf::Quaternion quat;
  tf.setOrigin(tf::Vector3(_config->sensor_offset_x, _config->sensor_offset_y, _config->sensor_offset_z));
  quat.setRPY(_config->sensor_roll_angle, _config->sensor_tilt_angle, _config->sensor_yaw_angle);
  tf.setRotation(quat);
}

void callbackDynamicReconfigure(phros_utils::ReconfigureFrameChangerConfig& config, uint32_t level)
{
  if(!_config)
    _config = std::make_unique<phros_utils::ReconfigureFrameChangerConfig>();
  *_config = config;
}