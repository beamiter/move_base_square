#include "ivodom.h"
#include <iostream>

ivodom::ivodom(ros::NodeHandle nh)
{
  cmd_vel = nh.advertise<geometry_msgs::Twist>("/cmd_vel",5,true);
  rate = 20;
  ros::Rate loop_rate(rate);
  linear_speed = 0.15;
  goal_distance = 1.0;
  angular_speed = 0.5;
  angular_tolerance = radians(1.0);
  goal_angle = M_PI;
  odom_frame = "/odom";
  try{
    listener.waitForTransform(odom_frame,"/base_footprint",ros::Time(0),ros::Duration(1.0));
    base_frame = "/base_footprint";
  }
  catch (tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    try{
      listener.waitForTransform(odom_frame,"/base_link",ros::Time(0),ros::Duration(1.0));
      base_frame = "/base_link";
      
    }
    catch (tf::ConnectivityException exc){
      ROS_INFO("Cannot find transform between /odom and /base_link or /base_footprint");
      ROS_ERROR("%s",exc.what());
      ROS_ERROR("tf Exception");
      
    }
  }
  // for (int i=0; i<2; i++)
  while (ros::ok())
  {
    move_cmd.linear.x = linear_speed;
    get_odom();
    float x_start = pos.getX();
    float y_start = pos.getY();
    distance = 0;
    while (distance < goal_distance && ros::ok())
    {
      cmd_vel.publish<geometry_msgs::Twist>(move_cmd);
      loop_rate.sleep();
      get_odom();
      distance = sqrt(pow((pos.getX() - x_start),2) +
	pow((pos.getY() - y_start),2));
    }
    init_vel();
    cmd_vel.publish<geometry_msgs::Twist>(move_cmd);
    ros::Duration(1.0).sleep();
    move_cmd.angular.z = angular_speed;
    last_angle = rotation;
    turn_angle = 0.0;
    while (abs(turn_angle + angular_tolerance) < abs(goal_angle) && ros::ok())
    {
      cmd_vel.publish<geometry_msgs::Twist>(move_cmd);
      loop_rate.sleep();
      get_odom();
      float delta_angle = rotation - last_angle;
      turn_angle += delta_angle;
      last_angle = rotation;
    }
    init_vel();
    cmd_vel.publish<geometry_msgs::Twist>(move_cmd);
    ros::Duration(1.0).sleep();
  }
  shutdown();
  
}

ivodom::~ivodom()
{

}

void ivodom::get_odom()
{

  tf::Quaternion q;
  try{
    listener.lookupTransform(odom_frame,base_frame,ros::Time(0),transform);

    pos = transform.getOrigin();
    q = transform.getRotation();
    rotation = q.getAngle();
    
  }
  catch(tf::TransformException ex){
    ROS_ERROR("%s",ex.what());
    ROS_ERROR("tf Exception!!!");
    
  }

}

float ivodom::radians(float r)
{
  float foo = r*M_PI/180.0;
  foo = normalize_angle(foo);
  return foo;
}
void ivodom::shutdown()
{
  ROS_ERROR("Stopping the robot...");
  init_vel();
  cmd_vel.publish<geometry_msgs::Twist>(move_cmd);
  ros::Duration(1.0).sleep();
}


void ivodom::init_vel()
{
  memset(&move_cmd, 0.0, sizeof(move_cmd));
  //move_cmd.angular.x = move_cmd.angular.y = move_cmd.angular.z = 0.0;
  //move_cmd.linear.x =move_cmd.linear.x = move_cmd.linear.x = 0.0;
}

float ivodom::normalize_angle(float angle)
{
  float foo = angle;
  while (foo > M_PI)
  {
    foo -= 2.0*M_PI;
  }
  
  while (foo < -M_PI)
  {
    foo += 2.0*M_PI;
  }
  return foo;
}


























