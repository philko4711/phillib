#include <Eigen/Dense>
#include <ros/ros.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <string>
#include <dynamic_reconfigure/server.h>
#include <phros_utils/ReconfigureFilterDepthConfig.h>

void                  callBackCloud(const sensor_msgs::PointCloud2& cloud);
void callBackDynamicReconfigure(phros_utils::ReconfigureFilterDepthConfig& config, const uint32_t level);
static ros::Publisher _pubCloud;
static phros_utils::ReconfigureFilterDepthConfig _config;
int main(int argc, char** argv)
{
  ros::init(argc, argv, "filter_depth");
  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");
  std::string     topicCloudIn;
  std::string     topicCloudOut;
  prvNh.param<std::string>("topic_cloud_in", topicCloudIn, "puck_front/velodyne_points");
  prvNh.param<std::string>("topic_cloud_out", topicCloudOut, "filter_depth/output");
  ros::Subscriber subsPointCloud = nh.subscribe(topicCloudIn, 1, callBackCloud);
  _pubCloud = nh.advertise<sensor_msgs::PointCloud2>(topicCloudOut, 1);
    dynamic_reconfigure::Server<phros_utils::ReconfigureFilterDepthConfig> serverReconf; ///< ROS dynamic reconfigure server
  dynamic_reconfigure::Server<phros_utils::ReconfigureFilterDepthConfig>::CallbackType callBackConfig; ///< ROS dynamic reconfigure object
  callBackConfig = boost::bind(callBackDynamicReconfigure, _1, _2);
  serverReconf.setCallback(callBackConfig);
  ros::spin();

  return 0;
}

void callBackCloud(const sensor_msgs::PointCloud2& cloud)
{
  static unsigned int seq = 0;
  sensor_msgs::PointCloud  cloudIn;
  sensor_msgs::PointCloud cloudOut;
  cloudOut.header = cloudIn.header;
  cloudOut.channels = cloudIn.channels;

  sensor_msgs::convertPointCloud2ToPointCloud(cloud, cloudIn);
  for(auto& iter : cloudIn.points)
  {
    Eigen::Vector3f vec(iter.x, iter.y, iter.z);
    const float abs = vec.norm();
    if((abs > _config.thresh_min) && (abs < _config.thresh_max))
      cloudOut.points.push_back(iter);
  }
  sensor_msgs::PointCloud2 cloud2Out;
  if(cloudOut.points.size())
  {
    sensor_msgs::convertPointCloudToPointCloud2(cloudOut, cloud2Out);
    cloud2Out.header.stamp = ros::Time::now();
    cloud2Out.header.seq = seq++;
    _pubCloud.publish(cloud2Out);
  }
}

void callBackDynamicReconfigure(phros_utils::ReconfigureFilterDepthConfig& config, const uint32_t level)
{
  _config = config;
}