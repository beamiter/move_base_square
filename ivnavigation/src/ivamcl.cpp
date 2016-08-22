#include "ivamcl.h"
#include <iostream>

using namespace std;
ivamcl::ivamcl(ros::NodeHandle nh):move_base("move_base", true)
{
   float looprate = 1.0;
  nh.param("rest_time",rest_time,5);
  nh.param("fake_test",fake_test,false);

  
  init_pose();
  
  vel_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 5, true);
  
  // while(!move_base.waitForServer(ros::Duration(5)))
  // {
  //     ROS_INFO("Waiting for move base action server to start.");
  // }
  ROS_INFO("Waiting for move base action server to start.");
  move_base.waitForServer(ros::Duration(5));
  ROS_INFO("Connected to move base server, move base action server started!");
  
  n_locations = vpose.size();
  ROS_INFO_STREAM(n_locations);
  n_goals = 0;
  n_successes = 0;
  i = n_locations;
  
  init_vsequence(i);
  distance_traveled = 0;
  start_time = ros::Time::now();
  temp_time = ros::Time::now();
  running_time = 0.0;
  location = 0;
  last_location = 0;
  std::cout << FGRN("*** Click the 2D Pose Estimate button in RViz to set the robot's initial pose...")<<std::endl;
 ros::topic::waitForMessage<geometry_msgs::PoseWithCovarianceStamped>("initialpose");

  pose_sub = nh.subscribe("initialpose",5, &ivamcl::update_initial_pose, this);
  //ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
  if (initial_pose.header.frame_id == "")
  {
    ros::Duration(1.0).sleep();
    std::cout << FYEL("************waiting for the initialization!!*****************") << std::endl;
  }
  ROS_DEBUG("Starting amcl navigation test");
  ros::Rate loop_rate(looprate);
  while (ros::ok())
  {
    ros::spinOnce();
    if (i == n_locations)
    {
      
      i = 0;
      srand(time(0));
      std::random_shuffle(vsequence.begin(), vsequence.end());
      // while (vsequence.at(i) = last_location)
      // {
      //   i = (i+1)%n_locations;
      // }
      if (vsequence.at(i) = last_location)
        i +=1;
    }
    location = vsequence.at(i);
    if (initial_pose.header.frame_id == "map")
    // if (initial_pose.header.stamp == ros::Time(0))
    {
      distance = sqrt(pow(vpose.at(location).position.x-
			      vpose.at(last_location).position.x, 2)+
                              pow(vpose.at(location).position.y-
			      vpose.at(last_location).position.y, 2));
    }
    else
    {
      std::cout << FYEL("Updating current pose...") << std::endl;
      distance = sqrt(pow(vpose.at(location).position.x-
			      initial_pose.pose.pose.position.x, 2)+
                      pow(vpose.at(location).position.y-
			      initial_pose.pose.pose.position.y, 2));
      initial_pose.header.frame_id = "map";
      // initial_pose.header.stamp == ros::Time(0);
    }
    last_location = location;
    i+=1;
    n_goals +=1;
    goal.target_pose.pose = vpose.at(location);
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();
    
    ROS_INFO_STREAM(gp_string(location).c_str());
    move_goal(goal);
    
    running_time = (ros::Time::now().toSec() - temp_time.toSec())/60;
    total_time = (ros::Time::now().toSec() - start_time.toSec()) /60.0;
    temp_time = ros::Time::now();
    
    ROS_INFO_STREAM("Success so far: "<<n_successes<<"/"<<n_goals
		    <<"="<<(n_successes/n_goals)<<std::endl
		    <<"Running time: "<<setiosflags(ios::fixed)<<setprecision(2)<<running_time<<" min"<<std::endl
		    <<"Single traveled distance: "<<distance<<" m\t"<<"Total distance traveled: "<<distance_traveled<<" m"<<std::endl
		    << FBLU("The action lasts for: ")<<setprecision(2)<<total_time<<" min"<<std::endl);
     loop_rate.sleep();   
    //ros::Duration(rest_time).sleep();
  }
  
}

ivamcl::~ivamcl()
{

}

