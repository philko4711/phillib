#include "SensorVelodyne.h"
#include <ros/ros.h>
int main(int argc, char** argv)
{
  ros::init(argc, argv, "sensor_velodyne");
  SensorVelodyne sensorVelodyne;
  sensorVelodyne.start();
  return 0;
}