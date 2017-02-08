#include "ros/ros.h"
#include "ros/time.h"
#include <string> 
#include <boost/asio.hpp> 
using namespace std; 
using namespace boost::asio; 
#include <dynamic_reconfigure/server.h>
#include <ivudp/ivudpConfig.h>

typedef ivudp::ivudpConfig config_;

string send_data = "01234567890123456789042345678901234567890123456789012345678901234567890";/*the contents to be sent*/ 

void callback(config_& config, uint32_t level)
{
    ROS_INFO_STREAM("Updating the udp send data!!!");

    std::string temp = config.send_data_0 + config.send_data_1 + config.send_data_2 \
		     + config.send_data_3 + config.send_data_4 + config.send_data_5 \
		     + config.send_data_6 + config.send_data_7;
    send_data = temp;
    ROS_ERROR_STREAM("send_data: "<<send_data);
}

int main(int argc, char* argv[]) 
{      
    ros::init(argc, argv, "udpsender");  
    io_service my_io_service; 
// ip::udp::endpoint my_local_enpoint(ip::udp::v4(),0);/*another way to create endpoint*/ 
//   my_udp_socket.open(my_login_server_endpoint.protocol());   
//   my_udp_socket.bind(my_local_enpoint); 
 
    ip::udp::endpoint local_endpoint(ip::udp::v4(), 7777);//create endpoint,this a local endpoint 
 
    ip::udp::endpoint remote_endpoint(ip::address_v4::from_string("192.168.0.105"), 3000);//create a remote endpoint 
    //don't  fill (ip::udp::v4()) in the first parameter,it will cause that the contents are seny out the failure! 
    ip::udp::socket socket(my_io_service, local_endpoint);//create socket and bind the endpoint 
 
    dynamic_reconfigure::Server<config_> srv;
    dynamic_reconfigure::Server<config_>::CallbackType f;
    f = boost::bind(callback, _1, _2);
    srv.setCallback(f);
    try 
    {  
	ros::Rate loop_rate(10.0);
        while (ros::ok()) 
        {
        ros::spinOnce();
	ROS_ERROR_STREAM("send_data: "<<send_data);
        socket.send_to(buffer(send_data, send_data.length()), remote_endpoint); 
        loop_rate.sleep();
        }
    } 
    catch (std::exception& e)//to get the error when sending 
    { 
        std::cerr << e.what() << std::endl; 
    } 
 
    return 0; 
} 