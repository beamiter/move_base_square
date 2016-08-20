#include "ivnav.h"
#include "ivamcl.h"
#include <iostream>

int main (int argc, char **argv)
{
  ros::init(argc, argv, "ivnavigation");
  ros::NodeHandle nh;
  //ivnav ivnav(nh);
  ivamcl ivamcl(nh);
  ros::spin();
  return 0;
}