#include "ros/ros.h"

#include "std_msgs/String.h"
#include "stdlib.h"
#include <std_msgs/Float32.h>
#include <time.h>

#define random(x) (rand() % x)

typedef struct sAddAttr{
  int posattr;
  int roadattr;
}sAddAttr;

int main(int argc, char **argv) {

  ros::init(argc, argv, "rd_generator");
  ros::NodeHandle n;

  sAddAttr addattr;
  memset(&addattr, 0, sizeof(addattr));

  ros::Publisher chatter_pub =

      n.advertise<std_msgs::Float32>("/random_number", 1000);

  ros::Rate loop_rate(1.0);

  int count = 0;
  while (ros::ok()) {
    srand(count);
    float a = 0, b = 0;
    n.getParam("pos_attr", addattr.posattr);
    n.getParam("road_attr", addattr.roadattr);
    n.getParam("pcontrol", a);
    n.getParam("icontrol", b);

    std_msgs::Float32 msg;
    msg.data = random(10);
    // ROS_INFO("%f", msg.data);
    chatter_pub.publish(msg);
    ROS_INFO("%.2f, %.2f", a, b);
    ROS_INFO("%d, %d", addattr.posattr, addattr.roadattr);

    ros::spinOnce();

    loop_rate.sleep();

    ++count;
  }

  return 0;
}
