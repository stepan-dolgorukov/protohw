#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <iostream>

using namespace boost::asio;

int main() {
     boost::asio::io_service io_service;
     ip::tcp::socket socket(io_service);
     socket.connect( ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 7777 ));

     const std::string msg{"Домашка\n"};
     boost::system::error_code error{};
     boost::asio::write(socket, boost::asio::buffer(msg), error);
     boost::asio::streambuf receive_buffer;
     boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(),
                       error);
     const char* data{
         boost::asio::buffer_cast<const char*>(receive_buffer.data())};
     std::cout << data << std::endl;
    }
