/*
 * threadspin.cpp
 *
 *  Created on: 2016年8月3日
 *      Author: yin
 */

#include "threadspin.h"

threadspin::threadspin(ros::NodeHandle nh):d(0.01)
{
threadspin::sub_ = nh.subscribe("chattertest", 10, &threadspin::chatter1, this);
threadspin::sub1_ = nh.subscribe("chatter", 10, &threadspin::chatter2, this);
threadspin::sub2_ = nh.subscribe("chattertest", 10, &threadspin::chatter3, this);
threadspin::sub3_ = nh.subscribe("chatter", 10, &threadspin::chatter4, this);
  /**
   * The MultiThreadedSpinner object allows you to specify a number of threads to use
   * to call callbacks.  If no explicit # is specified, it will use the # of hardware
   * threads available on your system.  Here we explicitly specify 4 threads.
   */
  ros::MultiThreadedSpinner s(4);
  ros::spin(s);
//    ros::Rate r(1);
//  while (nh.ok())
//  {
//    ros::spinOnce();
//    r.sleep();
//  }
}
threadspin::~threadspin()
{
	ROS_INFO_STREAM("invoking destructor!");
}

  void threadspin::chatter1(const ivthread::test::ConstPtr& msg)
  {
    ROS_INFO_STREAM("chatter1: [" << msg->message << "] [thread=" << boost::this_thread::get_id() << "]");
    d.sleep();
  }
  void threadspin::chatter2(const std_msgs::String::ConstPtr& msg)
  {
    ROS_INFO_STREAM("chatter2: [" << msg->data << "] [thread=" << boost::this_thread::get_id() << "]");
   d.sleep();
  }
  void threadspin::chatter3(const ivthread::test::ConstPtr& msg)
  {
    ROS_INFO_STREAM("chatter3: [" << msg->message << "] [thread=" << boost::this_thread::get_id() << "]");
    d.sleep();
  }
  void threadspin::chatter4(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO_STREAM("chatter4: [" << msg->data << "] [thread=" << boost::this_thread::get_id() << "]");
  d.sleep();
}



