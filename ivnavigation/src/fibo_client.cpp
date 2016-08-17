#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <ivnavigation/fiboAction.h>
#include <ros/ros.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "fibo_client");

  // create the action client
  // true causes the client to spin its own thread
  actionlib::SimpleActionClient<ivnavigation::fiboAction> ac("fibo", true);

  ROS_INFO("Waiting for action server to start.");
  ROS_INFO_STREAM(ros::this_node::getName());
  // wait for the action server to start
  while (!ac.waitForServer(ros::Duration(2))) // will wait for  time
  {
    ROS_INFO("waiting for the server to come up!");
  }

  ROS_INFO("Action server started, sending goal.");
  // send a goal to the action
  ivnavigation::fiboGoal goal;
  goal.order = 30;
  ac.sendGoal(goal);

  // wait for the action to return
  bool finished_before_timeout = ac.waitForResult(ros::Duration(30.0));

  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = ac.getState();
    ROS_INFO("Action finished: %s", state.toString().c_str());
  } else
    ROS_INFO("Action did not finish before the time out.");

  // exit
  return 0;
}
