#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/point_cloud_conversion.h>
#include <pcl/io/ply_io.h>

void callBackCloud(const sensor_msgs::PointCloud2& cloud);

int main(int argc, char** argv)
{
    ros::init(argc, argv, "cloud_saver");
    ros::NodeHandle nh;
    ros::Subscriber subs = nh.subscribe("/puck_front/velodyne_points", 1, callBackCloud);
    ros::spin();
}

void callBackCloud(const sensor_msgs::PointCloud2& cloud)
{
    sensor_msgs::PointCloud cloudIn;
    sensor_msgs::convertPointCloud2ToPointCloud(cloud, cloudIn);
    pcl::PointCloud<pcl::PointXYZ> cloudPcl;
    for(auto& iter : cloudIn.points)
    {
        pcl::PointXYZ point(iter.x, iter.y, iter.z);
        cloudPcl.push_back(point);
    }
    pcl::PLYWriter writer;
    writer.write("/tmp/cloud.ply", cloudPcl);
    std::exit(1);
}