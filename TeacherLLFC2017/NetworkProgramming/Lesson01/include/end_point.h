#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include <end_point.h>

//每次引入该头文件，都会重新定义
//使用extern能避免重复定义
//终端节点：用来通信的端对端的节点，可以通过IP地址和端口构造
//其他的节点可以连接这个终端节点做通信
extern int client_end_point();

extern int server_end_point();

extern int create_tcp_socket();

extern int create_acceptor_socket();

extern int bind_acceptor_socket();

extern int connect_to_end_point();

extern int connect_to_end_point_with_dns();

extern int accept_new_connection();

extern void use_const_buffer();

extern void use_buffer_string();

extern void use_buffer_array();

void write_to_socket(boost::asio::ip::tcp::socket& socket);

extern int send_data_by_write_some();

extern int send_data_by_write();

std::string read_from_socket(boost::asio::ip::tcp::socket& socket);

int read_data_by_recieve();