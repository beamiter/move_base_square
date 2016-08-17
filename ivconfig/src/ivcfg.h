/*************************************************************************
        > File Name: config.h
        > Author:
        > Mail:
        > Created Time: 2016年08月01日 星期一 17时22分59秒
 ************************************************************************/

#ifndef _CONFIG_H
#define _CONFIG_H

// c++ lib
#include <vector>
// ROS lib
#include "ros/ros.h"
#include "ros/time.h"
// other lib
#include <sstream>

#include "std_msgs/String.h"
#include <dynamic_reconfigure/server.h>
#include <ivconfig/ivconfigConfig.h>

using namespace std;

// Custom message includes. Auto-generated from msg/ directory.

// change you configure class here
typedef ivconfig::ivconfigConfig config_;

class ivcfg {
public:
  ivcfg(ros::NodeHandle nh);
  ~ivcfg();

  void callback(config_ &config, uint32_t level);

private:
  config_ m_config;
  ros::Subscriber sub_;
  ros::Publisher pub_;
};

#endif
