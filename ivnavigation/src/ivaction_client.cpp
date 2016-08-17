#include <ivnavigation/ivnavAction.h>
#include <ivnavigation/ivnavActionFeedback.h>
#include <ivnavigation/ivnavActionGoal.h>
#include <ivnavigation/ivnavActionResult.h>
#include <ivnavigation/ivnavFeedback.h>
#include <ivnavigation/ivnavGoal.h>
#include <ivnavigation/ivnavResult.h>

#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<ivnavigation::ivnavAction> Client;

int main(int argc, char **argv) {
  ros::init(argc, argv, "ivaction_client");
  Client client("ivaction", true); // true -> don't need ros::spin()
  while (!client.waitForServer(ros::Duration(2))) {
    ROS_INFO("waiting for the server to come up");
  }
  ivnavigation::ivnavGoal goal;
  // Fill in goal here
  client.sendGoal(goal);
  client.waitForResult(ros::Duration(5.0));
  if (client.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    printf("Yay! The car arrived at the destinations!\n");
  printf("Current State: %s\n", client.getState().toString().c_str());
  return 0;
}
