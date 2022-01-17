#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // for time_t, time and ctime;
    time_t now = time(0);
#if defined _WIN32
    char str[126];
    ctime_s(str, sizeof(str), &now);
    return str;
#else
    return ctime(&now);
#endif
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), 13));
        for (;;)
        {
            boost::array<char, 1> recv_buf;
            udp::endpoint remote_endpoint;
            socket.receive_from(boost::asio::buffer(recv_buf), remote_endpoint);
            std::string message = make_daytime_string();
            boost::system::error_code ignored_error;
            socket.send_to(boost::asio::buffer(message),
                           remote_endpoint, 0, ignored_error);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}