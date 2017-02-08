#include "ros/ros.h"
#include "ros/time.h"
#include <string>  
#include <boost/asio.hpp>  
using namespace std;  
using namespace boost::asio;
int main(int argc, char* argv[])  
{  
    ros::init(argc, argv, "udpserver");
    cout << "udp server start."<<endl;
    io_service ios;
    ip::udp::socket sock(ios, ip::udp::endpoint(ip::udp::v4(), 3000));
    for (;;)
    {
      char buf[1];
      ip::udp::endpoint ep;
      boost::system::error_code ec;
      sock.receive_from(buffer(buf), ep, 0, ec);
      if (ec && ec != error::message_size)
      {
	throw boost::system::system_error(ec);
	cout << "send to "<<ep.address()<<endl;
	sock.send_to(buffer("hello asio udp"), ep);
      }
      
    } 
    return 0;  
}  