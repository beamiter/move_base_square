/*
 * threadspin.h
 *
 *  Created on: 2016年8月3日
 *      Author: yin
 */

#ifndef IVTHREAD_SRC_THREADSPIN_H_
#define IVTHREAD_SRC_THREADSPIN_H_



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

class threadspin
{
public:
	threadspin(ros::NodeHandle nh);
	~threadspin();
  	void chatter1(const ivthread::test::ConstPtr& msg);
  	void chatter2(const std_msgs::String::ConstPtr& msg);
  	void chatter3(const ivthread::test::ConstPtr& msg);
 	 void chatter4(const std_msgs::String::ConstPtr& msg);

private:
	ros::Subscriber sub_, sub1_,sub2_,sub3_;
	ros::Publisher pub;
    ros::Duration d;

};



#endif /* IVTHREAD_SRC_THREADSPIN_H_ */
