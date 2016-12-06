/*
 * asyncspin.h
 *
 *  Created on: 2016年8月3日
 *      Author: yin
 */

#ifndef IVTHREAD_SRC_ASYNCSPIN_H_
#define IVTHREAD_SRC_ASYNCSPIN_H_


//c++ lib
#include <vector>
// ROS lib
#include "ros/ros.h"
#include "ros/time.h"
//other lib
#include <sstream>

#include "std_msgs/String.h"

#include "ros/callback_queue.h"

#include <boost/thread.hpp>
#include "ivthread/test.h"

using namespace std;

// Custom message includes. Auto-generated from msg/ directory.


//change you configure class here

class asyncspin
{
public:
	asyncspin(ros::NodeHandle nh);
	~asyncspin();
  	void chatter1_(const ivthread::test::ConstPtr& msg1);
  	void chatter2_(const std_msgs::String::ConstPtr& msg);
  	void chatter3_(const ivthread::test::ConstPtr& msg1);
 	void chatter4_(const std_msgs::String::ConstPtr& msg);

private:
	ros::Subscriber sub_, sub1_,sub2_,sub3_;
	ros::Publisher pub;
	ros::Duration d;
};


#endif /* IVTHREAD_SRC_ASYNCSPIN_H_ */
