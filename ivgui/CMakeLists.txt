cmake_minimum_required(VERSION 2.8.3)

project(ivgui)

find_package(catkin REQUIRED COMPONENTS	message_generation rospy std_msgs)
	
add_service_files(DIRECTORY srv
                  FILES
                  SetBatteryLevel.srv)
            
add_message_files(DIRECTORY msg
                  FILES
                  ivgui.msg
)

generate_messages(DEPENDENCIES std_msgs)

catkin_package(DEPENDS CATKIN DEPENDS message_runtime std_msgs)