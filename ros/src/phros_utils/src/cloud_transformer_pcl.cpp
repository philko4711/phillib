/*
 * cloud_transformer.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: phil
 */

#include <ros/ros.h>
#include <tf/transform_listener.h>
//#include <pcl_ros/transforms.h>
#include <pcl_ros/point_cloud.h>
#include <string>
#include <tf_conversions/tf_eigen.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/common/transforms.h>

void callBackCloud(const pcl::PointCloud<pcl::PointXYZ>& cloud);
bool transFormPointCloud(pcl::PointCloud<pcl::PointXYZ>& in, tf::StampedTransform& tf);

static ros::Publisher _pubTfCloud;
static std::unique_ptr<tf::TransformListener> _tfListener;
static std::string _tfChildFrame;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cloud_transformer");
  _tfListener = std::make_unique<tf::TransformListener>();

  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");
  std::string inputTopic;
  std::string outputTopic;
  prvNh.param<std::string>("input_topic", inputTopic, "point_cloud");
  prvNh.param<std::string>("output_topic", outputTopic, "transformed_cloud");
  prvNh.param<std::string>("tf_frame", _tfChildFrame, "base_link");

  ros::Subscriber cloudSubs = nh.subscribe(inputTopic, 1, callBackCloud);
  _pubTfCloud = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >(outputTopic, 1);
  ros::spin();
}

void callBackCloud(const pcl::PointCloud<pcl::PointXYZ>& cloud)
{
  pcl::PointCloud<pcl::PointXYZ> cloudTf = cloud;
  cloudTf.header.frame_id = _tfChildFrame;
  ros::Time stamp;
  tf::StampedTransform tf;
  pcl_conversions::fromPCL(cloud.header.stamp, stamp);
  ros::NodeHandle nh;
  if(!_tfListener->waitForTransform(_tfChildFrame, cloud.header.frame_id , stamp ,ros::Duration(0.5)))
  {
    ROS_ERROR_STREAM(nh.getNamespace() << " " << __PRETTY_FUNCTION__ << " Timeout waiting for transform from " << cloud.header.frame_id << " to " << _tfChildFrame);
    return;
  }
  try
  {
    _tfListener->lookupTransform(_tfChildFrame, cloud.header.frame_id, stamp, tf);
  }
  catch (tf::TransformException& ex)
  {
    ROS_ERROR("%s",ex.what());
    return;
  }
  transFormPointCloud(cloudTf, tf);
  _pubTfCloud.publish(cloudTf);
}

bool transFormPointCloud(pcl::PointCloud<pcl::PointXYZ>& in, tf::StampedTransform& tf)
{
  Eigen::Affine3d aff;
  tf::transformTFToEigen(tf, aff);
  pcl::transformPointCloud(in, in, aff);
  return true;
}
