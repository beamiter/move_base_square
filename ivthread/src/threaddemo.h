/*
 * thread.h
 *
 *  Created on: 2016年8月2日
 *      Author: yin
 */

#ifndef IVTHREAD_SRC_THREADDEMO_H_
#define IVTHREAD_SRC_THREADDEMO_H_

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

class threaddemo
{
public:
	threaddemo(ros::NodeHandle nh);
	~threaddemo();
    void chatterCallbackMainQueue(const std_msgs::String::ConstPtr& msg);
    void chatterCallbackCustomQueue(const ivthread::test::ConstPtr& msg);
    void chatterCallbackTestQueue(const ivthread::test::ConstPtr& msg);
    void callbackThread_();
    void callbackThread1_();

private:
	ros::Subscriber sub_, sub,sub1_;
	ros::Publisher pub;
    ros::SubscribeOptions ops_,ops1_;
    ros::CallbackQueue g_queue_,g_queue1_;
    boost::function<void( const ivthread::test::ConstPtr &)> func_,func1_;
    boost::function<void ()> f_,f1_;

};



#endif /* IVTHREAD_SRC_THREADDEMO_H_ */
