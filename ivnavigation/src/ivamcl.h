#ifndef _IVAMCL_H
#define _IVAMCL_H

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

using namespace std;

#define random(x) (rand() % x)

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> action_client;
typedef geometry_msgs::PoseWithCovarianceStamped stampedpose;

typedef enum emGoalStatus{
    PENDING,
    ACTIVE,
    RECALLED,
    REJECTED,
    PREEMPTED,
    ABORTED,
    SUCCEEDED,
    LOST
}emGoalStatus;

typedef enum emGoalPosition{
  hall_foyer,
  hall_kitchen,
  hall_bedroom,
  living_room1,
  living_room2,
  dining_room1
}emGoalPosition;

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


class ivamcl{
public:
  ivamcl(ros::NodeHandle nh);
  ~ivamcl();
  
private:
  int rest_time, i;
  int distance_traveled, location, last_location;
  int n_locations, n_goals, n_successes, distance;
  
  //double start_time, running_time;
  ros::Time start_time, temp_time;
  double total_time, running_time;
  
  bool fake_test;
  emGoalPosition goalposition;
  emGoalStatus goalstatus;
  move_base_msgs::MoveBaseGoal goal;
  std::vector<geometry_msgs::Pose> vpose;
  std::vector<geometry_msgs::Point> vpoint;
  std::vector<int> vsequence;
  geometry_msgs::PoseWithCovarianceStamped initial_pose;
  std::string gs_string(const int& gs) const;
  std::string gp_string(const int& gp) const;
  
  ros::Subscriber pose_sub;
  ros::Publisher marker_pub, vel_pub;
  
  void init_pose();
  void init_subpose(const double& x, const double& y, const double& z,
		    const double& qx, const double& qy, const double& qz, const double& qw);
  
  void init_vsequence(const int& num);
  void update_initial_pose(const geometry_msgs::PoseWithCovarianceStamped& pose);
  action_client move_base;
  
  void doneCb(const actionlib::SimpleClientGoalState& state);
  void activeCb();
  void feedbackCb();
  void move_goal(move_base_msgs::MoveBaseGoal goal);
  
  
protected:
  
  
  
  
};

#endif