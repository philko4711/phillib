#include <Eigen/Dense>
#include <ros/ros.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <string>

void callBackCloud(const sensor_msgs::PointCloud2 &cloud);
static ros::Publisher _pubCloud;

int main(int argc, char **argv) {
  ros::init(argc, argv, "filter_depth");
  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");
  std::string topicCloudIn;
  std::string topicCloudOut;
  prvNh.param<std::string>("topic_cloud_in", topicCloudIn, "puck_front/velodyne_points");
prvNh.param<std::string>("topic_cloud_out", topicCloudOut, "filter_depth/output");
ros::Subscriber subsPointCloud = nh.subscribe(topicCloudIn, 1, callBackCloud);
ros::spin();

  return 0;
}

void callBackCloud(const sensor_msgs::PointCloud2 &cloud) 
{

 sensor_msgs::PointCloud cloudOut;
  sensor_msgs::PointCloud2 cloudOut;

  sensor_msgs::convertPointCloud2ToPointCloud(cloud, cloudIn);   
}