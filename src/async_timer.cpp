#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code& /*e*/)
{
	std::cout << "Hello, world!" << std::endl;
}

int main()
{
	boost::asio::io_context io;

	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));

	t.async_wait(&print);	// 当异步操作wait结束时,执行回调函数print()

	io.run();

	return 0;
}
