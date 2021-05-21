#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <gazebo_msgs/ModelStates.h>
#include <gazebo_msgs/GetModelState.h>
#include <geometry_msgs/Pose.h>

void callBackTimer(const ros::TimerEvent& event);
void callBackModelStates(const gazebo_msgs::ModelStates& states);

#include <string>

static std::string _modelName;
static std::string _frameMap;
static std::string _frameGroundTruth;
static ros::ServiceClient _clientGetModelState;

int main(int argc, char** argv)
{
ros::init(argc, argv, "get_link_tf");
ros::NodeHandle nh;
ros::NodeHandle prvNh("~");
std::string topicModelStates;
std::string topicGetModelState;
double updateRate;
prvNh.param<std::string>("topic_model_states", topicModelStates, "/gazebo/model_states");
prvNh.param<std::string>("topic_get_model_state", topicGetModelState, "/gazebo/get_model_state");
prvNh.param<std::string>("model_name", _modelName, "");
prvNh.param<std::string>("frame_map", _frameMap, "map");
prvNh.param<std::string>("frame_link", _frameGroundTruth, "ground_truth");
prvNh.param<double>("update_rate", updateRate, 100.0);
//ros::Subscriber subsModelStates = nh.subscribe(topicModelStates, 1, callBackModelStates);

ros::Time waiting = ros::Time::now();
while(!ros::service::waitForService(topicGetModelState, ros::Duration(0.1)))
{
  const double elapsed = (ros::Time::now() - waiting).toSec();
  ROS_INFO_STREAM_THROTTLE(1.0, "waiting for gazebo on topic " << topicGetModelState << " since " << elapsed);
  if(elapsed > 10.0)
  {
    ROS_ERROR_STREAM("Gazebo could not be reached on topic " << topicGetModelState);
    std::exit(1);
  }
}
_clientGetModelState = nh.serviceClient<gazebo_msgs::GetModelState>(topicGetModelState);
ros::Timer timerMain = nh.createTimer(ros::Duration(1.0 / updateRate), callBackTimer);
  ros::spin();
return 0;
}

void callBackTimer(const ros::TimerEvent& event)
{
static tf::TransformBroadcaster bc;
  static tf::StampedTransform tf;
  tf.frame_id_ = _frameMap;
  tf.child_frame_id_ = _frameGroundTruth;
  
  gazebo_msgs::GetModelState getState;
  getState.request.model_name = "/"; //todo: hardcoded shit...remove. But the model namespace needs to be fixed first.
  if(_clientGetModelState.call(getState))
  {
    geometry_msgs::Pose& current = getState.response.pose;
    tf.setOrigin(tf::Vector3(current.position.x, current.position.y, current.position.z - 0.529));   //TODO: this results from the gazebo model. Base footpring hangs 5cm in the air
    tf.setRotation(tf::Quaternion(current.orientation.x, current.orientation.y, current.orientation.z, current.orientation.w));
    tf.stamp_ = ros::Time::now();
    bc.sendTransform(tf);
  }
  else
    ROS_ERROR_STREAM("Error. Call to gazebo failed");

}

void callBackModelStates(const gazebo_msgs::ModelStates& states)
{
  
  // for(unsigned int i = 0;  i < states.name.size(); i++)
  // {
  //   if(states.name[i] == "/")
  //   {
  //     geometry_msgs::Pose& current = states.pose[i];
  //     std::cout << __PRETTY_FUNCTION__ << " pos.x / y " << states.pose[i].position.x << " / " << states.pose[i].position.y << std::endl;
  //     tf.setOrigin(tf::Vector3(current.position.x, current.position.y, current.position.z));
  //     tf.setRotation(tf::Quaternion(current.orientation.x, current.orientation.y, current.orientation.z, current.orientation.w));
  //   }
  // }
}