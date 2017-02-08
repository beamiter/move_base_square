#include "ros/ros.h"
#include "ros/time.h"
#include <string>  
#include <boost/asio.hpp>  
using namespace std;  
using namespace boost::asio;  
int main(int argc, char* argv[])  
{  
    ros::init(argc, argv, "udpreceiver");
    
    io_service my_io_service;  
  
    ip::udp::endpoint local_endpoint(ip::address_v4::from_string("192.168.1.130"), 3010);//create  a local endpoint  
  
    ip::udp::endpoint romote_endpoint; //this enpoint is used to store the endponit from remote-computer  
  
    ip::udp::socket socket(my_io_service, local_endpoint);//create socket and bind the endpoint  
  
    char buffer[40000];  
      
    int nAdd = 0;  
  
    while (1)  
    {     
        memset(buffer, 0, 40000);//to initialize variables  
        nAdd++;  
        socket.receive_from(boost::asio::buffer(buffer, 40000), romote_endpoint);//receive data from  remote-computer  
        ROS_INFO("recv %d datapacket:%s\n",nAdd, buffer);  
    }  
    return 0;  
}  