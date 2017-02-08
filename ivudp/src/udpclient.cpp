#include "ros/ros.h"
#include "ros/time.h"
#include <string>  
#include <boost/asio.hpp>  
using namespace std;  
using namespace boost::asio;
int main(int argc, char* argv[])  
{  
    ros::init(argc, argv, "udpclient");
    cout << "udp client start."<<endl;
    io_service ios;
    ip::udp::endpoint send_ep(ip::address::from_string("192.168.0.103"), 3000);
    ip::udp::socket sock(ios);
    sock.open(ip::udp::v4());
    char buf[1];
    sock.send_to(buffer(buf), send_ep);
    vector<char> v(100, 0);
    ip::udp::endpoint recv_ep;
    sock.receive_from(buffer(v), recv_ep);
    cout << "recv from "<<recv_ep.address()<<";";
    cout << &v[0] << endl;
    return 0;  
}  