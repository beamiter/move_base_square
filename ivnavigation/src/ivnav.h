#ifndef _IVNAV_H
#define _IVNAV_H

// c++ lib
#include <vector>
#include <boost/bind.hpp>
// ROS lib
#include "ros/ros.h"
#include "ros/time.h"
// other lib
#include <sstream>
#include <cmath>

#include "std_msgs/String.h"
#include <dynamic_reconfigure/server.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <nav_msgs/Odometry.h>

#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseFeedback.h>

const double pi = M_PI;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client;

class ivnav{
public:
  ivnav(ros::NodeHandle nh);
  ~ivnav();

private:

  tf::TransformBroadcaster caster;
  tf::TransformListener listener;
  move_base_msgs::MoveBaseGoal goal;
  move_base_msgs::MoveBaseFeedback feedback;
  void move_goal(move_base_msgs::MoveBaseGoal goal);
  void init_markers();	
  void shutdown();
  ros::Subscriber sub;
  ros::Publisher marker_pub, vel_pub;
  tf::Transform transform;
  action_client move_base;
  tf::Quaternion q;
  std::vector<visualization_msgs::Marker> vmarker;
  std::vector<geometry_msgs::Pose> vpose;
	
  void doneCb(const actionlib::SimpleClientGoalState& state);
  void activeCb();
  void feedbackCb();
  

  void transform_marker(const double& x, const double& y, const double& z,
			const double& roll, const double& pitch, const double& yaw);
	
protected:

};


#endif