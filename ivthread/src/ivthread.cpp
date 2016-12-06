/*
 * ivthread.cpp
 *
 *  Created on: 2016年8月2日
 *      Author: yin
 */
#include<iostream>
#include "threadspin.h"
#include "threaddemo.h"
#include "asyncspin.h"

using namespace std;

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "ivthread");
  ros::NodeHandle nh;
  //you can only use one of the following class;
 //testing one of them by blocking the other two;
  //threadspin threadspin(nh);
  threaddemo threaddemo(nh);
  //asyncspin asyncspin(nh);
  return 0;
}




