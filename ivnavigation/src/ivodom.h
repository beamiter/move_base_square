#ifndef _IVODOM_H
#define _IVODOM_H

// c++ lib
#include <vector>
#include <boost/bind.hpp>
// ROS lib
#include "ros/ros.h"
#include "ros/time.h"
// other lib
#include <cmath>
#include <time.h>

#include "std_msgs/String.h"

#include <dynamic_reconfigure/server.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <nav_msgs/Odometry.h>

#include <visualization_msgs/Marker.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <move_base_msgs/MoveBaseGoal.h>
#include <move_base_msgs/MoveBaseFeedback.h>
#include <algorithm>
#include <iomanip>
#include <boost/function.hpp>
#include <boost/bind.hpp>

/* FOREGROUND */

#define RST  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST
#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

using namespace std;

class ivodom{
public:
  ivodom(ros::NodeHandle nh);
  ~ivodom();
  
  
  
private:
  void get_odom();
  ros::Subscriber pose_sub;
  ros::Publisher cmd_vel;
  float looprate, linear_speed, goal_distance, distance, last_angle;
  float angular_tolerance, goal_angle, rotation, turn_angle;
  float rate, angular_speed;
  
  
  float radians(float r);
  float normalize_angle(float angle);
  void shutdown();
  void init_vel();
  
  
  
  tf::TransformBroadcaster broader;
  tf::TransformListener listener;
  tf::StampedTransform transform;

  
  geometry_msgs::Twist move_cmd;
  tf::Vector3 pos;
  
  std::string odom_frame, base_frame;
  
  

  
  
  
  
  
  
  
  
  
  
protected:
  
  
  
  
  
  
  
  
  
};

#endif