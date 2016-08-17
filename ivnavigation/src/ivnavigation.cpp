#include "ivnav.h"
#include <iostream>

int main (int argc, char **argv)
{
  ros::init(argc, argv, "ivnavigation");
  ros::NodeHandle nh;
  ivnav ivnav(nh);
  ros::spin();
  return 0;
}