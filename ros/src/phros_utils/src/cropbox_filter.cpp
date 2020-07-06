/*
 * cropbox_filter.cpp
 *
 *  Created on: Apr 10, 2019
 *      Author: phil
 */

#include "phros_utils/ReconfigureCropBoxFilterConfig.h"
#include <Eigen/Dense>
#include <dynamic_reconfigure/server.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl_ros/point_cloud.h>
#include <ros/ros.h>
#include <string>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>

void callBackPointCloud(const pcl::PointCloud<pcl::PointXYZ>& cloudRos);
void callbackDynamicReconfigure(phros_utils::ReconfigureCropBoxFilterConfig& config, uint32_t level);
void callBackTimer(const ros::TimerEvent& event);
bool operator>(const Eigen::Vector3f& a, const Eigen::Vector3f& b);
bool operator<(const Eigen::Vector3f& a, const Eigen::Vector3f& b);

static ros::Publisher                                  _pubCloudOut;
static ros::Publisher                                  _pubBoxMarker;
static std::string                                     _frameMarker = "base_link";
static Eigen::Vector3f                                 _threshVecMin(0.0, 0.0, 0.0);
static Eigen::Vector3f                                 _threshVecMax(0.0, 0.0, 0.0);
static Eigen::Vector3i                                 _rgb;
static phros_utils::ReconfigureCropBoxFilterConfig _config;
pcl::PointCloud<pcl::PointCloud<pcl::PointXYZ> >       filtered;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "cropbox_filter");
  ros::NodeHandle nh;
  ros::NodeHandle prvNh("~");

  std::string topicCloudIn;
  std::string topicCloudOut;
  std::string topicBoxMarker;

  prvNh.param<std::string>("topic_cloud_in", topicCloudIn, "/velodyne_points");
  prvNh.param<std::string>("topic_cloud_out", topicCloudOut, "/cropbox_filter/output");
  prvNh.param<std::string>("topic_box_marker", topicBoxMarker, "/cropbox_filter/area");

  ros::Subscriber subsCloudIn = nh.subscribe(topicCloudIn, 1, callBackPointCloud);
  _pubCloudOut                = nh.advertise<pcl::PointCloud<pcl::PointXYZ> >(topicCloudOut, 1);
  dynamic_reconfigure::Server<phros_utils::ReconfigureCropBoxFilterConfig>               serverReconf;
  dynamic_reconfigure::Server<phros_utils::ReconfigureCropBoxFilterConfig>::CallbackType callBackConfig;
  callBackConfig = boost::bind(callbackDynamicReconfigure, _1, _2);
  serverReconf.setCallback(callBackConfig);
  ros::Timer timer = nh.createTimer(ros::Duration(0.05), callBackTimer);
  _pubBoxMarker    = nh.advertise<visualization_msgs::MarkerArray>(topicBoxMarker, 1);

  //_filter = new pcl::CropBox<pcl::PointCloud<pcl::PointXYZ> >(true);
  //  _filter = new pcl::CropHull<pcl::PointCloud<pcl::PointXYZ> >;
  //  _filter->setTranslation(Eigen::Vector3f(0.0, 0.0, 0.0));

  ros::spin();
}

void callBackPointCloud(const pcl::PointCloud<pcl::PointXYZ>& cloudRos)
{
  pcl::PointCloud<pcl::PointXYZ> filtered;
  pcl::PointCloud<pcl::PointXYZ> filteredInverse;
  filtered.header.frame_id        = cloudRos.header.frame_id;
  filteredInverse.header.frame_id = cloudRos.header.frame_id;
  for(auto& iter : cloudRos)
  {
    Eigen::Vector3f currentPoint(iter.x, iter.y, iter.z);
    if(!((currentPoint > _threshVecMin) && (currentPoint < _threshVecMax)))
      filtered.push_back(iter);
    else
      filteredInverse.push_back(iter);
  }
  // pcl_conversions::toPCL(ros::Time::now(), filtered.header.stamp);
  // pcl_conversions::toPCL(ros::Time::now(), filteredInverse.header.stamp);
  filtered.header.stamp = cloudRos.header.stamp;
  filteredInverse.header.stamp = cloudRos.header.stamp;
  _frameMarker = cloudRos.header.frame_id;
  if(_config.inverse)
    _pubCloudOut.publish(filteredInverse);
  else
    _pubCloudOut.publish(filtered);
}

void callbackDynamicReconfigure(phros_utils::ReconfigureCropBoxFilterConfig& config, uint32_t level)
{
  _threshVecMin = Eigen::Vector3f(static_cast<float>(config.min_x), static_cast<float>(config.min_y), static_cast<float>(config.min_z));
  _threshVecMax = Eigen::Vector3f(static_cast<float>(config.max_x), static_cast<float>(config.max_y), static_cast<float>(config.max_z));
  _config       = config;
}

bool operator>(const Eigen::Vector3f& a, const Eigen::Vector3f& b) { return ((a.x() > b.x()) && (a.y() > b.y()) && (a.z() > b.z())); }

bool operator<(const Eigen::Vector3f& a, const Eigen::Vector3f& b) { return ((a.x() < b.x()) && (a.y() < b.y()) && (a.z() < b.z())); }

void callBackTimer(const ros::TimerEvent& event)
{
  Eigen::Vector3d dim((_config.max_x - _config.min_x), (_config.max_y - _config.min_y), (_config.max_z - _config.min_z));
  // std::cout << __PRETTY_FUNCTION__ << " dim "  << dim << std::endl;
  visualization_msgs::MarkerArray markers;
  visualization_msgs::Marker      markerBox;
  markerBox.header.frame_id    = _frameMarker;
  markerBox.header.stamp       = ros::Time();
  markerBox.id                 = 0;
  markerBox.type               = visualization_msgs::Marker::CUBE;
  markerBox.action             = visualization_msgs::Marker::ADD;
  markerBox.pose.position.x    = (_config.max_x + _config.min_x) / 2.0;
  markerBox.pose.position.y    = (_config.max_y + _config.min_y) / 2.0;
  markerBox.pose.position.z    = (_config.max_z + _config.min_z) / 2.0;
  markerBox.pose.orientation.x = 0.0;
  markerBox.pose.orientation.y = 0.0;
  markerBox.pose.orientation.z = 0.0;
  markerBox.pose.orientation.w = 1.0;
  markerBox.scale.x            = dim.x();
  markerBox.scale.y            = dim.y();
  markerBox.scale.z            = dim.z();
  markerBox.color.a            = _config.color_box_a;
  markerBox.color.r            = _config.color_box_r;
  markerBox.color.g            = _config.color_box_g;
  markerBox.color.b            = _config.color_box_b;
  markers.markers.push_back(markerBox);
  _pubBoxMarker.publish(markers);
}