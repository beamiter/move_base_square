#include <ivnavigation/ivnavAction.h>
#include <ivnavigation/ivnavActionFeedback.h>
#include <ivnavigation/ivnavActionGoal.h>
#include <ivnavigation/ivnavActionResult.h>
#include <ivnavigation/ivnavFeedback.h>
#include <ivnavigation/ivnavGoal.h>
#include <ivnavigation/ivnavResult.h>

#include <actionlib/client/simple_action_client.h>
#include <actionlib/server/simple_action_server.h>

typedef actionlib::SimpleActionServer<ivnavigation::ivnavAction> Server;

void move_callback(const ivnavigation::ivnavGoalConstPtr &goal, Server *srv) {
  // Do lots of awesome groundbreaking robot stuff here
  srv->setSucceeded();
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "ivaction_server");
  ros::NodeHandle n;
  Server server(n, "ivaction", boost::bind(&move_callback, _1, &server), false);
  server.start();
  ros::spin();
  return 0;
}
