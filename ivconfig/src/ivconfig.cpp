/*************************************************************************
        > File Name: ivconfig.cpp
        > Author:
        > Mail:
        > Created Time: 2016年08月01日 星期一 17时22分40秒
 ************************************************************************/

#include "ivcfg.h"
#include <cmath>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "ivconfig");
  ros::NodeHandle nh;
  ivcfg ivcfg(nh);
  return 0;
}
