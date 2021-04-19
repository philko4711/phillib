/*
 * cloud_transformer.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: phil
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <string>

void callBackCloud(const sensor_msgs::PointCloud2& cloud);

static ros::Publisher         _pubTfCloud;
static std::unique_ptr<tf::TransformListener> _tfListener;
static std::string            _tfChildFrame;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cloud_transformer");
  _tfListener = std::make_unique<tf::TransformListener>();

  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");
  std::string     inputTopic;
  std::string     outputTopic;
  prvNh.param<std::string>("input_topic", inputTopic, "point_cloud");
  prvNh.param<std::string>("output_topic", outputTopic, "transformed_cloud");
  prvNh.param<std::string>("tf_frame", _tfChildFrame, "base_link");

  ros::Subscriber cloudSubs = nh.subscribe(inputTopic, 1, callBackCloud);
  _pubTfCloud               = nh.advertise<sensor_msgs::PointCloud2>(outputTopic, 1);
  ros::spin();
}

void callBackCloud(const sensor_msgs::PointCloud2& cloud)
{
  sensor_msgs::PointCloud cloudOut;
  sensor_msgs::PointCloud cloudIn;

  sensor_msgs::convertPointCloud2ToPointCloud(cloud, cloudIn);
  if(!_tfListener->waitForTransform(_tfChildFrame, cloud.header.frame_id, cloud.header.stamp, ros::Duration(0.5)))
  {
    // ROS_ERROR_STREAM(nh.getNamespace() << " " << __PRETTY_FUNCTION__ << " Timeout waiting for transform from " << cloud.header.frame_id << " to " <<
    // _tfChildFrame);
    return;
  }
  try
  {
    _tfListener->transformPointCloud(_tfChildFrame, cloudIn.header.stamp, cloudIn, cloudIn.header.frame_id, cloudOut);
  }
  catch(tf::TransformException& ex)
  {
    ROS_ERROR("%s", ex.what());
    return;
  }
  sensor_msgs::PointCloud2 cloudSend;
  sensor_msgs::convertPointCloudToPointCloud2(cloudOut, cloudSend);
  _pubTfCloud.publish(cloudSend);
}
