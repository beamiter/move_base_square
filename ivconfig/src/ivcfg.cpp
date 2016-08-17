/*************************************************************************
        > File Name: config.cpp
        > Author:
        > Mail:
        > Created Time: 2016年08月01日 星期一 17时22分52秒
 ************************************************************************/

#include "ivcfg.h"
#include <iostream>
using namespace std;
ivcfg::ivcfg(ros::NodeHandle nh) {
  std::string s0 = "unknown";
  int s1 = 0;
  double s2 = 0.0;
  bool s3;
  ROS_INFO("Starting to spin...");
  // boost bind invoking object member function;
  dynamic_reconfigure::Server<config_> srv;
  dynamic_reconfigure::Server<config_>::CallbackType f;
  f = boost::bind(&ivcfg::callback, this, _1, _2);
  srv.setCallback(f);
  ros::Rate loop_rate(1);

  while (ros::ok()) {
    // please pay attention to the useage of ROS_INFO and ROS_INFO_STREAM

    ros::spinOnce();
    loop_rate.sleep();
  }
}

ivcfg::~ivcfg() {}

void ivcfg::callback(config_ &config, uint32_t level) {

  // ROS_INFO_STREAM("callback ok!");
  ros::NodeHandle nh;
  m_config = config;
  /* please set your parameter here
   *  use "nh.getParam("myparam", ***)" wherever you want to get the parameter
   */
  if(m_config.control)
  {
  nh.setParam("pcontrol", m_config.pcontrol);
  nh.setParam("icontrol", m_config.icontrol);
  nh.setParam("dcontrol", m_config.dcontrol);
  nh.setParam("control", m_config.control);
  }
  if(m_config.attribution)
  {
  nh.setParam("pos_attr", m_config.pos_attr);
  nh.setParam("road_attr", m_config.road_attr);
  nh.setParam("attribution", m_config.attribution);
  }

}
