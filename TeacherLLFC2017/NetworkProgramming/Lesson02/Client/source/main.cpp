#include <iostream>
#include <vector>
#include <string>

#include <boost/asio.hpp>

const int MAX_LENGTH = 1024;

int main(void)
{
    try
    {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::endpoint remote_end_point(boost::asio::ip::address::from_string("127.0.0.1"), 8888);
        boost::asio::ip::tcp::socket socket(io_context);
        boost::system::error_code error_code = boost::asio::error::host_not_found;
        socket.connect(remote_end_point, error_code);
        if (error_code)
        {
            std::cerr << "Failed to connect!\n"
                << "Error Code: " << error_code.value() << '\n'
                << "Error Message: " << error_code.message() << std::endl;
            return error_code.value();
        }
        std::cout << "Enter message: ";
        std::string request;
        request.reserve(MAX_LENGTH);
        std::cin.getline(request.data(), MAX_LENGTH);
        boost::asio::write(socket, boost::asio::buffer(request.data(), request.length()));

        std::string reply;
        reply.reserve(MAX_LENGTH);
        std::size_t reply_length = boost::asio::read(socket, boost::asio::buffer(reply.data(), request.length()));
        std::cout << "Reply is: ";
        std::cout.write(reply.data(), reply_length);
        std::cout << std::endl;


    }
    catch (std::exception& exception)
    {
        std::cerr << "Exception: " << exception.what() << std::endl;
    }
}