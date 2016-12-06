/*
 * asyncspin.cpp
 *
 *  Created on: 2016年8月3日
 *      Author: yin
 */

#include "asyncspin.h"

asyncspin::asyncspin(ros::NodeHandle nh):d(0.01)
{
asyncspin::sub_ = nh.subscribe("chattertest", 10, &asyncspin::chatter1_, this);
asyncspin::sub1_ = nh.subscribe("chatter", 10, &asyncspin::chatter2_, this);
asyncspin::sub2_ = nh.subscribe("chattertest", 10, &asyncspin::chatter3_, this);
asyncspin::sub3_ = nh.subscribe("chatter", 10, &asyncspin::chatter4_, this);

  /**
   * The AsyncSpinner object allows you to specify a number of threads to use
   * to call callbacks.  If no explicit # is specified, it will use the # of hardware
   * threads available on your system.  Here we explicitly specify 4 threads.
   */
  ros::AsyncSpinner s(4);
  s.start();

  ros::Rate r(5);
  while (ros::ok())
  {
    ROS_INFO_STREAM("Main thread [" << boost::this_thread::get_id() << "].");
    r.sleep();
  }

}
asyncspin::~asyncspin()
{
	ROS_INFO_STREAM("invoking destructor!");
}

  void asyncspin::chatter1_(const ivthread::test::ConstPtr& msg1)
  {
    ROS_INFO_STREAM("chatter1: [" << msg1->message<< "] [thread=" << boost::this_thread::get_id() << "]");
    d.sleep();
  }
  void asyncspin::chatter2_(const std_msgs::String::ConstPtr& msg)
  {
    ROS_INFO_STREAM("chatter2: [" << msg->data << "] [thread=" << boost::this_thread::get_id() << "]");
   d.sleep();
  }
  void asyncspin::chatter3_(const ivthread::test::ConstPtr& msg1)
  {
    ROS_INFO_STREAM("chatter3: [" << msg1->message << "] [thread=" << boost::this_thread::get_id() << "]");
    d.sleep();
  }
  void asyncspin::chatter4_(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO_STREAM("chatter4: [" << msg->data << "] [thread=" << boost::this_thread::get_id() << "]");
    d.sleep();
}