void ivamcl::move_goal(move_base_msgs::MoveBaseGoal goal)
{
  ros::NodeHandle nh;
  move_base.sendGoal(goal, boost::bind(&ivamcl::doneCb, this, _1),
                            boost::bind(&ivamcl::activeCb, this), boost::bind(&ivamcl::feedbackCb, this));
  bool finished_before_timeout = move_base.waitForResult(ros::Duration(120.0));
  if (finished_before_timeout) {
    actionlib::SimpleClientGoalState state = move_base.getState();
    if (state == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
    n_successes +=1;
    distance_traveled += distance;
    }
//    if (move_base.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
//    {
//    n_successes +=1;
//    distance_traveled += distance;
//    }
    ROS_INFO("Action finished: %s", state.toString().c_str());
  } 
  else
  {
    move_base.cancelGoal();
    ROS_ERROR("Action did not finish before the time out....");
    pose_sub = nh.subscribe("initialpose",5, &ivamcl::update_initial_pose, this); 
    n_goals +=1;
    goal.target_pose.pose = vpose.at(i);
    goal.target_pose.header.frame_id = "map";
    ROS_ERROR_STREAM(initial_pose.header.frame_id);
    goal.target_pose.header.stamp = ros::Time::now();
    move_goal(goal);
  }

}


void ivamcl::doneCb(const actionlib::SimpleClientGoalState& state)
{
  ROS_INFO("Finished in state [%s]", state.toString().c_str());
}

void ivamcl::activeCb()
{
  std::cout << FCYN("Goal just went active") << std::endl;
}
void ivamcl::feedbackCb()
{
  std::cout << FMAG("The action is in progress...") << std::endl;
}



void ivamcl::init_vsequence(const int& num)
{
  for(int i=0; i<num; i++)
  {
    ivamcl::vsequence.push_back(i);
  }
}


void ivamcl::update_initial_pose(const geometry_msgs::PoseWithCovarianceStamped& pose)
{
  ROS_ERROR("Update initial pose OK!!!");
  initial_pose.header.frame_id = pose.header.frame_id;
  initial_pose.header.seq = pose.header.seq;
  initial_pose.header.stamp = pose.header.stamp;
  initial_pose.pose.pose = pose.pose.pose;
  initial_pose.pose.covariance = pose.pose.covariance;
}


void ivamcl::init_pose()
{
  init_subpose(0.643, 4.720, 0.000, 0.000, 0.000, 0.223, 0.975);
  init_subpose(-1.994, 4.382, 0.000, 0.000, 0.000, -0.670, 0.743);
  init_subpose(-3.719, 4.401, 0.000, 0.000, 0.000, 0.733, 0.680);
  init_subpose(0.720, 2.229, 0.000, 0.000, 0.000, 0.786, 0.618);
  init_subpose(1.471, 1.007, 0.000, 0.000, 0.000, 0.480, 0.877);
  init_subpose(-0.861, -0.019, 0.000, 0.000, 0.000, 0.892, -0.451);
}

void ivamcl::init_subpose(const double& x, const double& y, const double& z,
			  const double& qx, const double& qy, const double& qz, const double& qw)
{
  geometry_msgs::Pose p;
  geometry_msgs::Point pt;
  p.position.x = pt.x = x;
  p.position.y = pt.y = y;
  p.position.z = pt.z = z;
  p.orientation.x = qx;
  p.orientation.y = qy;
  p.orientation.z = qz;
  p.orientation.w = qw;
  vpoint.push_back(pt);
  vpose.push_back(p);
}



std::string ivamcl::gp_string(const int& gp) const
{
  switch(gp)
  {
    case hall_foyer:
      return "hall_foyer";
    case hall_kitchen:
      return "hall_kitchen";
    case hall_bedroom:
      return "hall_bedroom";
    case living_room1:
      return "living_room1";
    case living_room2:
      return "living_room2";
    case dining_room1:
      return "dining_room1";
    default :
      ROS_ERROR("Unhandled goal position: %u!", gp);
      break;
  }

}

std::string ivamcl::gs_string(const int& gs) const
{
      switch(gs)
    {
      case PENDING:
        return "PENDING";
      case ACTIVE:
        return "ACTIVE";
      case RECALLED:
        return "RECALLED";
      case REJECTED:
        return "REJECTED";
      case PREEMPTED:
        return "PREEMPTED";
      case ABORTED:
        return "ABORTED";
      case SUCCEEDED:
        return "SUCCEEDED";
      case LOST:
        return "LOST";
      default:
        ROS_ERROR("Unhandled GoalState: %u!", gs);
        break;
    }

}
