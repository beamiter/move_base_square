#include "ivnav.h"
#include <iostream>

ivnav::ivnav(ros::NodeHandle nh): move_base("move_base", true)
{
  q.setRPY(0, 0, 0);
  float square_size = 1.5;
  float euler_angles[4] = {pi / 2, pi, 3 * pi / 2, 0.0};
  ivnav::transform_marker(square_size, 0.0-0.5, 0.0, 0.0, 0.0, euler_angles[0]);
  ivnav::transform_marker(square_size, square_size, 0.0, 0.0, 0.0, euler_angles[1]);
  ivnav::transform_marker(0.0-0.5, square_size, 0.0, 0.0, 0.0, euler_angles[2]);
  ivnav::transform_marker(0.0-0.5, 0.0-0.5, 0.0, 0.0, 0.0, euler_angles[3]);
  ivnav::init_markers();
  ivnav::vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 5, true);
  // while(!move_base.waitForServer(ros::Duration(5)))
  // {
  //     ROS_INFO("Waiting for move base action server to start.");
  // }
  ROS_INFO("Waiting for move base action server to start.");
  ivnav::move_base.waitForServer(ros::Duration(6));
  ROS_INFO("Move base action server started, starting navigation test");

  ros::Rate loop_rate(1.0);
  while (ros::ok())
  {
      geometry_msgs::Twist vel;
      std::vector<visualization_msgs::Marker>::const_iterator iter;
      vel.linear.x = vel.angular.z = 1.0;
      vel.linear.y = vel.linear.z = vel.angular.x = vel.angular.y = 0.0;

      ivnav::vel_pub.publish<geometry_msgs::Twist>(vel);

      for (iter = ivnav::vmarker.begin(); iter != ivnav::vmarker.end(); iter++) {
      marker_pub.publish<visualization_msgs::Marker>(*iter);
      ivnav::goal.target_pose.header.frame_id = "map";
      ivnav::goal.target_pose.header.stamp = ros::Time::now();
      ivnav::goal.target_pose.pose = (*iter).pose;
      ivnav::move_goal(ivnav::goal);
      ros::spinOnce();
      loop_rate.sleep();
    }
  }
}

ivnav::~ivnav()
{

}


void ivnav::init_markers()
{
  ros::NodeHandle nh;
  float marker_scale = 0.2;
  int marker_lifetime = 0;
  std::string marker_ns = "waypoints";
  float marker_id = 0;
  float r = 1.0, g = 0.7, b = 1.0, a = 1.0;
  std::string frame_id = "odom";
  marker_pub = nh.advertise<visualization_msgs::Marker>("waypoint_markers", 5, true);
  for (int i = 0; i < 4; i++) {
    visualization_msgs::Marker p;
    p.ns = marker_ns;
    p.header.frame_id = frame_id;
    p.id = marker_id++;
    p.type = visualization_msgs::Marker::CUBE_LIST;
    p.header.stamp = ros::Time::now();
    p.action = visualization_msgs::Marker::ADD;
    p.lifetime = ros::Duration(marker_lifetime);
    p.scale.x = marker_scale;
    p.scale.y = marker_scale;
    p.scale.z = marker_scale;
    p.color.r = r;
    p.color.g = g;
    p.color.b = b;
    p.color.a = a;
    p.pose = ivnav::vpose.at(i);

    geometry_msgs::Point pt;
    pt.x = 0.0;
    pt.y = 0.0;
    pt.z = 0.0;
    p.points.push_back(pt);

    ivnav::vmarker.push_back(p);
  }
}

void ivnav::shutdown()
{
  geometry_msgs::Twist vel;
  vel.angular.x = vel.angular.y = vel.angular.z = 0.0;
  vel.linear.x = vel.linear.y = vel.linear.z = 0.0;
  ROS_INFO("stoppint the robot...");
  ivnav::move_base.cancelGoal();
  ivnav::vel_pub.publish<geometry_msgs::Twist>(vel);
  ros::Duration(1.0).sleep(); 
  
}

void ivnav::doneCb(const actionlib::SimpleClientGoalState& state)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
}

void ivnav::activeCb()
{
  ROS_INFO("Goal just went active");
}


void ivnav::move_goal(move_base_msgs::MoveBaseGoal goal)
{
  ivnav::move_base.sendGoal(goal, boost::bind(&ivnav::doneCb, this, _1),
                            boost::bind(&ivnav::activeCb, this), boost::bind(&ivnav::feedbackCb, this));
  bool finished_before_timeout = move_base.waitForResult(ros::Duration(20.0));
  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = move_base.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  } else
    ROS_INFO("Action did not finish before the time out.");
}

void ivnav::transform_marker(const double& x, const double& y, const double& z,
                             const double& roll, const double& pitch, const double& yaw)

{
  geometry_msgs::Pose p;
  // visualization_msgs::Marker marker;
  float halfYaw = float(yaw) * float(0.5);
  float halfPitch = float(pitch) * float(0.5);
  float halfRoll = float(roll) * float(0.5);
  float cosYaw = cos(halfYaw);
  float sinYaw = sin(halfYaw);
  float cosPitch = cos(halfPitch);
  float sinPitch = sin(halfPitch);
  float cosRoll = cos(halfRoll);
  float sinRoll = sin(halfRoll);
  p.orientation.x = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw; //x
  p.orientation.y = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw; //y
  p.orientation.z = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw; //z
  p.orientation.w = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw; //formerly yzx
  p.position.x = x;
  p.position.y = y;
  p.position.z = z;
  ivnav::vpose.push_back(p);
}

void ivnav::feedbackCb()
{
  ROS_INFO("The action is in progress...");
}

