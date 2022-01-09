#include <iostream>
#include <boost/asio.hpp> // 引入asio整体头文件

int main()
{
    boost::asio::io_context io;  // 定义执行上下文对象
    boost::asio::steady_timer t( // 创建对象绑定至io_context并开始计时
        io,
        boost::asio::chrono::seconds(5));

    t.wait(); // 阻塞
    std::cout << "Hello, world!" << std::endl;

    return 0;
}
