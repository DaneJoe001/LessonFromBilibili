#include <end_point.h>

int client_end_point()
{
    std::string raw_ip_addr = "127.0.0.1";
    unsigned short port = 8888;
    boost::system::error_code error_code;
    boost::asio::ip::address ip_addr = boost::asio::ip::address::from_string(raw_ip_addr, error_code);
    if (error_code.value() != 0)
    {
        std::cerr << "Failed to open socket!\n"
            << "Error Code: " << error_code.value() << '\n'
            << "Error Message: " << error_code.message() << std::endl;
        return error_code.value();
    }
    //生成端点
    boost::asio::ip::tcp::endpoint end_point(ip_addr, port);
    return 0;
}

//如果是服务端，只需要根据本地地址绑定就可以生成endpoint
int server_end_point()
{
    unsigned short port = 8888;
    //使用IPv4的方式绑定本地地址
    //addre_v6(IPv6)
    boost::asio::ip::address ip_addr = boost::asio::ip::address_v4::any();
    boost::asio::ip::tcp::endpoint end_point(ip_addr, port);
    return 0;
}

int create_tcp_socket()
{
    //创建上下文,旧版本用io_service
    boost::asio::io_context io_context;
    //生成IPv4的协议
    boost::asio::ip::tcp protocol = boost::asio::ip::tcp::v4();
    boost::asio::ip::tcp::socket socket(io_context);
    boost::system::error_code error_code;
    //新版本会自动打开套接字，并检查，不需要手动打开
#define NEW_BOOST_VERSION
#ifndef NEW_BOOST_VERSION
    socket.open(protocol, error_code);
    if (error_code.value() != 0)
    {
        std::cerr << "Failed to open socket!\n"
            << "Error Code: " << error_code.value() << '\n'
            << "Error Message: " << error_code.message() << std::endl;
        return error_code.value();
    }
#endif
}

int create_acceptor_socket()
{
    unsigned short port = 8888;
    //创建上下文,旧版本用io_service
    boost::asio::io_context io_context;
    //新版本只需要创建acceptor
    //默认会进行绑定操作
    boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
    return 0;
}

//旧版本写法
int bind_acceptor_socket()
{
    unsigned short port = 8888;
    boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address_v4::any(), port);
    //创建上下文,旧版本用io_service
    boost::asio::io_context io_context;
    //生成并绑定acceptor
    boost::asio::ip::tcp::acceptor acceptor(io_context, end_point.protocol());
    boost::system::error_code error_code;
    acceptor.bind(end_point, error_code);
    if (error_code.value() != 0)
    {
        std::cerr << "Failed to bind socket!\n"
            << "Error Code: " << error_code.value() << '\n'
            << "Error Message: " << error_code.message() << std::endl;
        return error_code.value();
    }
    return 0;
}

int connect_to_end_point()
{
    std::string raw_ip_addr = "192.168.1.124";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_addr), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        //连接到服务器
        socket.connect(end_point);
    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to connect server!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }

}

//通过解析域名连接服务器
//实际中很少通过域名连接
//一般都会先转换成IP地址
int connect_to_end_point_with_dns()
{

    std::string host = "llfc.club";
    std::string port = "3333";
    boost::asio::io_context io_context;
    //创建dns的解析器
    boost::asio::ip::tcp::resolver::query resolve_query(host, port, boost::asio::ip::tcp::resolver::query::numeric_service);
    boost::asio::ip::tcp::resolver resolver(io_context);
    try
    {
        boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(resolve_query);
        boost::asio::ip::tcp::socket socket(io_context);
        //全局的连接函数
        boost::asio::connect(socket, it);
    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to connect server!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }
    return 0;
}

int accept_new_connection()
{
    //定义监听队列的大小
    const int BACKLOG_SIZE = 32;
    unsigned short port = 8888;
    boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address_v4::any(), port);
    boost::asio::io_context io_context;
    try
    {
        //定义接收器
        boost::asio::ip::tcp::acceptor acceptor(io_context, end_point.protocol());
        acceptor.bind(end_point);
        //开始监听
        acceptor.listen(BACKLOG_SIZE);
        boost::asio::ip::tcp::socket socket(io_context);
        //接收连接
        acceptor.accept(socket);

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to accept new connection!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }
    return 0;
}

void use_const_buffer()
{
    //较为麻烦
    std::string buf = "Hello,world!";
    boost::asio::const_buffer asio_buffer(buf.c_str(), buf.length());
    std::vector<boost::asio::const_buffer>buffers_sequence;
    buffers_sequence.push_back(asio_buffer);
}

void use_buffer_string()
{
    //简易版本
    boost::asio::const_buffers_1 output_buf = boost::asio::buffer("Hello, world!");
}

void use_buffer_array()
{
    const std::size_t BUFFER_SIZE_BYTES = 20;
    std::unique_ptr<char[]>buffer(new char[BUFFER_SIZE_BYTES]);
    auto input_buffer = boost::asio::buffer(static_cast<void*>(buffer.get()), BUFFER_SIZE_BYTES);
}

void write_to_socket(boost::asio::ip::tcp::socket& socket)
{
    std::string buffer = "Hello,world!";
    std::size_t size_written = 0;
    while (size_written != buffer.length())
    {
        size_written += socket.write_some(boost::asio::buffer(buffer.c_str() + size_written, buffer.length() - size_written));
    }
}

int send_data_by_write_some()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        socket.connect(end_point);
        std::string buffer = "Hello,world!";
        int size_send = socket.send(boost::asio::buffer(buffer.c_str(), buffer.length()));
        if (size_send < 0)
        {
            return 0;
        }

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to accept send!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }

}

int send_data_by_write()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        socket.connect(end_point);
        std::string buffer = "Hello,world!";
        int size_send = boost::asio::write(socket, boost::asio::buffer(buffer.c_str(), buffer.length()));
        if (size_send <= 0)
        {
            return 0;
        }

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to accept send!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }

}

std::string read_from_socket(boost::asio::ip::tcp::socket& socket)
{
    const unsigned char MESSAGE_SIZE = 16;
    char buffer[MESSAGE_SIZE] = { 0 };
    std::size_t bytes_read = 0;
    while (bytes_read != MESSAGE_SIZE)
    {
        bytes_read += socket.read_some(boost::asio::buffer(buffer + bytes_read, MESSAGE_SIZE - bytes_read));
    }
    return std::string(buffer, bytes_read);
}

int read_data_by_read_some()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        socket.connect(end_point);
        read_from_socket(socket);

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to read!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }
}

int read_data_by_recieve()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        socket.connect(end_point);
        const unsigned char BUFFER_SIZE = 16;
        char buffer_receive[BUFFER_SIZE];
        int receive_length = socket.receive(boost::asio::buffer(buffer_receive, BUFFER_SIZE));
        if (receive_length <= 0)
        {
            return 0;
        }

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to read!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }
}

int read_data_by_recieve()
{
    std::string raw_ip_address = "127.0.0.1";
    unsigned short port = 8888;
    try
    {
        boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(raw_ip_address), port);
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context, end_point.protocol());
        socket.connect(end_point);
        const unsigned char BUFFER_SIZE = 16;
        char buffer_receive[BUFFER_SIZE];
        int receive_length = boost::asio::read(socket, boost::asio::buffer(buffer_receive, BUFFER_SIZE));
        if (receive_length <= 0)
        {
            return 0;
        }

    }
    catch (boost::system::system_error& exception)
    {
        std::cerr << "Failed to read!\n"
            << "Error Code: " << exception.code() << '\n'
            << "Error Message: " << exception.what() << std::endl;
        return exception.code().value();
    }
}