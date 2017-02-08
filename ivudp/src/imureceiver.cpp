#include "ros/ros.h"
#include "ros/time.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include "ivsensorimu/ivsensorimu.h"
#include "ivsensorimu/imurawdata.h"
using namespace std;

void callback(const ivsensorimu::ivsensorimu::ConstPtr& msg, ivsensorimu::ivsensorimu& refer)
{
	refer = *msg;
	ROS_INFO_STREAM("The lag time is: "<<ros::Time::now() - refer.header.stamp <<" s");
}

void rawcallback(const ivsensorimu::imurawdata::ConstPtr& msg, ivsensorimu::imurawdata& refer)
{
  refer = *msg;
  // ROS_INFO_STREAM("The raw data: "<<refer);
  int num = refer.data.size();
  ROS_INFO_STREAM(num);
  for (int i = 0; i < num; ++i)
  {
    char buffer[20];
    sprintf(buffer, "0x%2X", refer.data.at(i));
    ROS_INFO_STREAM(buffer);
    // printf("raw: %2X\n", refer.data.at(i));
  }

}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "imureseiver");
  ros::NodeHandle nh;
  ivsensorimu::ivsensorimu imumsg;
  ivsensorimu::imurawdata rawmsg;
  ros::Subscriber imusub = nh.subscribe<ivsensorimu::ivsensorimu>("ivsensorimu", 1000, boost::bind(callback, _1, imumsg));
  ros::Subscriber rawsub = nh.subscribe<ivsensorimu::imurawdata>("imurawdata", 1000, boost::bind(rawcallback, _1, rawmsg));
  ros::Rate loop(20);
  while (ros::ok())
  {
    ros::spinOnce();
    loop.sleep();
  }

  return 0;
}