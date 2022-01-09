// BoostTcpServer.cpp : 定义控制台应用程序的入口点。
//

#include <iostream>
#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/thread.hpp"

using namespace std;
using namespace boost::asio;

#ifdef _MSC_VER
#define _WIN32_WINNT 0X0501 //避免VC下编译警告
#endif

#define PORT 1000
#define IPV6
//#define IPV4

class AsyncServer
{
public:
    //构造函数
    AsyncServer(io_service &io, ip::tcp::endpoint &ep) : ios(io), acceptor(io, ep)
    {
        // acceptor(ios,ep);
        start();
    }
    //启动异步接受客户端连接
    void start()
    {
        sock_ptr sock(new ip::tcp::socket(ios));
        //当有连接进入时回调accept_handler函数
        acceptor.async_accept(*sock,
                              boost::bind(&AsyncServer::accept_handler, this, boost::asio::placeholders::error, sock));
    }

private:
    io_service &ios;
    ip::tcp::acceptor acceptor;
    typedef boost::shared_ptr<ip::tcp::socket> sock_ptr;

    void accept_handler(const boost::system::error_code &ec, sock_ptr sock)
    {
        if (ec)
            return;
        //输出客户端连接信息
        std::cout << "remote ip:" << sock->remote_endpoint().address() << endl;
        std::cout << "remote port:" << sock->remote_endpoint().port() << std::endl;
        //异步向客户端发送数据，发送完成时调用write_handler
        sock->async_write_some(buffer("I heard you!"),
                               bind(&AsyncServer::write_handler, this, boost::asio::placeholders::error));
        //再次启动异步接受连接
        start();
    }

    void write_handler(const boost::system::error_code &)
    {
        cout << "send msg complete!" << endl;
    }
};

int _tmain(int argc, char *argv[])
{
    try
    {
        //定义io_service对象
        io_service ios;
        //定义服务端endpoint对象(协议和监听端口)
#ifdef IPV4
        ip::tcp::endpoint serverep(ip::tcp::v4(), PORT);
#endif

#ifdef IPV6
        ip::tcp::endpoint serverep(ip::tcp::v6(), PORT);
#endif
        //启动异步服务
        AsyncServer server(ios, serverep);
        //等待异步完成
        ios.run();
    }
    catch (std::exception &e)
    {
        cout << e.what() << endl;
    }
    return 0;
}