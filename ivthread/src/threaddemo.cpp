/*
 * thread.cpp
 *
 *  Created on: 2016年8月2日
 *      Author: yin
 */
#include "threaddemo.h"

threaddemo::threaddemo(ros::NodeHandle nh)
{
      ////////////////////////////////////////////////////////////////
	//please pay attention to boost::function and boost::bind, especially the <> | () parameters;
      func_ = boost::bind(&threaddemo::chatterCallbackCustomQueue, this, _1);
      ops_ = ros::SubscribeOptions::create<ivthread::test>("chattertest", 1000,func_,  ros::VoidPtr(), &g_queue_);
      sub_ = nh.subscribe(threaddemo::ops_);
      f_ = boost::bind(&threaddemo::callbackThread_, this);
      boost::thread chatter_thread_(f_);
//////////////////////////////////////////////////////////////////////
      func1_ = boost::bind(&threaddemo::chatterCallbackTestQueue, this, _1);
      ops1_ = ros::SubscribeOptions::create<ivthread::test>("chattertest", 1000,func1_,  ros::VoidPtr(), &g_queue1_);
      sub1_ = nh.subscribe(threaddemo::ops1_);
      f1_ = boost::bind(&threaddemo::callbackThread1_, this);
      boost::thread chatter_thread1_(f1_);
////////////////////////////////////////////////////////////////////
      sub = nh.subscribe("chatter", 1000, &threaddemo::chatterCallbackMainQueue,this);
      ROS_INFO_STREAM("Main thread id=" << boost::this_thread::get_id());

      ros::Rate r(1);
  while (nh.ok())
  {
    ros::spinOnce();
    r.sleep();
  }
///////////////////////////////////////////////////////////////////
  chatter_thread_.join();
  chatter_thread1_.join();

}

threaddemo::~threaddemo()
{
	ROS_INFO_STREAM("invoking destructor!");
}

void threaddemo::chatterCallbackMainQueue(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO_STREAM("I heard: [ " << msg->data << "] in thread [" << boost::this_thread::get_id() << "] (Main thread)");
}

void threaddemo::chatterCallbackCustomQueue(const ivthread::test::ConstPtr& msg)
{
  ROS_INFO_STREAM("I heard: [ " << msg->message << "] in thread [" << boost::this_thread::get_id() << "] (Custom thread)");
}

void threaddemo::chatterCallbackTestQueue(const ivthread::test::ConstPtr& msg)
{
  ROS_INFO_STREAM("the message [ " << msg->message << "] in thread [" << boost::this_thread::get_id() << "] (test thread)");
}

void threaddemo::callbackThread_()
{
  ROS_INFO_STREAM("Callback thread id=" << boost::this_thread::get_id());
  ros::NodeHandle n;
  while (n.ok())
  {
    g_queue_.callAvailable(ros::WallDuration(0.01));
  }
}

void threaddemo::callbackThread1_()
{
  ROS_INFO_STREAM("Test thread id=" << boost::this_thread::get_id());
  ros::NodeHandle n;
  while (n.ok())
  {
    g_queue1_.callAvailable(ros::WallDuration(0.01));
  }
}

