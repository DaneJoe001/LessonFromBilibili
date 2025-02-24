#include <iostream>
#include <memory>
#include <set>

#include <boost/asio.hpp>

const int MAX_LENGTH = 1024;

using socket_ptr = std::shared_ptr<boost::asio::ip::tcp::socket>;
std::set<std::shared_ptr<std::thread>> thread_set;

void session(socket_ptr sock)
{
    try
    {
        for (;;)
        {
            char data[MAX_LENGTH] = { 0 };
            boost::system::error_code error_code;
            std::size_t length = sock->read_some(boost::asio::buffer(data, MAX_LENGTH), error_code);
            if (error_code == boost::asio::error::eof)
            {
                std::cout << "Connnection closed by peer!" << std::endl;
                break;
            }
            else if (error_code)
            {
                throw boost::system::system_error(error_code);
            }
            std::cout << "Received from: " << sock->remote_endpoint().address().to_string() << std::endl;
            std::cout << "Recieved data: " << data << std::endl;
            //回传数据
            boost::asio::write(*sock, boost::asio::buffer(data, length));
        }

    }
    catch (std::exception& exception)
    {
        std::cerr << "Exception in thread: " << exception.what() << std::endl;
    }
}

void server(boost::asio::io_context& io_context, unsigned short port)
{
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    for (;;)
    {
        socket_ptr socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context);
        acceptor.accept(*socket);
        auto thread = std::make_shared<std::thread>(session, socket);
        thread_set.insert(thread);

    }
}

int main(void)
{
    try
    {
        boost::asio::io_context io_contxt;
        server(io_contxt, 8888);
        for (auto& it : thread_set)
        {
            it->join();

        }
    }
    catch (std::exception& exception)
    {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}