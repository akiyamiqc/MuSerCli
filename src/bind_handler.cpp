#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

void print(const boost::system::error_code &e,
           boost::asio::steady_timer *t, /*获取计时器对象*/
           int *count)                   /*获取触发次数*/
{
    if (*count < 5)
    {
        std::cout << *count << std::endl;
        ++(*count);
        t->expires_at(t->expiry() + boost::asio::chrono::seconds(1)); /*给计时器续一秒*/
        /*用bind把 t 和 count 绑定到print函数上 然后把生成的函数对象传给async_wait()*/
        t->async_wait(boost::bind(print, boost::asio::placeholders::error, t, count));
    }
}

int main()
{
    boost::asio::io_context io;
    int count = 0;
    boost::asio::steady_timer t(io, boost::asio::chrono::seconds(1));
    t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t, &count));
    io.run();
    std::cout << "Final count is " << count << std::endl;

    return 0;
}
